CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic
LDFLAGS := -pthread
TARGET := Thread_pool
SRCS := $(wildcard *.cpp)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
