#ifndef MD5_H
#define MD5_H

#include <stdint.h>

void md5(char * sm, size_t l, char * output);
void md5chunk(unsigned char * buf, uint32_t * h);

#endif // MD5_H
