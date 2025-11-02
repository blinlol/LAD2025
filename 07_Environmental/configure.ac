AC_INIT([rhasher], [1.0], [your-email@example.com])
AC_CONFIG_SRCDIR([src/rhasher.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects])

# Проверка компилятора C
AC_PROG_CC
AC_PROG_INSTALL

# Проверка обязательной библиотеки rhash
AC_CHECK_HEADER([rhash.h],,
    [AC_MSG_ERROR([rhash development headers not found])])
AC_CHECK_LIB([rhash], [rhash_library_init],
    [RHASH_LIBS="-lrhash"],
    [AC_MSG_ERROR([rhash library not found])])
AC_SUBST([RHASH_LIBS])

# Проверка опциональной библиотеки readline
AC_ARG_WITH([readline],
    [AS_HELP_STRING([--without-readline],
        [Build without readline support even if available])],
    [with_readline=$withval],
    [with_readline=check])

have_readline=no
if test "x$with_readline" != "xno"; then
    AC_CHECK_HEADER([readline/readline.h], [have_readline=yes], [have_readline=no])
    if test "x$have_readline" = "xyes"; then
        AC_CHECK_LIB([readline], [readline],
            [READLINE_LIBS="-lreadline"],
            [have_readline=no])
    fi
fi

# Условная компиляция для readline
AM_CONDITIONAL([HAVE_READLINE], [test "x$have_readline" = "xyes"])

if test "x$have_readline" = "xyes"; then
    AC_DEFINE([HAVE_READLINE], [1], [Define to 1 if readline is available])
    READLINE_LIBS="-lreadline"
else
    READLINE_LIBS=""
fi
AC_SUBST([READLINE_LIBS])

# Генерация файлов
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

# Информационное сообщение
echo
echo "Build configuration:"
echo "  rhash:    yes"
echo "  readline: $have_readline"
if test "x$have_readline" = "xyes"; then
    echo "    (use --without-readline to disable)"
fi
echo