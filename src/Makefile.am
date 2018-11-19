# Build the ROSE-based tools
include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs

EXTRA_DIST = 

# install the tools in 'bin'
bin_SCRIPTS = 

AM_CPPFLAGS = $(ROSE_INCLUDES)
AM_LDFLAGS = $(LIBS_WITH_RPATH) $(ROSE_LIBS)

bin_PROGRAMS = moveDeclarationToInnermostScope voprotector

moveDeclarationToInnermostScope_SOURCES = moveDeclarationToInnermostScope.C

voprotector_SOURCES = voprotector.C typedvalue.C voencoder.C sequencevoencoder.C notvoencoder.C minusvoencoder.C intvoencoder.C returnvoencoder.C jumpvoencoder.C conditionvoencoder.C ifthenelsevoencoder.C pntrderefvoencoder.C addressofvoencoder.C assignvoencoder.C varrefvoencoder.C vardeclvoencoder.C printfvoencoder.C rootvoencoder.C virtualizationobfuscationprotector.C subtractvoencoder.C stringvoencoder.C strcmpvoencoder.C addvoencoder.C multiplyvoencoder.C dividevoencoder.C

$(voprotector_OBJECTS): rose.h.gch

rose.h.gch: $(top_srcdir)/src/rose.h
	$(AM_V_CXX)$(CXXCOMPILE) -c -o $@ $<

