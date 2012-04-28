#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

void md5(char * sm, size_t l, char * output);

int main() {
	string line;
	char output[16];
	while (getline(cin, line)) {
		char * c = strdup(line.c_str());
		printf("%s\n", c);
		md5(c, line.size(), output);
		free(c);
		fwrite(output, 1, 16, stdout);
	}
	return 0;
}

