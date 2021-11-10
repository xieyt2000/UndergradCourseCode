#include "solver.h"
#include "cache.h"
#include <iostream>

int Solver::getAns(BaseCache *cache, int addresses, int lines) {
    // DONE：获取并返回未知地址
    cache->flushAny();
    // u in which cache line?
    int line = 0;
    cache->accessu();
    for (; line < lines; line++) {
        if (cache->access(line) == 0) {  // u is line
            return line;
        }
        if (cache->accessu() == 1) {  // u is replaced by line
            break;
        }
    }
    for (int i = line; i < addresses; i += lines) {
        if (cache->flush(i) == 1) {
            return i;
        }
    }
    return -1;
}
