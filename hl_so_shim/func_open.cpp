#include "func_open.hpp"
#include "../loader/global.hpp"

#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>

static bool dll_ready = false;
static bool so_ready = false;

static void *so_handle = nullptr;

#ifndef HL_DLL_PATH
#define HL_DLL_PATH "./hl.dll"
#endif

#ifndef HL_SO_PATH
#define HL_SO_PATH "./hl.so"
#endif

#define STR__(x) #x
#define STR(x) STR__(x)

void *func_open(const char *so_name, const char *dll_name) {
	void *result = nullptr;

	if (dll_name) {
		if (!dll_ready) {
			global_pe_load(STR(HL_DLL_PATH));
			dll_ready = true;
		}
		result = global_pe_sym(dll_name);

		if (result) {
			fprintf(stderr, "func_open(): found '%s' in hl.dll\n", dll_name);
		} else {
//			fprintf(stderr, "func_open(): '%s' not found in hl.dll\n", dll_name);
		}
	}

	if (!result && so_name) {
		if (!so_ready) {
			so_handle = dlopen(STR(HL_SO_PATH), RTLD_LAZY);

			if (!so_handle) {
				fprintf(stderr, "func_open(): failed to dlopen '%s'\n", STR(HL_SO_PATH));
				abort();
			}

			so_ready = true;
		}

		result = dlsym(so_handle, so_name);

		if (result) {
//			fprintf(stderr, "func_open(): found '%s' in hl.so\n", so_name);
		} else {
//			fprintf(stderr, "func_open(): '%s' not found in hl.so\n", so_name);
		}
	}

	return result;
}

void __attribute__ ((constructor)) setup(void) {
	func_open("foo", "foo");
}

