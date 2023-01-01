
# test executables
BUILDNAME = $(BUILDDIR)/panacea
# source files
SOURCE = $(wildcard $(SRCDIR)/*.cpp) # wildcard get all files with ext cpp

# CXX - reference to the system C++ compiler
# LDFLAGS - linker flags
# CXXFLAGS - C++ compiler flags
# CPPFLAGS C/C++ preprocessor flags

$(BUILDNAME): $(SOURCE) FORCE
	$(CXX)	$(CPPFLAGS) $(CXXFLAGS) -o $(BUILDNAME) $(SOURCE)