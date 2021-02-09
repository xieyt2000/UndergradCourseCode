#include "router.h"
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>

map<CIDRAddr, RoutingTableEntry> routingTable;


uint32_t calculateMask(uint32_t maskLen) {
    uint8_t byteMask = ~(((uint8_t) 1 << (8 - maskLen % 8)) - 1);
    uint32_t maskBytes = maskLen / 8 * 8;
    uint32_t mask = (1llu << maskBytes) - 1 + (byteMask << maskBytes);
    return mask;
}

uint32_t calculateLength(uint32_t mask) {
    int len = 0;
    while (mask > 0) {
        if (mask % 2 == 1) {
            len++;
        }
        mask /= 2;
    }
    return len;
}

/**
 * @brief 插入/删除一条路由表表项
 * @param insert 如果要插入则为 true ，要删除则为 false
 * @param entry 要插入/删除的表项
 *
 * 插入时如果已经存在一条 addr 和 len 都相同的表项，则替换掉原有的。
 * 删除时按照 addr 和 len **精确** 匹配。
 */
void update(bool insert, RoutingTableEntry entry) {
    CIDRAddr addr = CIDRAddr(entry.addr, entry.len);
    if (insert) {
        routingTable[addr] = entry;
    } else {
        auto routingTableIter = routingTable.find(addr);
        if (routingTableIter != routingTable.end()) {
            routingTable.erase(routingTableIter);
        }
    }
}

/**
 * @brief 进行一次路由表的查询，按照最长前缀匹配原则
 * @param addr 需要查询的目标地址，网络字节序
 * @param nexthop 如果查询到目标，把表项的 nexthop 写入
 * @param if_index 如果查询到目标，把表项的 if_index 写入
 * @return 查到则返回 true ，没查到则返回 false
 */
bool prefix_query(uint32_t addr, uint32_t *nexthop, uint32_t *if_index) {
    for (int32_t maskLen = 32; maskLen >= 0; maskLen--) {
        uint32_t mask = calculateMask(maskLen);
        auto routingTableIter = routingTable.find(CIDRAddr(addr & mask, maskLen));
        if (routingTableIter != routingTable.end()) {
            *if_index = routingTableIter->second.if_index;
            *nexthop = routingTableIter->second.nexthop;
            return true;
        }
    }
    *if_index = *nexthop = 0;
    return false;
}
