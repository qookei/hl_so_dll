#pragma once

#include <stdint.h>
#include <stddef.h>

#include "util.hpp"

void register_fake_symbols();
uint32_t lookup_fake_symbol(const char *name);

DLL_FAKE void FAKE_TlsFree(uint32_t);
