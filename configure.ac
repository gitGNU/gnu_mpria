dnl Process this file with autoconf to produce a configure script.
AC_COPYRIGHT([
MPRIA - GNU Multi-Precision Rational Interval Arithmetic Library
Copyright (C) 2009-2016  Jerome Benoit <jgmbenoit@rezozer.net>

This file is part of the GNU MPRIA Library.

The GNU MPRIA Library is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The GNU MPRIA Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with the GNU MPRIA Library.  If not, see <http://www.gnu.org/licenses/>.
])
dnl
AC_PREREQ([2.69])
LT_PREREQ([2.4.2])

dnl
AC_INIT([GNU MPRIA],[0.7.3],
	[bug-mpria@gnu.org],[mpria],
	[http://www.gnu.org/software/mpria/])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/numtheory.c])
AC_CONFIG_HEADERS([src/mpria_config.h])
AM_INIT_AUTOMAKE([gnu])
AM_MAINTAINER_MODE([])

dnl Check for which system:
AC_CANONICAL_HOST

dnl Package setup:
MPRIA_AC_PKG_MPRIA_SETUP

dnl Checks for programs:
AC_PROG_SED
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

dnl Setup CC and CFLAGS wrt GMP
dnl (GNU MultiPrecision arithmetic library):
mpria_AC_PROG_PATH_GMP_CC([6.1.0])
####AC_PROG_CC
####AC_PROG_CPP

dnl LibTool setup:
LT_INIT

dnl Checks for programs used for maintenance:
MPRIA_AC_MAINTAINER_PROG_GAP

dnl Checks for linker script support:
gl_LD_VERSION_SCRIPT

dnl Check for the math library:
LT_LIB_M

dnl Checks for header files:
AC_CHECK_HEADERS([stddef.h string.h])
AC_CHECK_HEADERS([limits.h])dnl self-tests

dnl Checks for typedefs, structures, and compiler characteristics:
AC_C_INLINE
AC_TYPE_SIZE_T

dnl Checks for library functions:
AC_CHECK_FUNCS([atexit strchr])
AC_CHECK_FUNCS([strtol])dnl self-tests

dnl Append drastic compiler options:
MPRIA_AX_MAINTAINER_APPEND_COMPILE_FLAGS

dnl Check for valgrind (self-tests):
gl_VALGRIND_TESTS

dnl Generate:
AC_CONFIG_FILES([
	src/mpria.h
	Makefile
	src/Makefile
	tests/Makefile
	doc/Makefile
	examples/Makefile
	])
AC_OUTPUT

dnl eof
