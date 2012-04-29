#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <err.h>
#include <cstdlib>
#include "md5.h"

using namespace std;

template <uint64_t D>
inline static void inc(char * buf);

template <>
void inc<0>(char * buf) {
	++buf[0];
}

template <uint64_t D>
void inc(char * buf) {
	if (++buf[D] > '9') {
		buf[D] = '0';
		inc<D-1>(buf);
	}
}

inline int parsehex(char c) {
	if ('0' <= c && c <= '9') return c-'0';
	return 10+c-'a';
}

void printhash(const uint32_t * h) {
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
	const uint64_t digits = 9;
	string msg(digits, '0');
	msg[0] = '1';
	md5string s(msg);
	while (true) {
		const uint32_t * h = s.md5().result();
		const bool found =
			(h[0] == target[0] &&
			 h[1] == target[1] &&
			 h[2] == target[2] &&
			 h[3] == target[3]);
		const bool progress =
			(s.data[digits-7] == '0' &&
			 s.data[digits-6] == '0' &&
			 s.data[digits-5] == '0' &&
			 s.data[digits-4] == '0' &&
			 s.data[digits-3] == '0' &&
			 s.data[digits-2] == '0' &&
			 s.data[digits-1] == '0');
		if (found || progress) {
			fwrite(&*s.data.begin(), 1, 9, stdout);
			if (found)
				printf(" <-- match found for ");
			else
				printf(" ");
			printhash(h);
			fflush(stdout);
		}
		inc<digits-1>(&*s.data.begin());
		s.invalidate_suffix(0, digits);
	}
	return 0;
}
// vim:set ts=4 sw=4 sts=4 noet:
