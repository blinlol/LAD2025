SUBDIRS = src po tests doc
EXTRA_DIST = autogen.sh po/greeter.pot po/ru.po po/Makevars po/POTFILES.in po/LINGUAS

MAINTAINERCLEANFILES = \
	Makefile.in \
	configure \
	config.h.in \
	config.log \
	config.status \
	autom4te.cache \
	libtool

clean-local:
	rm -rf autom4te.cache
