#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT([puDatatypes], [3.0.0], [diana@met.no])
AM_INIT_AUTOMAKE
METNO_SET_VERSION_INFO

AC_CONFIG_SRCDIR([src/miLine.cc])
AC_CONFIG_HEADER([include/config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

AC_LANG_PUSH(C++)

# Checks for libraries.
AC_CXX_HAVE_STD
AC_CXX_HAVE_STL

# Make sure pkg-config also considers $prefix/lib/pkgconfig.
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$prefix/lib/pkgconfig

# Check for the parameter library.
PKG_CHECK_MODULES([parameter], [parameter])
METNO_CHECK_LIB([parameter], [main], , , , [$parameter_LIBS], 
                [the parameter package])

# Check for the puTools library.
PKG_CHECK_MODULES([puTools], [putools])
METNO_CHECK_LIB([puTools], [main], , , , [$puTools_LIBS], 
                [the puTools package])

# Checks for header files.
METNO_CHECK_HEADERS([parameter/parameter.h], , , , [$parameter_CFLAGS], 
                    [the parameter package])

METNO_CHECK_HEADERS([puTools/miString.h puTools/miTime], , , ,
                    [$puTools_CFLAGS], [the puTools package])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_CHECK_FUNCS([rint sqrt])

AC_LANG_POP(C++)

#making our own .pc file, checking that it is ok and forfilled
AC_CONFIG_FILES(pudatatypes.pc)
AC_OUTPUT

export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:.
PKG_CHECK_MODULES([own_dependencies], [${PACKAGE_TARNAME}])

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 src/Makefile])
AC_OUTPUT

