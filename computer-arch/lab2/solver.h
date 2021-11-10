#pragma once
#include "cache.h"
#include <iostream>

using namespace std;

class Solver {
public:
	// getAns 返回获取的未知地址
	int getAns(BaseCache* cache, int addresses, int lines);
};
