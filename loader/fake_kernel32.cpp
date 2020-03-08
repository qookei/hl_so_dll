#include "fake_kernel32.hpp"
#include "util.hpp"
#include <iostream>

static symbol_map _fake_kernel32_symbols;

void register_fake_symbols() {
	_fake_kernel32_symbols["TlsFree"] = (uint32_t)&FAKE_TlsFree;
}

uint32_t lookup_fake_symbol(const char *name) {
	if (!_fake_kernel32_symbols.size())
		register_fake_symbols();

	auto ptr = _fake_kernel32_symbols[name];
	if (!ptr) {
#ifdef FAKE_KERNEL32_NO_ABORT
		return 0;
#endif
		printf("lookup_fake_symbol(): '%s' is not implemented\n", name);
		abort();
	}

	return ptr;
}

// --------------------------------------------------------------------

DLL_FAKE void FAKE_TlsFree(uint32_t foo) {
	printf("FAKE_TlsFree(): called with %u\n", foo);
}
