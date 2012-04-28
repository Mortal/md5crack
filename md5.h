#ifndef MD5_H
#define MD5_H

#include <string>
#include <stdint.h>

void md5(char * sm, size_t l, uint32_t * h);
void md5chunk(unsigned char * buf, uint32_t * h);
std::string hash_hex(uint32_t * h);

#endif // MD5_H
