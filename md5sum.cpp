#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "md5.h"

using namespace std;

int main() {
	string line;
	uint32_t h[4];
	while (getline(cin, line)) {
		char * c = strdup(line.c_str());
		md5(c, line.size(), h);
		free(c);
		cout << hash_hex(h) << endl;
	}
	return 0;
}
// vim:set ts=4 sw=4 sts=4 noet:
