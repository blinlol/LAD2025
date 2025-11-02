bin_PROGRAMS = rhasher
rhasher_SOURCES = rhasher.c
rhasher_CFLAGS = -I$(top_srcdir)/src
rhasher_LDADD = $(RHASH_LIBS) $(READLINE_LIBS)

# Условные флаги компиляции
if HAVE_READLINE
rhasher_CFLAGS += -DHAVE_READLINE
endif

clean-local:
	rm -rf *.o *.lo *.la .deps .libs

distclean-local:
	rm -f rhasher