#pragma once

#define PACKED __attribute__((packed))
#define STDCALL __attribute__((stdcall))
#define C_LINKAGE extern "C"

#define DLL_FAKE C_LINKAGE STDCALL

#include <string.h>
#include <stddef.h>
#include <string_view>
#include <unordered_map>

struct cstr_hash {
	size_t operator()(const char *k) const {
		return std::hash<std::string_view>{}(k);
	}
};

struct cstr_comparator {
	bool operator()(const char *a, const char *b) const {
		return !strcmp(a, b);
	}
};

using symbol_map = std::unordered_map<const char *, uint32_t, cstr_hash, cstr_comparator>;
