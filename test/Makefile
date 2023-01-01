# objects to build test
OBJS = $(addprefix $(BUILDDIR)/, $(patsubst %.cpp, %.o, $(notdir $(wildcard $(SRCDIR)/*.cpp))))
TESTOBJS = $(addprefix $(BUILDDIR)/, $(patsubst %.cpp, %.o, $(notdir $(wildcard $(TESTDIR)/*.cpp))))

# test executables
ARCHIVENAME = $(BUILDDIR)/panacea.a
TESTNAME = $(BUILDDIR)/test

# linker flags for boost
LDFLAGS += $(ARCHIVENAME) -lboost_unit_test_framework

# archiving
$(ARCHIVENAME): $(OBJS) FORCE
	$(AR) $(ARFLAGS) $@ $^

# build test
$(TESTNAME): $(TESTOBJS) $(ARCHIVENAME) FORCE
	$(CXX) -o $(TESTNAME) $^ $(LDFLAGS)

$(BUILDDIR)/%.o:$(SRCDIR)/%.cpp | $(BUILDDIR) FORCE
	$(COMPILE.cc) $< $(OUTPUT_OPTION)
	$(COMPILE.cc) -MM -MP -MT $@ $< -o $(BUILDDIR)/$*.d

$(BUILDDIR)/%.o:$(TESTDIR)/%.cpp | $(BUILDDIR) FORCE
	$(COMPILE.cc) $< $(OUTPUT_OPTION)
	$(COMPILE.cc) -MM -MP -MT $@ $< -o $(BUILDDIR)/$*.d
