AC_PREREQ([2.69])
AC_INIT([greeter], [1.0], [sdcs@sdcs.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([src/hello.c])
AC_CONFIG_HEADERS([config.h])

AC_LANG([C])
AC_PROG_CC

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4], [], [AC_MSG_ERROR([check library not found])])

AC_PATH_PROG([HELP2MAN], [help2man], [no])
AS_IF([test "x$HELP2MAN" = "xno"], [AC_MSG_ERROR([help2man not found; please install it])])

AC_PATH_PROG([MSGFMT], [msgfmt], [no])
AS_IF([test "x$MSGFMT" = "xno"], [AC_MSG_ERROR([msgfmt not found; please install gettext tools])])

AC_CHECK_HEADERS([libintl.h])
AC_CHECK_LIB([intl], [gettext], [INTL_LIBS="-lintl"], [INTL_LIBS=""])
AC_SUBST([INTL_LIBS])

AC_SUBST([CHECK_CFLAGS])
AC_SUBST([CHECK_LIBS])

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile tests/Makefile doc/Makefile])
AC_OUTPUT
