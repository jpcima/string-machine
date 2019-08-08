CXX ?= g++
CXXFLAGS ?= -O2 -g
LDFLAGS ?=

CXXFLAGS += -std=c++11
CXXFLAGS += -Wall -Wextra
CXXFLAGS += -MD -MP
CXXFLAGS += -Isources

TARGET_MACHINE := $(shell $(CXX) -dumpmachine)
ifneq (,$(findstring mingw,$(TARGET_MACHINE)))
APP_EXT := .exe
endif

SOURCES := sources/layout.cpp sources/reader.cpp sources/main.cpp
OBJS := $(patsubst sources/%.cpp,build/%.o,$(SOURCES))

all: layout-tool$(APP_EXT)

clean:
	rm -f layout-tool$(APP_EXT)
	rm -rf build

layout-tool$(APP_EXT): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

build/%.o: sources/%.cpp
	@mkdir -p build
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: all clean

-include $(OBJS:%.o=%.d)
