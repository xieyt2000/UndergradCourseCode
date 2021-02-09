#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>

extern bool validateIPChecksum(uint8_t *packet, size_t len);

extern uint16_t calculate_checksum(uint16_t *header);

/**
 * @brief 进行转发时所需的 IP 头的更新：
 *        你需要先检查 IP 头校验和的正确性，如果不正确，直接返回 false ；
 *        如果正确，请更新 TTL 和 IP 头校验和，并返回 true 。
 *        你可以调用 checksum 题中的 validateIPChecksum 函数，
 *        编译的时候会链接进来。
 * @param packet 收到的 IP 包，既是输入也是输出，原地更改
 * @param len 即 packet 的长度，单位为字节
 * @return 校验和无误则返回 true ，有误则返回 false
 */
bool forward(uint8_t *packet, size_t len) {
    // 在这里你不需要考虑 TTL 为 0 的情况，在最终你的路由器实现中才做要求
    if (!validateIPChecksum(packet, len)) {
        return false;
    }
    packet[8]--;  //ttl
    auto u16_packet = (uint16_t *) packet;
    uint16_t old_checksum = ntohs(u16_packet[5]);
    // from eqn 2 in rfc 1624
    // old_ttl + ~new_ttl = old + 0xff - (old - 1) = old + 0x100
    uint32_t new_checksum = old_checksum + 0x100u;
    new_checksum = (new_checksum & 0xffffu) + (new_checksum >> 16u);
    new_checksum = (new_checksum == 0xffffu ? 0u : new_checksum);
    u16_packet[5] = htons((uint16_t) (new_checksum));
    return true;
}