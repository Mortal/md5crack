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


std::string hash_hex(const uint32_t * h) {
	uint32_t swap[4];
	const char * a = reinterpret_cast<const char *>(h);
	char * b = reinterpret_cast<char *>(swap);
	b[0] = a[3];
	b[1] = a[2];
	b[2] = a[1];
	b[3] = a[0];
	b[4] = a[7];
	b[5] = a[6];
	b[6] = a[5];
	b[7] = a[4];
	b[8] = a[11];
	b[9] = a[10];
	b[10] = a[9];
	b[11] = a[8];
	b[12] = a[15];
	b[13] = a[14];
	b[14] = a[13];
	b[15] = a[12];
	char c[33];
	sprintf(c, "%08x%08x%08x%08x", swap[0], swap[1], swap[2], swap[3]);
	return c;
}

// vim:set ts=4 sw=4 sts=4 noet:
