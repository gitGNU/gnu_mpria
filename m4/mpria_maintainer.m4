dnl m4/mpria_maintainer.m4 -- M4 macro processor include script
dnl MPRIA - GNU Multi-Precision Rational Interval Arithmetic Library
dnl Copyright (C) 2009-2016  Jerome Benoit <jgmbenoit@rezozer.net>
dnl
dnl This file is part of the GNU MPRIA Library.
dnl
dnl The GNU MPRIA Library is free software: you can redistribute it and/or modify it
dnl under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl The GNU MPRIA Library is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with the GNU MPRIA Library.  If not, see <http://www.gnu.org/licenses/>.
dnl
AC_DEFUN([MPRIA_AC_MAINTAINER_PROG_GAP],[dnl
AC_REQUIRE([AM_MAINTAINER_MODE])dnl
AS_IF([test x"$USE_MAINTAINER_MODE" = xyes],[dnl then
AC_MSG_NOTICE(********* MAINTAINER MODE *********)
AC_PATH_PROG(GAP,gap,/usr/bin/gap)
AC_MSG_NOTICE(***********************************)
],[:])])dnl
dnl
AC_DEFUN([MPRIA_AX_MAINTAINER_APPEND_COMPILE_FLAGS],[dnl
AC_REQUIRE([AM_MAINTAINER_MODE])dnl
AS_IF([test x"$USE_MAINTAINER_MODE" = xyes],[dnl then
AC_MSG_NOTICE(********* MAINTAINER MODE *********)
AX_APPEND_COMPILE_FLAGS(-Werror)
AX_APPEND_COMPILE_FLAGS(-Wall)
AX_APPEND_COMPILE_FLAGS(-W)
AX_APPEND_COMPILE_FLAGS(-Wno-unused-function)
AX_APPEND_COMPILE_FLAGS(-Wno-unused-parameter)
AX_APPEND_COMPILE_FLAGS(-Wuninitialized)
AX_APPEND_COMPILE_FLAGS(-Wmissing-prototypes)
AX_APPEND_COMPILE_FLAGS(-Wmissing-declarations)
AX_APPEND_COMPILE_FLAGS(-Wconversion)
AX_APPEND_COMPILE_FLAGS(-Wno-shadow)
AX_APPEND_COMPILE_FLAGS(-Wpointer-arith)
AX_APPEND_COMPILE_FLAGS(-Wformat)
AX_APPEND_COMPILE_FLAGS(-Wdisabled-optimization)
AC_MSG_NOTICE(***********************************)
],[:])])dnl
dnl eof
