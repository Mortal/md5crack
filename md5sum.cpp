#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "md5.h"

using namespace std;

int main() {
	string prev;
	string line;
	md5string s(line);
	while (getline(cin, line)) {
		size_t i = 0;
		while (i < line.size() && i < prev.size() && line[i] == prev[i]) i++;
		s.set_suffix(line.c_str()+i, i, line.size()-i);
		cout << hash_hex(s.md5().result()) << endl;
		prev = line;
	}
	return 0;
}
// vim:set ts=4 sw=4 sts=4 noet:
