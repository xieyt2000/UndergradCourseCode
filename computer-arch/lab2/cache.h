#pragma once
#include <iostream>
#include <cstdlib>

using namespace std;

class BaseCache {
	// 包含32个Cache Line，按照直接映射的方式组织（地址 % 32 就是映射的Cache Line）。
	// u: 未知地址
	int u;

	// tag：存储的物理地址；valid：是否有效；time：计时
	int line;
	int tag[32];
	bool valid[32];
	int time[32];

	// count：计算总访问次数
	int count;

	void state_rand();

public:
	BaseCache(int _u, int _line);

	int getCount();

	// flush(x)：将地址x从cache中清除，如果命中，延迟高，否则延迟低。
	// access(x)：读写地址x，如果命中，延迟低，否则延迟高。
	// flushu、accessu：对地址u的flush、access，不需要参数，返回值同一般的flush、access。
	// flushAny：将整个cache情况，如果cache中存在有效数据，延迟高，否则延迟低。
	// 延迟高：返回1； 延迟低：返回0

	int flush(int x);

	int access(int x);

	int accessu();

	int flushu();

	int flushAny();
};
