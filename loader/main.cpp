#include <iostream>

#include "global.hpp"
#include "util.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("loader_test: missing argument <file name>\n");
		return 1;
	}

	global_pe_load(argv[1]);

	printf("loader_test: calling foo(1337)\n");

	auto foo_ptr = (int(STDCALL*)(int))global_pe_sym("foo@4");
	int ret = foo_ptr(1337);

	printf("loader_test: foo(1337) returned %d\n", ret);


	std::cout << "hello world\n";
}
