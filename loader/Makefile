OBJS = main.o pe_loader.o fake_kernel32.o global.o
TARGET = loader_test

CXXFLAGS = -m32 -static -std=c++17 -g
CXXFLAGS += -DFAKE_KERNEL32_NO_ABORT

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm $(TARGET)
	rm $(OBJS) 
