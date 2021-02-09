#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

// return in host order
uint16_t calculate_checksum(uint16_t *header) {
    uint32_t checksum = 0;
    size_t header_len = (header[0] & 0xfu) * 2;
    auto *header_end = header + header_len;
    for (uint16_t *iter = header; iter < header_end; iter++) {
        checksum += *iter;
    }
    checksum = (checksum & 0xffffu) + (checksum >> 16u);
    checksum = (checksum & 0xffffu) + (checksum >> 16u);
    return ~checksum;
}


/**
 * @brief 进行 IP 头的校验和的验证
 * @param packet 完整的 IP 头和载荷
 * @param len 即 packet 的长度，单位是字节，保证包含完整的 IP 头
 * @return 校验和无误则返回 true ，有误则返回 false
 */

bool validateIPChecksum(uint8_t *packet, size_t len) {
    auto *u16_packet = (uint16_t *) packet;
    uint16_t old_checksum = u16_packet[5];
    u16_packet[5] = 0;
    bool ret = old_checksum == calculate_checksum(u16_packet);
    u16_packet[5] = old_checksum;
    return ret;
}
