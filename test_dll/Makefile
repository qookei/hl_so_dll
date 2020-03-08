#clang -target i686-w64-mingw32 -shared test.c -o test.dll -nostdlib -lkernel32 -mwindows

SRC = test.c
TARGET = test.dll
CC = clang

CFLAGS = -nostdlib -lkernel32 -mwindows
CLANG_TARGET ?= i686-w64-mingw32

$(TARGET): $(SRC)
	$(CC) -target $(CLANG_TARGET) -o $@ -shared $^ $(CFLAGS)

.PHONY: clean

clean:
	rm $(TARGET)
