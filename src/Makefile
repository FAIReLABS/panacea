
# test executables
BUILDNAME = $(BUILDDIR)/panacea
# source files
SOURCE = $(wildcard $(SRCDIR)/*.cpp) # wildcard get all files with ext cpp

# CXX - reference to the system C++ compiler
# LDFLAGS - linker flags
# CXXFLAGS - C++ compiler flags
# CPPFLAGS C/C++ preprocessor flags
# -g needed for debugging with gdb based debuggers
# -Wall shows almost all compile warnings
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

$(BUILDNAME): $(SOURCE) FORCE
	$(CXX)	$(CPPFLAGS) $(CXXFLAGS) -o $(BUILDNAME) $(SOURCE) -g -Wall