# archiving
$(ARCHIVENAME): $(OBJS) 
	$(AR) $(ARFLAGS) $@ $^

# build test
$(TESTNAME): $(TESTOBJS) $(ARCHIVENAME) 
	$(CXX) -o $(TESTNAME) $^ $(LDFLAGS)

$(BUILDDIR)/%.o:$(SRCDIR)/%.cpp | $(BUILDDIR) 
	$(COMPILE.cc) $< $(OUTPUT_OPTION)
	$(COMPILE.cc) -MM -MP -MT $@ $< -o $(BUILDDIR)/$*.d

$(BUILDDIR)/%.o:$(TESTDIR)/%.cpp | $(BUILDDIR) 
	$(COMPILE.cc) $< $(OUTPUT_OPTION)
	$(COMPILE.cc) -MM -MP -MT $@ $< -o $(BUILDDIR)/$*.d
