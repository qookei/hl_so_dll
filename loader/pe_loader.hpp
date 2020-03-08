#pragma once

#include <stdint.h>
#include <stddef.h>
#include "util.hpp"

struct PACKED data_dir {
	uint32_t vaddr;
	uint32_t size;
};

struct PACKED pe_section {
	char name[8];
	uint32_t vsize;
	uint32_t vaddr;
	uint32_t raw_size;
	uint32_t raw_ptr;
	uint32_t reloc_ptr;
	uint32_t line_no_ptr;
	uint16_t n_reloc;
	uint16_t n_line_no;
	uint32_t characteristics;
};

struct PACKED pe_header {
	uint32_t sig;
	uint16_t machine;
	uint16_t n_section;
	uint32_t timestamp;
	uint32_t symbol_table;
	uint32_t symbol_count;
	uint16_t optional_header_size;
	uint16_t characteristics;

	uint16_t magic;
	uint8_t major_linker_ver;
	uint8_t minor_linker_ver;
	uint32_t code_size;
	uint32_t data_size;
	uint32_t bss_size;
	uint32_t entry_point;
	uint32_t code_base;
	uint32_t data_base;

	uint32_t image_base;
	uint32_t section_align;
	uint32_t file_align;
	uint16_t major_os_ver;
	uint16_t minor_os_ver;
	uint16_t major_image_ver;
	uint16_t minor_image_ver;
	uint16_t major_sub_ver;
	uint16_t minor_sub_ver;
	uint32_t win32_ver;
	uint32_t image_size;
	uint32_t headers_size;
	uint32_t checksum;
	uint16_t subsystem;
	uint16_t dll_characteristics;
	uint32_t stack_reserve_size;
	uint32_t stack_commit_size;
	uint32_t heap_reserve_size;
	uint32_t heap_commit_size;
	uint32_t loader_lags;
	uint32_t n_rva_sizes;

	data_dir export_table;
	data_dir import_table;
	data_dir resource_table;
	data_dir exception_table;
	data_dir certificate_table;
	data_dir base_reloc_table;
	data_dir debug;
	data_dir architecture_data;
	data_dir global_ptr;
	data_dir tls_table;
	data_dir load_config_table;
	data_dir bound_import;
	data_dir import_address_table;
	data_dir delay_import_descriptor;
	data_dir clr_runtime_header;
	data_dir null_data_dir;

	pe_section sections[];
};

struct PACKED export_dir_table {
	uint32_t export_flags;
	uint32_t timestamp;
	uint16_t major_ver;
	uint16_t minor_ver;
	uint32_t name_rva;
	uint32_t ordinal_base;
	uint32_t addr_tab_ents;
	uint32_t n_name_ptr;
	uint32_t export_addr_tab_rva;
	uint32_t name_ptr_rva;
	uint32_t ordinal_table_rva;
};

struct PACKED import_dir_table {
	uint32_t import_lookup_rva;
	uint32_t timestamp;
	uint32_t forwarder_chain;
	uint32_t name_rva;
	uint32_t import_address_rva;
};

struct PACKED hint_name_table_entry {
	uint16_t hint;
	char name[];
};

struct pe {
	void load(void *file);
	void *sym(const char *name);
private:
	void reloc();
	void load_imports();
	void load_exports();

	void *rva_abs(uintptr_t rva);
	void *file_abs(uintptr_t ptr);

	void *_file;
	void *_image;
	pe_header *_hdr;

	symbol_map _export_symbols;
};

