#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([puDatatypes], [4.0.0], [diana@met.no])
AM_INIT_AUTOMAKE
METNO_SET_VERSION_INFO

AC_CONFIG_SRCDIR([src/miLine.cc])
AC_CONFIG_HEADER([include/config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_LANG(C++)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$prefix/lib/pkgconfig
#PKG_CHECK_MODULES([parameter], [parameter])
#PKG_CHECK_MODULES([PUTOOLS], [putools])
AC_CHECK_HEADERS(parameter/parameter.h puTools/miString.h puTools/miTime.h,, AC_MSG_ERROR("missing header"))


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_CHECK_FUNCS([rint sqrt])

AC_CONFIG_FILES([Makefile
		pudatatypes.pc
		include/Makefile
		src/Makefile])
AC_OUTPUT
