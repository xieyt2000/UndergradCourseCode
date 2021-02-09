#include "rip.h"
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>

/*
  在头文件 rip.h 中定义了结构体 `RipEntry` 和 `RipPacket` 。
  你需要从 IPv4 包中解析出 RipPacket 结构体，也要从 RipPacket 结构体构造出对应的
  IP 包。 由于 RIP 包结构本身不记录表项的个数，需要从 IP 头的长度中推断，所以在
  RipPacket 中额外记录了个数。 需要注意这里的地址都是用 **网络字节序（大端序）**
  存储的，1.2.3.4 在小端序的机器上被解释为整数 0x04030201 。
*/

bool maskValid(uint32_t mask) {
    uint32_t inverse = ~mask;   // 0...01..1
    uint32_t one1 = inverse + 1;  //0...010...0
    return ((inverse & one1) == 0);
}

/**
 * @brief 从接受到的 IP 包解析出 RIP 协议的数据
 * @param packet 接受到的 IP 包
 * @param len 即 packet 的长度
 * @param output 把解析结果写入 *output
 * @return 如果输入是一个合法的 RIP 包，把它的内容写入 RipPacket 并且返回
 * true；否则返回 false
 *
 * IP 包的 Total Length 长度可能和 len 不同，当 Total Length 大于 len
 * 时，把传入的 IP 包视为不合法。 你不需要校验 IP 头和 UDP 的校验和是否合法。
 * 你需要检查 Command 是否为 1 或 2，Version 是否为 2， Zero 是否为 0，
 * Family 和 Command 是否有正确的对应关系（见上面结构体注释），Tag 是否为 0，
 * Metric 是否在 [1,16] 的区间内，
 * Mask 的二进制是不是连续的 1 与连续的 0 组成等等。
 */
bool disassemble(const uint8_t *packet, uint32_t len, RipPacket *output) {
    const auto *u16Packet = (uint16_t *) packet;
    const uint16_t totalLen = ntohs(u16Packet[1]);
    if (totalLen > len)
        return false;
    const uint8_t headerLen = (packet[0] & 0xfu) * 4, udpHeaderLen = 8;
    const uint8_t *ripHeader = packet + headerLen + udpHeaderLen;
    const auto u16RipHeader = (uint16_t *) ripHeader;
    const uint8_t command = ripHeader[0];
    output->command = command;
    if (command != 1 && command != 2)
        return false;
    const uint8_t version = ripHeader[1];
    if (version != 2)
        return false;
    const uint16_t zero = ntohs(u16RipHeader[1]);
    if (zero != 0)
        return false;
    const auto ripEntriesBegin = (uint16_t *) (ripHeader + 4);
    const uint32_t ripHeaderLen = 4;
    const uint32_t numEntries = (len - headerLen - udpHeaderLen - ripHeaderLen) / 20;
    output->numEntries = numEntries;
    for (uint32_t i = 0; i < numEntries; i++) {
        const uint16_t *u16CurEntryBegin = ripEntriesBegin + 10 * i;
        const uint16_t family = ntohs(u16CurEntryBegin[0]);
        if (!((command == 1 && family == 0) || (command == 2 && family == 2)))
            return false;
        const uint16_t tag = ntohs(u16CurEntryBegin[1]);
        if (tag != 0)
            return false;
        const auto u32curEntryBegin = (uint32_t *) (u16CurEntryBegin);
        const uint32_t metric = ntohl(u32curEntryBegin[4]);
        if (metric < 1 || metric > 16)
            return false;
        const uint32_t mask = ntohl(u32curEntryBegin[2]);
        if (!maskValid(mask))
            return false;
        RipEntry entry = {u32curEntryBegin[1], u32curEntryBegin[2],
                          u32curEntryBegin[3], u32curEntryBegin[4]};
        output->entries[i]=entry;
    }
    return true;
}

/**
 * @brief 从 RipPacket 的数据结构构造出 RIP 协议的二进制格式
 * @param rip 一个 RipPacket 结构体
 * @param buffer 一个足够大的缓冲区，你要把 RIP 协议的数据写进去
 * @return 写入 buffer 的数据长度
 *
 * 在构造二进制格式的时候，你需要把 RipPacket 中没有保存的一些固定值补充上，包括
 * Version、Zero、Address Family 和 Route Tag 这四个字段 你写入 buffer
 * 的数据长度和返回值都应该是四个字节的 RIP 头，加上每项 20 字节。
 * 需要注意一些没有保存在 RipPacket 结构体内的数据的填写。
 */
uint32_t assemble(const RipPacket *rip, uint8_t *buffer) {
    buffer[0] = rip->command;
    const uint16_t family = htons(rip->command == 1 ? 0 : 2);
    buffer[1] = 2;  // version
    buffer[2] = 0;  // zero first byte
    buffer[3] = 0;  // zero second byte
    // entries
    const auto entriesBegin = (uint16_t *) (buffer + 4);
    for (uint32_t i = 0; i < rip->numEntries; i++) {
        uint16_t *u16CurEntryBegin = entriesBegin + 10 * i;
        u16CurEntryBegin[0] = family;
        u16CurEntryBegin[1] = 0;  // tag
        auto u32CurEntryBegin = (uint32_t *) (u16CurEntryBegin + 2);
        u32CurEntryBegin[0] = rip->entries[i].addr;
        u32CurEntryBegin[1] = rip->entries[i].mask;
        u32CurEntryBegin[2] = rip->entries[i].nexthop;
        u32CurEntryBegin[3] = rip->entries[i].metric;
    }
    return 4 + 20 * rip->numEntries;
}
