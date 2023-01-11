package = panacea
version = 0.0.0.9000

# package structure
BUILDDIR = bin
INCDIRS = include
SRCDIR = src
TESTDIR = test

# paths
prefix = /usr/local

# CXX - reference to the system C++ compiler
# LDFLAGS - linker flags
# -lboost_unit_test_framework for unit testing
# CXXFLAGS - C++ compiler flags
# -std=c++1y for new standard c++
# CPPFLAGS C/C++ preprocessor flags
# -g needed for debugging with gdb based debuggers
# -Wall shows almost all compile warnings
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

# compiler vars
CXXFLAGS += $(INCDIRS:%=-I%) -std=c++1y
# linker flags for boost
LDFLAGS += $(ARCHIVENAME) -lboost_unit_test_framework

# source files
SOURCE = $(wildcard $(SRCDIR)/*.cpp) # wildcard get all files with ext cpp

# objects to build test
OBJS = $(addprefix $(BUILDDIR)/, $(patsubst %.cpp, %.o, $(notdir $(wildcard $(SRCDIR)/*.cpp))))
TESTOBJS = $(addprefix $(BUILDDIR)/, $(patsubst %.cpp, %.o, $(notdir $(wildcard $(TESTDIR)/*.cpp))))

# executables
ARCHIVENAME = $(BUILDDIR)/panacea.a
TESTNAME = $(BUILDDIR)/test-panacea
BUILDNAME = $(BUILDDIR)/panacea
DEBUGNAME = $(BUILDDIR)/debug-panacea

include src/Makefile
include test/Makefile

# build binary
all panacea: $(BUILDNAME)

# debug binary
debug: $(DEBUGNAME)

# unit testing
test: $(TESTNAME)

# installation
install: 
	cp $(BUILDNAME) $(prefix)/bin
	chown root:root $(prefix)/$(BUILDNAME)
	chmod +x $(prefix)/$(BUILDNAME)

# make sure to include build directory
FORCE:
	-mkdir -p $(BUILDDIR)

clean: 
	$(RM) $(BUILDDIR)/*.d $(BUILDDIR)/*.o $(ARCHIVENAME) $(TESTNAME) $(DEBUGNAME)

.PHONY: all clean FORCE