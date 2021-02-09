// DONE: change header
#include "rip.h"
#include "router.h"
#include "router_hal.h"
#include "../lookup/router.h"
#include "../protocol/rip.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>


extern uint16_t calculate_checksum(uint16_t *header);

extern uint32_t calculateLength(uint32_t mask);

extern bool validateIPChecksum(uint8_t *packet, size_t len);

extern void update(bool insert, RoutingTableEntry entry);

extern bool prefix_query(uint32_t addr, uint32_t *nexthop, uint32_t *if_index);

extern bool forward(uint8_t *packet, size_t len);

extern bool disassemble(const uint8_t *packet, uint32_t len, RipPacket *output);

extern uint32_t assemble(const RipPacket *rip, uint8_t *buffer);

uint8_t packet[2048];
uint8_t output[2048];

// for online experiment, don't change
#ifdef ROUTER_R1
// 0: 192.168.1.1
// 1: 192.168.3.1
// 2: 192.168.6.1
// 3: 192.168.7.1
const in_addr_t addrs[N_IFACE_ON_BOARD] = {0x0101a8c0, 0x0103a8c0, 0x0106a8c0,
                                           0x0107a8c0};
#elif defined(ROUTER_R2)
// 0: 192.168.3.2
// 1: 192.168.4.1
// 2: 192.168.8.1
// 3: 192.168.9.1
const in_addr_t addrs[N_IFACE_ON_BOARD] = {0x0203a8c0, 0x0104a8c0, 0x0108a8c0,
                                           0x0109a8c0};
#elif defined(ROUTER_R3)
// 0: 192.168.4.2
// 1: 192.168.5.2
// 2: 192.168.10.1
// 3: 192.168.11.1
const in_addr_t addrs[N_IFACE_ON_BOARD] = {0x0204a8c0, 0x0205a8c0, 0x010aa8c0,
                                           0x010ba8c0};
#else

// 自己调试用，你可以按需进行修改，注意字节序
// 0: 10.0.0.1
// 1: 10.0.1.1
// 2: 10.0.2.1
// 3: 10.0.3.1
in_addr_t addrs[N_IFACE_ON_BOARD] = {0x0100000a, 0x0101000a, 0x0102000a,
                                     0x0103000a};
#endif

//DONE: Debugging output
#define DEBUG 0

const uint8_t RIP_RESPOND_CMD = 2;
const in_addr_t MULTICAST_IP = 0x090000e0; // 224.0.0.9
const macaddr_t MULTICAST_MAC = {0x01, 0x00, 0x5e, 0x00, 0x00, 0x09};

void hex_ip_format(uint32_t ip_hex, uint32_t *output) {
    output[0] = ip_hex >> 24u;
    output[1] = ip_hex >> 16u & 0xffu;
    output[2] = ip_hex >> 8u & 0xffu;
    output[3] = ip_hex & 0xffu;
}

void print_routing_table() {
    printf("routing table:\n");
    for (auto iter = routingTable.begin(); iter != routingTable.end(); iter++) {
        RoutingTableEntry entry = iter->second;
        uint32_t addr_arr[5], nexthop_arr[5];
        hex_ip_format(entry.addr, addr_arr);
        hex_ip_format(entry.nexthop, nexthop_arr);
        printf("{addr:%d.%d.%d.%d, len:%d, nexthop:%d.%d.%d.%d, if_index:%d, metric:%x}\n",
               addr_arr[3], addr_arr[2], addr_arr[1], addr_arr[0], entry.len,
               nexthop_arr[3], nexthop_arr[2], nexthop_arr[1], nexthop_arr[0],
               entry.if_index, entry.metric);
    }
    printf("routing table end\n");
}

void print_rip(uint32_t src_addr, const RipPacket &rip) {
    uint32_t src_arr[5];
    hex_ip_format(src_addr, src_arr);
    printf("received rip packet\n");
    printf("{command: %d, numEntries: %d, src:%d.%d.%d.%d}\n", rip.command, rip.numEntries,
           src_arr[3], src_arr[2], src_arr[1], src_arr[0]);
    printf("packet end\n");
}

void print_found_routing(uint32_t dst_addr, uint32_t nexthop, uint32_t if_index) {
    printf("found in routing table\n");
    uint32_t addr_arr[5], nexthop_arr[5];
    hex_ip_format(dst_addr, addr_arr);
    hex_ip_format(nexthop, nexthop_arr);
    printf("{dst_addr:%d.%d.%d.%d, nexthop:%d.%d.%d.%d, if_index:%d, metric:%x}\n",
           addr_arr[3], addr_arr[2], addr_arr[1], addr_arr[0],
           nexthop_arr[3], nexthop_arr[2], nexthop_arr[1], nexthop_arr[0],
           if_index);
    printf("end");
}

void assemble_and_send_rip(const RipPacket *rip_packet, uint32_t interface,
                           const macaddr_t &dst_mac, uint8_t *target_packet) {
    // assemble RIP
    uint16_t total_len = assemble(rip_packet, &target_packet[28]) + 28;
#if DEBUG
    printf("rip total len: %d\n", total_len);
#endif
    // DONE: checksum calculation for ip
    auto ip_header = (struct ip *) target_packet;
    ip_header->ip_len = htons(total_len);
    ip_header->ip_sum = 0;
    ip_header->ip_sum = calculate_checksum((uint16_t *) ip_header);
    // DONE: udp length
    auto udp_header = (struct udphdr *) (&target_packet[20]);
    udp_header->uh_ulen = htons(total_len - 20);
    // send it back
#if DEBUG
    if (!validateIPChecksum(target_packet, total_len))
        printf("IP checksum error: %d\n", ip_header->ip_sum);
    RipPacket tmpRip;
    if (!disassemble(target_packet, total_len, &tmpRip))
        printf("Invalid RIP\n");
#endif
    HAL_SendIPPacket(interface, target_packet, total_len, dst_mac);
}

void send_routing_table(
        in_addr_t dst_ip, const macaddr_t &dst_mac, uint32_t interface,
        uint8_t *target_packet, bool multicast) {
    RipPacket resp;
    // DONE: fill resp
    // ref. RFC 2453 Section 3.4.3
    resp.command = RIP_RESPOND_CMD;
    // fill IP headers
    auto ip_header = (struct ip *) target_packet;
    ip_header->ip_hl = 5;
    ip_header->ip_v = 4;
    // DONE: set tos = 0, id = 0, off = 0, ttl = 1, p = 17(udp), dst and src
    ip_header->ip_tos = 0;
    ip_header->ip_id = 0;
    ip_header->ip_off = 0;
    ip_header->ip_ttl = 1;
    ip_header->ip_p = 17;
    ip_header->ip_sum = 0;
    ip_header->ip_dst = in_addr{dst_ip};
    // total len, checksum, src_addr set later
    // fill UDP headers
    auto udp_header = (struct udphdr *) &target_packet[20];
    // src port = 520   dst port = 520
    udp_header->uh_sport = htons(520u);
    udp_header->uh_dport = htons(520u);
    udp_header->uh_sum = 0;
    // UDP len set later
    for (uint32_t i = 0; i < N_IFACE_ON_BOARD; i++) {
        if (multicast || i == interface) {
            ip_header->ip_src = in_addr{addrs[i]};
            uint32_t entry_cnt = 0;
            for (auto iter = routingTable.begin(); iter != routingTable.end(); iter++, entry_cnt++) {
                const RoutingTableEntry &routing_entry = iter->second;
                // implement split horizon with poisoned reverse
                uint32_t rip_metric = (dst_ip == routing_entry.nexthop) ? 16 : routing_entry.metric;
//                uint32_t rip_metric = routing_entry.metric;
                RipEntry &cur_resp_entry = resp.entries[entry_cnt];
                cur_resp_entry.addr = routing_entry.addr;
                cur_resp_entry.mask = calculateMask(routing_entry.len);
                cur_resp_entry.nexthop = 0;
                cur_resp_entry.metric = htonl(rip_metric);
                if (entry_cnt >= (RIP_MAX_ENTRY - 1)) {
                    resp.numEntries = entry_cnt;
                    assemble_and_send_rip(&resp, i, dst_mac, target_packet);
                    entry_cnt = 0;
#if DEBUG
                    printf("rip max entry met.\n");
#endif
                }
            }
            if (entry_cnt > 0) {
                resp.numEntries = entry_cnt;
                assemble_and_send_rip(&resp, i, dst_mac, target_packet);
#if DEBUG
                printf("send unfilled rip of %d entries.\n", entry_cnt);
#endif
            }
        }
    }
}

// return in network order
uint16_t calculate_icmp_checksum(uint16_t *icmp_packet, uint32_t len) {
    uint32_t checksum = 0;
    auto *header_end = icmp_packet + len;
    for (uint16_t *iter = icmp_packet; iter < header_end; iter++) {
        checksum += *iter;
    }
    checksum = (checksum & 0xffffu) + (checksum >> 16u);
    checksum = (checksum & 0xffffu) + (checksum >> 16u);
    return ~checksum;
}

void send_icmp_echoreply(const macaddr_t &dst_mac, uint32_t interface, uint8_t *target_packet) {
    // you need to:
    auto ip_header = (struct ip *) target_packet;
    auto icmp_header = (struct icmp *) (&target_packet[20]);
    // 1. swap src ip addr and dst ip addr
    in_addr swap_tmp = ip_header->ip_src;
    ip_header->ip_src = ip_header->ip_dst;
    ip_header->ip_dst = swap_tmp;
    // 2. change icmp `type` in header
    icmp_header->icmp_type = ICMP_ECHOREPLY;
    // 3. set ttl to 64
    ip_header->ip_ttl = 64;
    // 4. re-calculate icmp checksum and ip checksum
    ip_header->ip_sum = 0;
    ip_header->ip_sum = calculate_checksum((uint16_t *) ip_header);
    icmp_header->icmp_cksum = 0;
    uint32_t total_len = ntohs(ip_header->ip_len);
    icmp_header->icmp_cksum = calculate_icmp_checksum((uint16_t *) icmp_header, (total_len - 20) / 2);
    // 5. send icmp packet
    HAL_SendIPPacket(interface, target_packet, total_len, dst_mac);
}

void send_icmp_time_exceed(in_addr_t dst_ip, const macaddr_t &dst_mac, uint32_t interface) {
    // fill IP header
    const uint32_t total_len = 20 + 8 + 20 + 8;
    auto *ip_header = (struct ip *) output;
    ip_header->ip_hl = 5;
    ip_header->ip_v = 4;
    // DONE: set tos = 0, id = 0, off = 0, ttl = 64, p = 1(icmp), src and dst
    ip_header->ip_tos = 0;
    ip_header->ip_len = htons(total_len);
    ip_header->ip_id = 0;
    ip_header->ip_off = 0;
    ip_header->ip_ttl = 64;
    ip_header->ip_p = 1;
    ip_header->ip_src = in_addr{addrs[interface]};
    ip_header->ip_dst = in_addr{dst_ip};
    // fill icmp header
    auto icmp_header = (struct icmp *) &output[20];
    // icmp type = Time Exceeded
    icmp_header->icmp_type = ICMP_TIMXCEED;
    // icmp_header = ICMP_TIME_EXCEEDED;
    // DONE: icmp code = 0
    icmp_header->icmp_code = 0;
    // DONE: fill unused fields with zero
    memset(&output[24], 0, 4);
    // DONE: append "ip header and first 8 bytes of the original payload"
    memcpy(&output[28], packet, 28);
    // DONE: calculate icmp checksum and ip checksum
    ip_header->ip_sum = 0;
    ip_header->ip_sum = calculate_checksum((uint16_t *) ip_header);
    icmp_header->icmp_cksum = 0;
    icmp_header->icmp_cksum = calculate_icmp_checksum((uint16_t *) icmp_header, (total_len - 20) / 2);
    // DONE: send icmp packet
    HAL_SendIPPacket(interface, output, total_len, dst_mac);
}

void send_icmp_dst_unreach(in_addr_t dst_ip, const macaddr_t &dst_mac, uint32_t interface) {
    // fill IP header
    const uint32_t total_len = 20 + 8 + 20 + 8;
    auto ip_header = (struct ip *) output;
    ip_header->ip_hl = 5;
    ip_header->ip_v = 4;
    // DONE: set tos = 0, id = 0, off = 0, ttl = 64, p = 1(icmp), src and dst
    ip_header->ip_tos = 0;
    ip_header->ip_len = htons(total_len);
    ip_header->ip_id = 0;
    ip_header->ip_off = 0;
    ip_header->ip_ttl = 64;
    ip_header->ip_p = 1;
    ip_header->ip_src = in_addr{addrs[interface]};
    ip_header->ip_dst = in_addr{dst_ip};
    // fill icmp header
    auto icmp_header = (struct icmp *) &output[20];
    // icmp type = Destination Unreachable
    icmp_header->icmp_type = ICMP_UNREACH;
    // DONE: icmp code = Destination Network Unreachable
    icmp_header->icmp_code = ICMP_UNREACH_NET;
    // DONE: fill unused fields with zero
    memset(&output[24], 0, 4);
    // DONE: append "ip header and first 8 bytes of the original payload"
    memcpy(&output[28], packet, 28);
    // DONE: calculate icmp checksum and ip checksum
    ip_header->ip_sum = 0;
    ip_header->ip_sum = calculate_checksum((uint16_t *) ip_header);
    icmp_header->icmp_cksum = 0;
    icmp_header->icmp_cksum = calculate_icmp_checksum((uint16_t *) icmp_header, (total_len - 20) / 2);
    // DONE: send icmp packet
    HAL_SendIPPacket(interface, output, total_len, dst_mac);
}

int main(int argc, char *argv[]) {
    // 0a.
    int res = HAL_Init(DEBUG, addrs);
    if (res < 0) {
        return res;
    }

    // 0b. Add direct routes
    // For example:
    // 10.0.0.0/24 if 0
    // 10.0.1.0/24 if 1
    // 10.0.2.0/24 if 2
    // 10.0.3.0/24 if 3
    for (uint32_t i = 0; i < N_IFACE_ON_BOARD; i++) {
        RoutingTableEntry entry = {
                .addr = addrs[i] & 0x00FFFFFF, // network byte order
                .len = 24,                     // host byte order
                .if_index = i,                 // host byte order
                .nexthop = 0,                   // network byte order, means direct
                .metric=1
        };
        update(true, entry);
#if DEBUG
        printf("%x\n", entry.addr);
#endif
    }

    uint64_t last_time = 0;
    while (1) {
#if DEBUG
        printf("loop begins\n");
#endif
        uint64_t time = HAL_GetTicks();
        // the RFC says 30s interval,
        // but for faster convergence, use 5s here
        if (time > last_time + 5 * 1000) {
            // ref. RFC 2453 Section 3.8
            printf("5s Timer\n");
#if DEBUG
            print_routing_table();
#endif
            // HINT: print complete routing table to stdout/stderr for debugging
            // DONE: send complete routing table to every interface
            send_routing_table(MULTICAST_IP, MULTICAST_MAC, 0, output, true);
            last_time = time;
        }

        int mask = (1 << N_IFACE_ON_BOARD) - 1;
        macaddr_t src_mac;
        macaddr_t dst_mac;
        int if_index;
        res = HAL_ReceiveIPPacket(mask, packet, sizeof(packet), src_mac, dst_mac,
                                  1000, &if_index);
        if (res == HAL_ERR_EOF) {
            break;
        } else if (res < 0) {
            return res;
        } else if (res == 0) {
            // Timeout
            continue;
        } else if (res > sizeof(packet)) {
            // packet is truncated, ignore it
            continue;
        }
#if DEBUG
        printf("receive packet\n");
#endif

        // 1. validate
        if (!validateIPChecksum(packet, res)) {
            printf("Invalid IP Checksum\n");
            // drop if ip checksum invalid
            continue;
        }
        in_addr_t src_addr, dst_addr;
        // DONE: extract src_addr and dst_addr from packet (big endian)
        auto ip_header = (struct ip *) packet;
        src_addr = ip_header->ip_src.s_addr;
        dst_addr = ip_header->ip_dst.s_addr;
        // 2. check whether dst is me
        bool dst_is_me = false;
        for (int i = 0; i < N_IFACE_ON_BOARD; i++) {
            if (memcmp(&dst_addr, &addrs[i], sizeof(in_addr_t)) == 0) {
                dst_is_me = true;
                break;
            }
        }
#if DEBUG
        printf("dst is me before multi? %d\n", dst_is_me);
#endif
        // DONE: handle rip multicast address(224.0.0.9)
        dst_is_me = dst_is_me || (memcmp(&dst_addr, &MULTICAST_IP, sizeof(in_addr_t)) == 0);
#if DEBUG
        printf("dst is me? %d\n", dst_is_me);
#endif
        if (dst_is_me) {
            // 3a.1
            RipPacket rip;
            // check and validate
            if (disassemble(packet, res, &rip)) {
#if DEBUG
                print_rip(src_addr, rip);
#endif
                if (rip.command == 1) {
                    // 3a.3 request, ref. RFC 2453 Section 3.9.1
                    // only need to respond to whole table requests in the lab
                    if (rip.numEntries == 1 && ntohl(rip.entries[0].metric) == 16) {
                        send_routing_table(src_addr, src_mac, if_index, output, false);
                    }
                } else {
                    // 3a.2 response, ref. RFC 2453 Section 3.9.2
                    // DONE: update routing table
                    // HINT: what is missing from RoutingTableEntry?
                    // optional: triggered updates ref. RFC 2453 Section 3.10.1
                    for (uint32_t i = 0; i < rip.numEntries; i++) {
                        RipEntry rip_entry = rip.entries[i];
                        // new metric = ?
                        // update metric, if_index, nexthop
                        uint32_t new_metric = ntohl(rip_entry.metric) + 1;
                        if (new_metric > 16) {
                            new_metric = 16;
                        }
                        // HINT: handle nexthop = 0 case
                        uint32_t new_nexthop = rip_entry.nexthop;
                        if (new_nexthop == 0) {
                            new_nexthop = src_addr;
                        }
                        uint32_t prefix_len = calculateLength(rip_entry.mask);
                        // you might want to use `prefix_query` and `update`, but beware of
                        // the difference between exact match and longest prefix match.
                        // exact match
                        auto routing_table_iter = routingTable.find(CIDRAddr(rip_entry.addr, prefix_len));
                        if (routing_table_iter != routingTable.end()) {  // update
                            RoutingTableEntry &routing_entry = routing_table_iter->second;
                            if (new_metric < routing_entry.metric ||
                                (src_addr == routing_entry.nexthop && new_metric != routing_entry.metric)) {
                                if (new_metric == 16) {
                                    routingTable.erase(routing_table_iter);
                                } else {
                                    routing_entry.metric = new_metric;
                                    routing_entry.nexthop = new_nexthop;
                                }
                            }
                        } else {  // insert new
                            if (new_metric != 16) {
                                update(true,
                                       RoutingTableEntry{
                                               .addr=rip_entry.addr, .len=prefix_len,
                                               .if_index=(uint32_t) if_index, .nexthop=src_addr,
                                               .metric=new_metric
                                       });
                            }
                        }
                    }
                }
            } else {
                // not a rip packet
                // handle icmp echo request packet
                // DONE: how to determine?
#if DEBUG
                printf("dst is me not rip\n");
#endif
                if (ip_header->ip_p == 1) {  // icmp
#if DEBUG
                    printf("dst is me icmp\n");
#endif
                    auto recv_icmp = (icmp *) (&packet[20]);
                    if (recv_icmp->icmp_type == ICMP_ECHO) {
                        // construct icmp echo reply
                        // reply is mostly the same as request
                        memcpy(output, packet, sizeof(ip) + sizeof(icmp));
                        send_icmp_echoreply(src_mac, if_index, output);
                    }
                }
            }
        } else {
#if DEBUG
            printf("dst is not me\n");
#endif
            // 3b.1 dst is not me
            // check ttl
            uint8_t ttl = packet[8];
            if (ttl <= 1) {
                // send icmp time to live exceeded to src addr
#if DEBUG
                printf("ttl exceed\n");
#endif
                send_icmp_time_exceed(src_addr, src_mac, if_index);
            } else {
                // forward
                // beware of endianness
                uint32_t nexthop, dest_if;
                if (prefix_query(dst_addr, &nexthop, &dest_if)) {
                    // found
                    macaddr_t dest_mac;
#if DEBUG
                    print_found_routing(dst_addr, nexthop, dest_if);
#endif
                    // direct routing
                    if (nexthop == 0) {
                        nexthop = dst_addr;
                    }
                    if (HAL_ArpGetMacAddress(dest_if, nexthop, dest_mac) == 0) {
                        // found
                        memcpy(output, packet, res);
                        // update ttl and checksum
                        forward(output, res);
                        HAL_SendIPPacket(dest_if, output, res, dest_mac);
                    } else {
                        // not found
                        // you can drop it
                        printf("ARP not found for nexthop %x\n", nexthop);
                    }
                } else {
                    // not found
                    // send ICMP Destination Network Unreachable
                    printf("IP not found in routing table for src %x dst %x\n", src_addr, dst_addr);
                    // send icmp destination net unreachable to src addr
                    send_icmp_dst_unreach(src_addr, src_mac, if_index);
                }
            }
        }
    }
    return 0;
}
