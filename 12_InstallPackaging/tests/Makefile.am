AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CFLAGS = $(CHECK_CFLAGS)

check_PROGRAMS = test_strutil
TESTS = $(check_PROGRAMS)

TESTS_ENVIRONMENT = GREETER_LOCALEDIR=$(abs_top_builddir)/po

test_strutil_SOURCES = test_strutil.c $(top_srcdir)/src/strutil.c
test_strutil_LDADD = $(CHECK_LIBS)

CLEANFILES = *.log *.trs
