#include "pe_loader.hpp"

#include <iostream>
#include <cstring>
#include <strings.h>
#include <cassert>

#include <sys/mman.h>

#include "fake_kernel32.hpp"

uint32_t pe::get_section_virt(const char *name) {
	for (size_t i = 0; i < _hdr->n_section; i++) {
		if (!strncmp(_hdr->sections[i].name, name, 8))
			return _hdr->sections[i].vaddr;
	}

	__builtin_trap();
}

void pe::reloc() {
	printf("pe::reloc(): image base = %08x, size = %u\n", _hdr->image_base, _hdr->image_size);

	size_t align_size = (_hdr->image_size + 0xFFF) & ~0xFFF;

	printf("pe::reloc(): aligned size = %lu\n", align_size);

	_image = mmap(
		(void *)_hdr->image_base,
		align_size,
		PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);

	if (_image == MAP_FAILED) {
		perror("mmap failed");
		abort();
	}

	memcpy(_image, _file, _hdr->headers_size);
	for (size_t i = 0; i < _hdr->n_section; i++) {
		auto section = _hdr->sections[i];
		memcpy(rva_abs(section.vaddr), file_abs(section.raw_ptr),
				section.raw_size);
	}

	printf("pe::reloc(): relocated\n");
}

void pe::load_imports() {
	import_dir_table *idata = (import_dir_table *)rva_abs(_hdr->import_table.vaddr);

	for (size_t i = 0; idata[i].import_lookup_rva; i++) {
		auto import = idata[i];
		const char *name = (const char *)rva_abs(import.name_rva);

		if (strcasecmp(name, "KERNEL32.dll")) {
			printf("pe::load_imports(): we want to import from '%s'\n", name);
			printf("pe::load_imports(): imports from other DLLs unsupported\n");
			printf("pe::load_imports(): only KERNEL32.dll imports and functions are implemented\n");
			abort();
		}

		uint32_t *lookups = (uint32_t *)rva_abs(import.import_lookup_rva);
		uint32_t *addrs = (uint32_t *)rva_abs(import.import_address_rva);

		if (!lookups[0])
			printf("pe::load_imports(): we want to import from '%s', but there are no lookup entries\n", name);

		for (size_t j = 0; lookups[j]; j++) {
			auto lookup = lookups[j];
			if (lookup & 0x80000000) {
				printf("pe::load_imports(): ordinal imports not supported\n");
				abort();
			}

			hint_name_table_entry *item = (hint_name_table_entry *)rva_abs(lookup);
			if ((addrs[j] = lookup_fake_symbol(item->name)))
				printf("pe::load_imports(): imported our FAKE_%s, which is at %#x\n", item->name, addrs[j]);
			else
				printf("pe::load_imports(): failed to import '%s' (FAKE_%s not implemented?)\n", item->name, item->name);
		}
	}
	printf("pe::load_imports(): done\n");
}

void pe::load_exports() {
	export_dir_table edata = *(export_dir_table *)rva_abs(_hdr->export_table.vaddr);

	uint32_t *exports = (uint32_t *)rva_abs(edata.export_addr_tab_rva);
	uint32_t *name_ptrs = (uint32_t *)rva_abs(edata.name_ptr_rva);
	uint16_t *ordinals = (uint16_t *)rva_abs(edata.ordinal_table_rva);

	for (size_t i = 0; i < edata.n_name_ptr; i++) {
		const char *name = (const char *)rva_abs(name_ptrs[i]);

		uint16_t ordinal = ordinals[i] + 1;
		uint32_t rva = exports[ordinal - edata.ordinal_base];

		uint32_t address = (uint32_t)rva_abs(rva);

		printf("pe::load_exports(): '%s' exported to %#8x\n", name, address);
		_export_symbols[name] = address;
	}

	printf("pe::load_exports(): done\n");
}

void *pe::rva_abs(uintptr_t rva) {
	return (void *)((uintptr_t)_image + rva);
}

void *pe::file_abs(uintptr_t ptr) {
	return (void *)((uintptr_t)_file + ptr);
}

void pe::load(void *file) {
	_file = file;

	uint32_t pe_off = *(uint32_t *)((uintptr_t)file + 0x3C);
	_hdr = (pe_header *)((uintptr_t)file + pe_off);

	reloc();
	load_imports();
	load_exports();

	printf("pe::load(): done, calling foo(42)\n");

	auto foo_ptr = (int(*)(int))_export_symbols["foo"];
	int ret = foo_ptr(42);

	printf("pe::load(): foo(42) returned %d\n", ret);
}
