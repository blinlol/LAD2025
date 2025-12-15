DOMAIN = greeter
LINGUAS = ru
localedir = $(datarootdir)/locale

EXTRA_DIST = greeter.pot ru.po Makevars POTFILES.in LINGUAS

MSGFMT = @MSGFMT@
MOFILES = $(LINGUAS:%=$(builddir)/%/LC_MESSAGES/$(DOMAIN).mo)

all-local: $(MOFILES)

$(builddir)/%/LC_MESSAGES/$(DOMAIN).mo: %.po
	$(AM_V_at)$(MKDIR_P) $(dir $@)
	$(AM_V_GEN)$(MSGFMT) -o $@ $<

install-data-local: $(MOFILES)
	@for lang in $(LINGUAS); do \
		dir=$(DESTDIR)$(localedir)/$$lang/LC_MESSAGES; \
		$(MKDIR_P) $$dir; \
		$(INSTALL_DATA) $(builddir)/$$lang/LC_MESSAGES/$(DOMAIN).mo $$dir/$(DOMAIN).mo; \
	done

CLEANFILES = $(MOFILES)
