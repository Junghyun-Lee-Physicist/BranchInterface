# Detect OS for shared library extension and flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # macOS settings
    SHARED_EXT  := dylib
    SHARED_FLAG := -dynamiclib
else
    # Linux settings
    SHARED_EXT  := so
    SHARED_FLAG := -shared
endif

# Directories
SRCDIR  := src
INCDIR  := include
OBJDIR  := obj
LIBDIR  := lib

# ROOT flags
ROOT_CFLAGS := $(shell root-config --cflags)
ROOT_LIBS   := $(shell root-config --libs)

# Compiler and flags
CC      := g++
CFLAGS  := -Wall -O2 -fPIC -I$(INCDIR) $(ROOT_CFLAGS)

# Archiver for static libraries
AR      := ar
ARFLAGS := rcs

# Base library name
LIBNAME := BranchInterface

# Filename patterns
STATIC_LIB := $(LIBDIR)/lib$(LIBNAME).a
SHARED_LIB := $(LIBDIR)/lib$(LIBNAME).$(SHARED_EXT)

# Source and object files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Build type: static or shared (default: static)
LIBTYPE ?= static

# Default target: build library of chosen type
all: $(LIBTYPE)
	@echo "=== Finished building $(LIBTYPE) library ==="

# Static library target
static: $(STATIC_LIB)
	@echo "=== Built static library: $(STATIC_LIB) ==="
	@echo "=== Cleaning object directory ==="
	@rm -rf $(OBJDIR)

$(STATIC_LIB): $(OBJS)
	@echo "=== Archiving static library: $(STATIC_LIB) ==="
	@mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $(OBJS)

# Shared library target
shared: $(SHARED_LIB)
	@echo "=== Built shared library: $(SHARED_LIB) ==="
	@echo "=== Cleaning object directory ==="
	@rm -rf $(OBJDIR)

$(SHARED_LIB): $(OBJS)
	@echo "=== Linking shared library: $(SHARED_LIB) ==="
	@mkdir -p $(LIBDIR)
	$(CC) $(SHARED_FLAG) -o $@ $(OBJS) $(ROOT_LIBS)

# Compile sources to objects
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

# Create object directory
$(OBJDIR):
	@echo "Creating object directory: $(OBJDIR)"
	@mkdir -p $(OBJDIR)

# Clean up build artifacts
clean:
	@echo "Cleaning all build artifacts"
	@rm -rf $(OBJDIR) $(LIBDIR)
	@echo "Clean complete."

.PHONY: all static shared clean
