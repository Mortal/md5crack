#ifndef MD5_H
#define MD5_H

#include <vector>
#include <algorithm>
#include <string>
#include <stdint.h>

#ifndef NDEBUG
#include <iostream>
#define DEBUG(msg) do { std::cout << "[DEBUG] " << msg << std::endl; } while (0)
#else
#define DEBUG(msg) do { } while (0)
#endif

void md5(char * sm, size_t l, uint32_t * h);
void md5chunk(unsigned char * buf, uint32_t * h);
std::string hash_hex(const uint32_t * h);

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

struct md5calculation {
	inline md5calculation() {
		h[0] = 0x67452301;
		h[1] = 0xefcdab89;
		h[2] = 0x98badcfe;
		h[3] = 0x10325476;
	}

	template <typename IT>
	inline void chunk(IT from) {
		uint32_t * w = reinterpret_cast<uint32_t *>(&*from);
		unsigned int aa[] = {h[0], h[1], h[2], h[3]};
		chunkpart<0>(w,aa);  chunkpart<1>(w,aa);  chunkpart<2>(w,aa);  chunkpart<3>(w,aa);
		chunkpart<4>(w,aa);  chunkpart<5>(w,aa);  chunkpart<6>(w,aa);  chunkpart<7>(w,aa);
		chunkpart<8>(w,aa);  chunkpart<9>(w,aa);  chunkpart<10>(w,aa); chunkpart<11>(w,aa);
		chunkpart<12>(w,aa); chunkpart<13>(w,aa); chunkpart<14>(w,aa); chunkpart<15>(w,aa);
		chunkpart<16>(w,aa); chunkpart<17>(w,aa); chunkpart<18>(w,aa); chunkpart<19>(w,aa);
		chunkpart<20>(w,aa); chunkpart<21>(w,aa); chunkpart<22>(w,aa); chunkpart<23>(w,aa);
		chunkpart<24>(w,aa); chunkpart<25>(w,aa); chunkpart<26>(w,aa); chunkpart<27>(w,aa);
		chunkpart<28>(w,aa); chunkpart<29>(w,aa); chunkpart<30>(w,aa); chunkpart<31>(w,aa);
		chunkpart<32>(w,aa); chunkpart<33>(w,aa); chunkpart<34>(w,aa); chunkpart<35>(w,aa);
		chunkpart<36>(w,aa); chunkpart<37>(w,aa); chunkpart<38>(w,aa); chunkpart<39>(w,aa);
		chunkpart<40>(w,aa); chunkpart<41>(w,aa); chunkpart<42>(w,aa); chunkpart<43>(w,aa);
		chunkpart<44>(w,aa); chunkpart<45>(w,aa); chunkpart<46>(w,aa); chunkpart<47>(w,aa);
		chunkpart<48>(w,aa); chunkpart<49>(w,aa); chunkpart<50>(w,aa); chunkpart<51>(w,aa);
		chunkpart<52>(w,aa); chunkpart<53>(w,aa); chunkpart<54>(w,aa); chunkpart<55>(w,aa);
		chunkpart<56>(w,aa); chunkpart<57>(w,aa); chunkpart<58>(w,aa); chunkpart<59>(w,aa);
		chunkpart<60>(w,aa); chunkpart<61>(w,aa); chunkpart<62>(w,aa); chunkpart<63>(w,aa);
		h[0] += aa[0];
		h[1] += aa[1];
		h[2] += aa[2];
		h[3] += aa[3];
	}

	template <int i>
	inline void chunkpart(uint32_t * w, unsigned int * aa) {
		chunkpart2<i/16, i%4>(w, aa, i);
	}

	template <int phase, int shift>
	inline void chunkpart2(uint32_t * w, unsigned int * aa, int i) {
		unsigned int & a = aa[(4-shift)%4];
		unsigned int & b = aa[(5-shift)%4];
		unsigned int & c = aa[(6-shift)%4];
		unsigned int & d = aa[(7-shift)%4];
		unsigned int f, g;
		switch (phase) {
		case 0:
			f = (b & c) | ((~b) & d);
			g = i;
			break;
		case 1:
			f = (d & b) | ((~d) & c);
			g = (5*i + 1) % 16;
			break;
		case 2:
			f = b ^ c ^ d;
			g = (3*i + 5) % 16;
			break;
		case 3:
			f = c ^ (b | (~d));
			g = (7*i) % 16;
			break;
		}
		const unsigned int v = a + f + k[i] + w[g];
		a = b + ((v << r[i]) | (v >> (32-r[i])));
	}

	inline const uint32_t * result() { return h; }

private:
	uint32_t h[4];
};

struct md5string {
	inline md5string(const char * m) {
		set_message(m, strlen(m));
	}
	inline md5string(const std::string & m) {
		set_message(m.c_str(), m.size());
	}
	inline md5string(const char * m, size_t l) {
		set_message(m, l);
	}
	inline void set_message(const char * src, size_t length) {
		messageLength = length;
		chunkCount = calculate_chunk_count(length);
		calculate_message_capacity();
		data.resize(chunkCount*CHUNKSZ);
		std::copy(src, src+length, data.begin());
		update_trailer();
		cachedCalculations = 0;
		calculations.resize(chunkCount);
	}
	inline void set_suffix(const char * src, size_t offset, size_t length) {
		if (offset == messageLength && length == 0) {
			DEBUG("Empty change");
			return;
		}
		if (offset+length <= messageCapacity) {
			std::copy(src, src+length, data.begin()+offset);
			invalidate_suffix(offset, offset+length);

			DEBUG("Replace " << length << " bytes at " << offset << " into buffer, msg len = " << messageLength << ", cached = " << cachedCalculations);
		} else {
			DEBUG("Reallocate buffer");
			size_t newChunkCount = calculate_chunk_count(offset+length);
			std::vector<char> newData(newChunkCount*CHUNKSZ);
			std::copy(data.begin(), data.begin()+offset, newData.begin());
			std::copy(src, src+length, newData.begin()+offset);
			data.swap(newData);
			chunkCount = newChunkCount;
			calculate_message_capacity();
			calculations.resize(chunkCount);
			invalidate_suffix(0, offset+length);
		}
	}

	inline void invalidate_suffix(size_t offset, size_t newLength) {
		cachedCalculations = std::min(cachedCalculations, offset/CHUNKSZ);
		if (newLength != messageLength) {
			messageLength = newLength;
			update_trailer();
		}
	}

	inline static size_t calculate_chunk_count(size_t messageLength) {
		return (messageLength+TRAILERSZ+CHUNKSZ-1)/CHUNKSZ;
	}

	inline void calculate_message_capacity() {
		messageCapacity = chunkCount*CHUNKSZ-TRAILERSZ;
	}

	std::vector<char> data;

	md5calculation md5() {
		DEBUG("calc " << chunkCount << " chunks");
		md5calculation & worker = calculations[chunkCount-1];
		if (cachedCalculations >= chunkCount) {
			DEBUG("Reuse cached calculation");
			return worker;
		}
		worker = cachedCalculations ? calculations[cachedCalculations-1] : md5calculation();
		size_t offset = cachedCalculations*CHUNKSZ;
		DEBUG(cachedCalculations << " cached calculations");
		for (size_t i = cachedCalculations; i < chunkCount; ++i) {
			worker.chunk(data.begin()+offset);
			if (i < chunkCount - 1) calculations[i] = worker;
			offset += CHUNKSZ;
		}
		cachedCalculations = chunkCount;
		return worker;
	}

private:
	size_t messageLength;
	size_t chunkCount;
	size_t messageCapacity;
	static const size_t TRAILERSZ = 9;
	static const size_t CHUNKSZ = 64;
	size_t cachedCalculations;
	std::vector<md5calculation> calculations;

	inline void update_trailer() {
		fill(data.begin()+messageLength, data.end(), 0);
		data[messageLength] = 0x80;
		uint64_t * p = reinterpret_cast<uint64_t *>(&(*(data.end()-8)));
		*p = messageLength*8;
	}
};

#endif // MD5_H
// vim:set ts=4 sw=4 sts=4 noet:
