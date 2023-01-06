package = panacea
version = 0.0.0.9000

# package structure
BUILDDIR = bin
INCDIRS = include
SRCDIR = src
TESTDIR = test

# paths
prefix = /usr/local

# compiler vars
CXXFLAGS += $(INCDIRS:%=-I%) -std=c++1y

include src/Makefile
include test/Makefile

# build binary
all panacea: $(BUILDNAME)

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
	$(RM) $(BUILDDIR)/*.d $(BUILDDIR)/*.o $(ARCHIVENAME) $(TESTNAME) $(BUILDNAME)

.PHONY: all clean FORCE