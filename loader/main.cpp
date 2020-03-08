#include <iostream>

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "pe_loader.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("loader_test: missing argument <file name>\n");
		return 1;
	}

	const char *name = argv[1];

	int fd = open(name, O_RDONLY);

	struct stat s;
	fstat(fd, &s);

	void *data = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);

	pe _pe{};
	_pe.load(data);

	std::cout << "hello world\n";
}
