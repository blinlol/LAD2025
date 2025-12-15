bin_PROGRAMS = greeter
greeter_SOURCES = hello.c strutil.c
AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\" \
	-DBUILD_LOCALEDIR=\"$(abs_top_builddir)/po\" \
	-DTEXTDOMAIN=\"greeter\"
greeter_LDADD = $(INTL_LIBS)
