#include <algorithm>
#include <stdint.h>
using namespace std;

static int r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
static unsigned int k[] = {
0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

void md5(char * sm, size_t l, char * output) {
	unsigned char * m = reinterpret_cast<unsigned char *>(sm);
	uint32_t * h = reinterpret_cast<uint32_t *>(output);
	size_t padded = (l+9+63)/64*64;
	h[0] = 0x67452301;
	h[1] = 0xefcdab89;
	h[2] = 0x98badcfe;
	h[3] = 0x10325476;
	unsigned char * buf = new unsigned char[padded];
	copy(m, m+l, buf);
	buf[l] = 0x80;
	fill(buf+l+1, buf+padded-8, 0);
	uint64_t * p = reinterpret_cast<uint64_t *>(buf+padded-8);
	*p = l*8;
	for (unsigned char * bb = buf; bb < buf+padded; bb += 64) {
		uint32_t * w = reinterpret_cast<uint32_t *>(bb);
		unsigned int a = h[0];
		unsigned int b = h[1];
		unsigned int c = h[2];
		unsigned int d = h[3];
		unsigned int f, g;
		for (unsigned int i = 0; i < 64; ++i) {
			if (i < 16) {
				f = (b & c) | ((~b) & d);
				g = i;
			} else if (i < 32) {
				f = (d & b) | ((~d) & c);
				g = (5*i + 1) % 16;
			} else if (i < 48) {
				f = b ^ c ^ d;
				g = (3*i + 5) % 16;
			} else {
				f = c ^ (b | (~d));
				g = (7*i) % 16;
			}
			const unsigned int temp = d;
			d = c;
			c = b;
			const unsigned int v = a + f + k[i] + w[g];
			b = b + ((v << r[i]) | (v >> (32-r[i])));
			a = temp;
		}
		h[0] += a;
		h[1] += b;
		h[2] += c;
		h[3] += d;
	}
}
