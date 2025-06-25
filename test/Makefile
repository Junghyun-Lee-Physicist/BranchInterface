# === test/Makefile ===
# Usage:
#   source ../env_setup.sh [static|shared]
#   make

CXX        ?= g++
CXXFLAGS   ?= -Wall -O2
ROOT_CFLAGS := $(shell root-config --cflags)
ROOT_LIBS   := $(shell root-config --libs)

# Add ROOT include flags (for test.cpp)
CXXFLAGS  += $(ROOT_CFLAGS)

# We assume env_setup.sh has already exported:
#   CPLUS_INCLUDE_PATH  → include/
#   LIBRARY_PATH/LD_LIBRARY_PATH → lib/
# Link against BranchInterface and ROOT
LDLIBS    += -lBranchInterface $(ROOT_LIBS)

# Target executable
TARGET    := test_app
SRCS      := test.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	@echo "Compiling and linking $@"
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

clean:
	@echo "Cleaning up"
	@rm -f $(TARGET)

.PHONY: all clean
