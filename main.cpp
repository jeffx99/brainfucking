#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>

void errlog(char* err) {
	std::cerr << err << std::endl;
}

int main(int argc, char** argv) {
	char array[30000] = {0};
	char *ptr = array;

	if (argc != 2) {
		errlog("usage: brainfucking [filename]");
		return 0;
	}

	std::ifstream code(argv[1], std::ios::in | std::ios::ate);
	if (!code) {
		errlog("error: file not recognized");
		return 0;
	}
	
	std::streamsize size = code.tellg();
	code.seekg(0, std::ios::beg);

	std::vector<char> buffer((unsigned int)size);
	code.read(buffer.data(), size); 
	if (code.bad()){
		errlog("error: reading failed");
		return 0;
	}
	code.close();

	unsigned int index = 0;
	char command;
	while (index < size) {
		command = buffer[index];
		switch (command) {
		case '>':
			++ptr;
			break;
		case '<':
			--ptr;
			break;
		case '+':
			++*ptr;
			break;
		case '-':
			--*ptr;
			break;
		case '.':
			putchar(*ptr);
			break;
		case ',':
			*ptr = getchar();
			break;
		case '[':
			if (!*ptr) {
				int match = 1;
				while (match != 0) {
					++index;
					if (buffer[index] == '[')
						++match;
					if (buffer[index] == ']')
						--match;
				}
			}
			break;
		case ']':
			if (*ptr) {
				int match = -1;
				while (match != 0) {
					--index;
					if (buffer[index] == ']')
						--match;
					if (buffer[index] == '[')
						++match;
				}
			}
			break;
		default:
			break;
		}
		++index;
	}
}