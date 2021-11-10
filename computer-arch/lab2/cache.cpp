#include <iostream>
#include <cstdlib>
#include "cache.h"

using namespace std;

void BaseCache::state_rand() {
	// Ëæ»ú³õÊ¼×´Ì¬
	for (int i = 0; i < line; ++i) {
		tag[i] = 0;
	}
	int sum = (rand() % 64) + 16;
	for (int i = 0; i < sum; ++i) {
		int j = rand() % 1600;
		access(j);
	}
	count = 0;
}

BaseCache::BaseCache(int _u, int _line) {
	count = 0;
	u = _u;
	line = _line;
	for (int i = 0; i < line; ++i)
		tag[i] = 0;

	for (int i = 0; i < line; ++i)
		valid[i] = false;

	for (int i = 0; i < line; ++i)
		time[i] = 0;
	state_rand();
}

int BaseCache::getCount() {
	return count;
}

int BaseCache::flush(int x) {
	bool hit = false;
	count++;
	if (x < 0 || x >= 1600) {
		return 0;
	}

	int line_num = x % 32;
	if (valid[line_num] && tag[line_num] == x) {
		valid[line_num] = false;
		hit = true;
	}

	if (hit) return 1;
	else return 0;
}

int BaseCache::access(int x) {
	bool hit = false;
	count++;
	if (x < 0 || x >= 1600) {
		return 0;
	}

	int line_num = x % 32;

	if (valid[line_num] && tag[line_num] == x) {
		hit = true;
	}
	else {
		valid[line_num] = true;
		tag[line_num] = x;
	}

	if (hit) return 0;
	else return 1;
}

int BaseCache::accessu() {
	return access(u);
}

int BaseCache::flushu() {
	return flush(u);
}

int BaseCache::flushAny() {
	bool hit = false;
	count++;
	for (int i = 0; i < line; ++i) {
		if (valid[i]) {
			valid[i] = false;
			hit = true;
		}
	}

	if (hit) return 1;
	else return 0;
}
