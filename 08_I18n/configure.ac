AC_PREREQ([2.72])
AC_INIT([main], [1.0], [mail@mail.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.23)

AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

ALL_LINGUAS="ru"

AC_PROG_CC
AC_CHECK_HEADERS([libintl.h])

AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile po/Makefile.in src/Makefile])
AC_OUTPUT