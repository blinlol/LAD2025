SUBDIRS = src
dist_doc_DATA = README
EXTRA_DIST = autogen.sh

clean-local:
	rm -rf *.cache *~ *.log *.status *.dirstamp

distclean-local:
	rm -rf autom4te.cache
	rm -f config.h config.h.in~ config.log config.status configure.lineno
	rm -f Makefile.in aclocal.m4 compile depcomp install-sh missing
	rm -f src/Makefile.in 

maintainer-clean-local:
	rm -f configure config.h.in
