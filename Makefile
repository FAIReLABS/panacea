package = panacea
version = 0.0.0.9000

BUILDDIR = bin
INCDIRS = include
SRCDIR = src
TESTDIR = test

CXXFLAGS += $(INCDIRS:%=-I%) -std=c++1y

include src/Makefile
include test/Makefile

.PHONY: all clean FORCE

all panacea: $(BUILDNAME)

test: $(TESTNAME)

# make sure to include build directory
FORCE:
	@mkdir $(BUILDDIR)

clean: 
	$(RM) $(BUILDDIR)/*.d $(BUILDDIR)/*.o $(ARCHIVENAME) $(TESTNAME) $(BUILDNAME)