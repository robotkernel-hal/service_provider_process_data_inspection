ACLOCAL_AMFLAGS = -I m4 

lib_LTLIBRARIES = libservice_provider_process_data_inspection.la

extraincludedir = $(includedir)/service_provider/process_data_inspection
extrainclude_HEADERS = include/service_provider/process_data_inspection/base.h

libservice_provider_process_data_inspection_la_SOURCES  = provider.cpp
libservice_provider_process_data_inspection_la_CXXFLAGS = --std=c++11 -fno-strict-aliasing -Wall \
												   -I$(top_srcdir)/src -I$(top_builddir) -I$(srcdir)/include \
												   @ROBOTKERNEL_CFLAGS@ 
libservice_provider_process_data_inspection_la_LDFLAGS  = -Wall -release $(PACKAGE_VERSION)

