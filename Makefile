include loader/Makefile
include hl_so_shim/Makefile

OBJS = $(PE_LOADER_OBJS) $(HL_SO_SHIM_OBJS)
TARGET = fake-hl.so

CXXFLAGS = -m32 -shared -std=c++17 -g

ORIGINAL_HL_SO ?= $(PWD)/hl.so
ORIGINAL_HL_DLL ?= $(PWD)/hl.dll

ifeq ($(IGNORE_MISSING_KERNEL32), 1)
CXXFLAGS += -DFAKE_KERNEL32_NO_ABORT
endif

CXXFLAGS += -DHL_DLL_PATH="$(ORIGINAL_HL_DLL)"
CXXFLAGS += -DHL_SO_PATH="$(ORIGINAL_HL_SO)"

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

include hl_so_shim/extra.mk

%.o: %.cpp %.d
	$(CXX) -c -o $@ $< $(CXXFLAGS)

%.d: %.cpp
	$(CXX) -M $< > $@ $(CXXFLAGS)

.PHONY: clean

clean:
	-rm $(OBJS)
	-rm $(HL_SO_SHIM_MISC)
	-rm $(TARGET)
