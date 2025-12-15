man_MANS = greeter.1

CLEANFILES = $(man_MANS)

# Generate manpage from the built greeter binary
$(man_MANS): $(top_builddir)/src/greeter$(EXEEXT)
	LC_ALL=C $(HELP2MAN) --no-info --name "Simple greeter program" --output=$@ $<
