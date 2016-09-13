ACLOCAL_AMFLAGS = -I m4 

libdir = $(prefix)/lib
lib_LTLIBRARIES = libinterface_process_data_inspection.la
BUILT_SOURCES = ln_messages.h
CLEANFILES = ln_messages.h

libinterface_process_data_inspection_la_SOURCES  = interface_process_data_inspection.cpp
libinterface_process_data_inspection_la_CXXFLAGS = -fno-strict-aliasing -Wall -I$(top_srcdir)/src -I$(top_builddir) @ROBOTKERNEL_CFLAGS@  @LIBSTRING_UTIL_CFLAGS@ @YAML_CPP_CFLAGS@
libinterface_process_data_inspection_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

VPATH = $(srcdir):$(top_srcdir)/share/ln/message_definitions

LN_MESSAGES = robotkernel/process_data_inspection/in \
			  robotkernel/process_data_inspection/out

ln_messages.h: Makefile $(LN_MESSAGES)
	@echo creating ln_messages.h
	@LN_GENERATE@ -o $@ $(LN_MESSAGES)
	touch $@

install-exec-hook:
	mkdir -p $(prefix)/share
	-cp -rf $(top_srcdir)/share/* $(DESTDIR)$(prefix)/share/

