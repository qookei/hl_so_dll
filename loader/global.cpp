#include "global.hpp"
#include "pe_loader.hpp"

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static pe *_pe_so;

void global_pe_load(const char *name) {
	int fd = open(name, O_RDONLY);
	if (fd < 0) {
		perror("global_pe_load(): failed to open");
		abort();
	}

	struct stat s;
	if (fstat(fd, &s)) {
		perror("global_pe_load(): failed to stat");
		abort();
	}

	void *data = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (data == MAP_FAILED) {
		perror("global_pe_load(): failed to mmap file");
		abort();
	}

	close(fd);

	_pe_so = new pe;
	_pe_so->load(data);

	if (munmap(data, s.st_size)) {
		perror("global_pe_load(): failed to munmap file");
		abort();
	}
}

void *global_pe_sym(const char *name) {
	if (!_pe_so) {
		printf("global_pe_sym(): no dll loaded\n");
		abort();
	}

	return _pe_so->sym(name);
}
