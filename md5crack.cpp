#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <err.h>
#include <cstdlib>
#include "md5.h"

using namespace std;

void md5chunk(unsigned char * buf, uint32_t * h);

template <uint64_t D>
inline static void inc(unsigned char * buf);

template <>
void inc<0>(unsigned char * buf) {
	++buf[0];
}

template <uint64_t D>
void inc(unsigned char * buf) {
	if (++buf[D] > '9') {
		buf[D] = '0';
		inc<D-1>(buf);
	}
}

inline int parsehex(char c) {
	if ('0' <= c && c <= '9') return c-'0';
	return 10+c-'a';
}

void printhash(uint32_t * h) {
	string hex = hash_hex(h);
	printf("%s\n", hex.c_str());
}

void parse_target(char * arg, uint32_t * target) {
	int i = 0;
	while (arg[i]) {
		if (!(('0' <= arg[i] && arg[i] <= '9') || ('a' <= arg[i] && arg[i] <= 'f'))) break;
		++i;
	}
	if (i != 32 || arg[i]) errx(1, "Invalid hash");
	unsigned char * t = reinterpret_cast<unsigned char *>(target);
	for (int i = 0; i < 16; ++i) {
		t[i] = 16*parsehex(arg[2*i])+parsehex(arg[2*i+1]);
	}
}

int main(int argc, char ** argv) {
	if (argc < 2) errx(1, "Missing parameter. Usage: %s [hash]", argv[0]);
	uint32_t target[4];
	parse_target(argv[1], target);
	unsigned char buf[64];
	fill(buf+0, buf+64, 0);
	const uint64_t digits = 9;
	for (uint64_t i = 0; i < digits; ++i) {
		buf[i] = '0';
	}
	buf[0] = '1';
	buf[digits] = 0x80;
	uint64_t * n = reinterpret_cast<uint64_t *>(buf+56);
	*n = digits*8;
	while (true) {
		uint32_t h[4];
		h[0] = 0x67452301;
		h[1] = 0xefcdab89;
		h[2] = 0x98badcfe;
		h[3] = 0x10325476;
		md5chunk(buf, h);
		const bool found =
			(h[0] == target[0] &&
			 h[1] == target[1] &&
			 h[2] == target[2] &&
			 h[3] == target[3]);
		const bool progress =
			(buf[digits-7] == '0' &&
			 buf[digits-6] == '0' &&
			 buf[digits-5] == '0' &&
			 buf[digits-4] == '0' &&
			 buf[digits-3] == '0' &&
			 buf[digits-2] == '0' &&
			 buf[digits-1] == '0');
		if (found || progress) {
			fwrite(buf, 1, 9, stdout);
			if (found)
				printf(" <-- match found for ");
			else
				printf(" ");
			printhash(h);
			fflush(stdout);
		}
		inc<digits-1>(buf);
	}
	return 0;
}
