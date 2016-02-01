dnl m4/mpria_setup.m4 -- M4 macro processor include script
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
AC_DEFUN([MPRIA_AC_PKG_MPRIA_SETUP],
[
AC_REQUIRE([AM_INIT_AUTOMAKE])
dnl AC_REQUIRE([AC_CANONICAL_HOST])
dnl
dnl See `Versioning' in the libtool manual for details,
dnl in particular subsection 7.3 `Updating library version information'.
dnl
MPRIA_VERSION_MAJOR=${PACKAGE_VERSION%%.*}
MPRIA_VERSION_MINOR=${PACKAGE_VERSION#*.}
MPRIA_VERSION_MINOR=${MPRIA_VERSION_MINOR%%.*}
MPRIA_VERSION_MICRO=${PACKAGE_VERSION%-*}
MPRIA_VERSION_MICRO=${MPRIA_VERSION_MICRO%~*}
MPRIA_VERSION_MICRO=${MPRIA_VERSION_MICRO#*.}
MPRIA_VERSION_MICRO=${MPRIA_VERSION_MICRO#*.}
MPRIA_VERSION_NANO=0
MPRIA_VERSION_EXTRA="${PACKAGE_VERSION}-"
MPRIA_VERSION_EXTRA=${MPRIA_VERSION_EXTRA#*-}
MPRIA_VERSION_EXTRA=${MPRIA_VERSION_EXTRA%-*}
if test "x${MPRIA_VERSION_EXTRA}" != "x" ;then
	MPRIA_VERSION_EXTRA=\"-${MPRIA_VERSION_EXTRA}\"
else
	MPRIA_VERSION_EXTRA="${PACKAGE_VERSION}~"
	MPRIA_VERSION_EXTRA=${MPRIA_VERSION_EXTRA#*~}
	MPRIA_VERSION_EXTRA=${MPRIA_VERSION_EXTRA%~*}
	if test "x${MPRIA_VERSION_EXTRA}" != "x" ;then
		MPRIA_VERSION_EXTRA=\"~${MPRIA_VERSION_EXTRA}\"
	else
		MPRIA_VERSION_EXTRA=\"\"
	fi
fi
dnl
MPRIA_LT_INFO_CURRENT="$(expr ${MPRIA_VERSION_MAJOR} + ${MPRIA_VERSION_MINOR})"
MPRIA_LT_INFO_REVISION=${MPRIA_VERSION_MICRO}
MPRIA_LT_INFO_AGE=${MPRIA_VERSION_MINOR}
MPRIA_LT_INFO=${MPRIA_LT_INFO_CURRENT}:${MPRIA_LT_INFO_REVISION}:${MPRIA_LT_INFO_AGE}
dnl
AC_SUBST(MPRIA_VERSION_MAJOR)
AC_SUBST(MPRIA_VERSION_MINOR)
AC_SUBST(MPRIA_VERSION_MICRO)
AC_SUBST(MPRIA_VERSION_NANO)
AC_SUBST(MPRIA_VERSION_EXTRA)
dnl AC_SUBST(MPRIA_LT_INFO_CURRENT)
dnl AC_SUBST(MPRIA_LT_INFO_REVISION)
dnl AC_SUBST(MPRIA_LT_INFO_AGE)
AC_SUBST(MPRIA_LT_INFO)
])
dnl eof
