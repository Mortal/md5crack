#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include "md5.h"

using namespace std;

void md5(char * sm, size_t l, uint32_t * h) {
	md5string s(sm, l);
	md5calculation c = s.md5();
	copy(c.result(), c.result()+4, h);
}

inline static uint32_t swapendian(uint32_t i) {
	return (i << 24)
		| ((i & 0xFF00) << 8)
		| ((i & 0xFF0000) >> 8)
		| (i >> 24);
}

std::string hash_hex(const uint32_t * h) {
	uint32_t swap[4];
	swap[0] = swapendian(h[0]);
	swap[1] = swapendian(h[1]);
	swap[2] = swapendian(h[2]);
	swap[3] = swapendian(h[3]);
	char c[33];
	sprintf(c, "%08x%08x%08x%08x", swap[0], swap[1], swap[2], swap[3]);
	return c;
}

// vim:set ts=4 sw=4 sts=4 noet:
