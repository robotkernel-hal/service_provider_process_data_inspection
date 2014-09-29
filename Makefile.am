ACLOCAL_AMFLAGS = -I m4 

libdir = $(prefix)/lib
lib_LTLIBRARIES = libinterface_process_data_inspection.la
BUILT_SOURCES = ln_messages.h
CLEANFILES = ln_messages.h

libinterface_process_data_inspection_la_SOURCES  = interface_process_data_inspection.cpp
libinterface_process_data_inspection_la_CXXFLAGS = -fno-strict-aliasing -Wall -I$(top_srcdir)/src \
										   -I$(top_builddir) @ROBOTKERNEL_CFLAGS@ 
libinterface_process_data_inspection_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

VPATH = $(srcdir):$(srcdir)/message_definitions

LN_MESSAGES = \
			  robotkernel/process_data_inspection/in \
			  robotkernel/process_data_inspection/out

ln_messages.h: Makefile $(LN_MESSAGES)
	@echo creating ln_messages.h
	@LN_GENERATE@ -o $@ $(LN_MESSAGES)
	touch $@

install-exec-hook:
	cp -r $(srcdir)/share $(prefix)
	mkdir -p $(prefix)/share/message_definitions
	cp -r $(srcdir)/message_definitions/* $(prefix)/share/message_definitions/
