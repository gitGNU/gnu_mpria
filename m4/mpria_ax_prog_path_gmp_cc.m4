# mpria_ax_prog_path_gmp_cc.m4 serial 1
dnl m4/mpria_ax_prog_path_gmp_cc.m4 -- M4 macro processor include script
dnl MPRIA - GNU Multi-Precision Rational Interval Arithmetic Library
dnl Copyright (C) 2013-2016  Jerome Benoit <jgmbenoit@rezozer.net>
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
dnl Under Section 7 of GPL version 3, you are granted additional
dnl permissions described in the Autoconf Configure Script Exception,
dnl version 3.0, as published by the Free Software Foundation.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with the GNU MPRIA Library.  If not, see <http://www.gnu.org/licenses/>.
dnl

dnl _mpria_AC_PROG_PATH_GMP_CC_ARG_WITH
AC_DEFUN_ONCE([_mpria_AC_PROG_PATH_GMP_CC_ARG_WITH],[dnl
AC_ARG_WITH([gmp-prefix],
	[AS_HELP_STRING([--with-gmp-prefix=PREFIX],
		[specify prefix for the installed GMP [standard search prefixes]])],
	[gmp_config_prefix="$withval"],[gmp_config_prefix=""])
AC_ARG_WITH([gmp-include],
	[AS_HELP_STRING([--with-gmp-include=PATH],
		[specify directory for the installed GMP header file [standard search paths]])],
	[gmp_config_include_prefix="$withval"],[gmp_config_include_prefix=""])
AC_ARG_WITH([gmp-lib],
	[AS_HELP_STRING([--with-gmp-lib=PATH],
		[specify directory for the installed GMP library [standard search paths]])],
	[gmp_config_lib_prefix="$withval"],[gmp_config_lib_prefix=""])

	if test "x$gmp_config_include_prefix" = "x" ; then
		if test "x$gmp_config_prefix" != "x" ; then
			gmp_config_include_prefix="$gmp_config_prefix/include"
		fi
	fi
	if test "x$gmp_config_lib_prefix" = "x" ; then
		if test "x$gmp_config_prefix" != "x" ; then
			gmp_config_lib_prefix="$gmp_config_prefix/lib"
		fi
	fi

	GMP_CPPFLAGS=
	if test "x$gmp_config_include_prefix" != "x" ; then
		GMP_CPPFLAGS="-I$gmp_config_include_prefix"
	fi

	GMP_LDFLAGS=
	if test "x$gmp_config_lib_prefix" != "x" ; then
		GMP_LDFLAGS="-L$gmp_config_lib_prefix"
	fi

AC_SUBST(GMP_CPPFLAGS)
AC_SUBST(GMP_LDFLAGS)
])

dnl mpria_AC_PROG_GMP_CC_BOOTSTRAP
dnl Inspired by some material in the configure.ac file
dnl distributed within the MPFR source ball
dnl at the time of writting (2014/01/31).
dnl The lastest version of MPFR is always available
dnl at http://www.mpfr.org/.
AC_DEFUN_ONCE([mpria_AC_PROG_GMP_CC_BOOTSTRAP],[dnl
AC_REQUIRE([AC_PROG_AWK])dnl
AC_REQUIRE([_mpria_AC_PROG_PATH_GMP_CC_ARG_WITH])dnl
AC_BEFORE([$0],[mpria_AC_PROG_GMP_CC])dnl
AC_BEFORE([$0],[mpria_AM_PATH_GMP])dnl

AC_MSG_CHECKING([for a C preprocessor to process gmp.h])
AC_MSG_RESULT([..])
if test -z "$GMP_GPP"; then
# Partially inspired by AC_PROG_CPP in autoconf/c.m4 .
# On Suns, sometimes $CPP names a directory.
	if test -n "$CPP" && test -d "$CPP" ; then
		CPP=
	fi
	if test -z "$CPP" ; then
		AC_PATH_TOOL([GMP_GPP],[cpp],[/lib/cpp],[/lib$PATH_SEPARATOR$PATH])
	else
		GMP_GPP=$CPP
	fi
fi
AC_MSG_CHECKING([for a C preprocessor to process gmp.h])
AC_MSG_RESULT([.. $GMP_GPP])
AC_ARG_VAR(GMP_GPP,[C preprocessor command to process gmp.h at bootstrap stage])

AC_LANG_CONFTEST([AC_LANG_SOURCE(
[[
#include "gmp.h"

#ifdef __GMP_CC
GMPM4_CC:: __GMP_CC
#else
GMPM4_CC:: ""
#endif

#ifdef __GMP_CFLAGS
GMPM4_CFLAGS:: __GMP_CFLAGS
#else
GMPM4_CFLAGS:: ""
#endif

#ifdef __GNU_MP_VERSION
GMPM4_VERSIONMAJOR:: __GNU_MP_VERSION
#else
GMPM4_VERSIONMAJOR:: 0
#endif

#ifdef __GNU_MP_VERSION_MINOR
GMPM4_VERSIONMINOR:: __GNU_MP_VERSION_MINOR
#else
GMPM4_VERSIONMINOR:: 0
#endif

#ifdef __GNU_MP_VERSION_PATCHLEVEL
GMPM4_VERSIONMICRO:: __GNU_MP_VERSION_PATCHLEVEL
#else
GMPM4_VERSIONMICRO:: 0
#endif
]]
)])

if test -f conftest.c ; then
	if $GMP_GPP $GMP_CPPFLAGS conftest.c 2>/dev/null > conftest.i ; then
		if
			GMP_CC=`$AWK 'BEGIN { status = 1 ; FS = "\"" } ; /^GMPM4_CC::/ { print $[]2 ; status = 0 ; exit } ; END { exit status }' conftest.i` &&
			GMP_CFLAGS=`$AWK 'BEGIN { status = 1 ; FS = "\"" } ; /^GMPM4_CFLAGS::/ { print $[]2 ; status = 0 ; exit } ; END { exit status }' conftest.i` &&
			gmp_hdr_version_major=`$AWK 'BEGIN { status = 1 } ; /^GMPM4_VERSIONMAJOR::/ { print $[]2 ; status = 0 ; exit } ; END { exit status }' conftest.i` &&
			gmp_hdr_version_minor=`$AWK 'BEGIN { status = 1 } ; /^GMPM4_VERSIONMINOR::/ { print $[]2 ; status = 0 ; exit } ; END { exit status }' conftest.i` &&
			gmp_hdr_version_micro=`$AWK 'BEGIN { status = 1 } ; /^GMPM4_VERSIONMICRO::/ { print $[]2 ; status = 0 ; exit } ; END { exit status }' conftest.i`
		then : ; else
			AC_MSG_FAILURE([unexpected awk ($AWK) failure])
		fi
	else
		AC_MSG_FAILURE([unexpected C preprocessor ($GMP_GPP) failure])
	fi
	rm -f conftest.i
	rm -f conftest.c
else
	AC_MSG_FAILURE([cannot find C preproccessor input])
fi

gmp_hdr_dotted_version="$gmp_hdr_version_major.$gmp_hdr_version_minor.$gmp_hdr_version_micro"

AC_SUBST(GMP_CC)
AC_SUBST(GMP_CFLAGS)
])

dnl mpria_AC_PROG_GMP_CC
AC_DEFUN_ONCE([mpria_AC_PROG_GMP_CC],[dnl
AC_REQUIRE([_mpria_AC_PROG_PATH_GMP_CC_ARG_WITH])dnl
AC_REQUIRE([mpria_AC_PROG_GMP_CC_BOOTSTRAP])dnl
AC_BEFORE([$0],[mpria_AM_PATH_GMP])dnl
if test -n "$GMP_CC" ; then
	CC=$GMP_CC
fi
AC_PROG_CC
AC_PROG_CPP
])

dnl mpria_AM_PATH_GMP([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
AC_DEFUN([mpria_AM_PATH_GMP],[dnl
AC_REQUIRE([AC_PROG_SED])dnl
AC_REQUIRE([_mpria_AC_PROG_PATH_GMP_CC_ARG_WITH])dnl

	min_gmp_version=m4_default([$1],[4.1.0])
	min_gmp_version_0_0_0="$min_gmp_version.0.0.0"

	min_gmp_version_major=`echo $min_gmp_version_0_0_0 | \
		$SED 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)\(.*\)/\1/'`
	min_gmp_version_minor=`echo $min_gmp_version_0_0_0 | \
		$SED 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)\(.*\)/\2/'`
	min_gmp_version_micro=`echo $min_gmp_version_0_0_0 | \
		$SED 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)\(.*\)/\3/'`

	min_gmp_dotted_version="$min_gmp_version_major.$min_gmp_version_minor.$min_gmp_version_micro"

	GMP_LIBS="-lgmp"

	AC_MSG_CHECKING([for GMP - version >= $min_gmp_version ])

	ac_save_CPPFLAGS="$CPPFLAGS"
	ac_save_CFLAGS="$CFLAGS"
	ac_save_LDFLAGS="$LDFLAGS"
	ac_save_LIBS="$LIBS"

	CPPFLAGS="$CPPFLAGS $GMP_CPPFLAGS"
	CFLAGS="$CFLAGS $GMP_CFLAGS"
	LDFLAGS="$LDFLAGS $GMP_LDFLAGS"
	LIBS="$LIBS $GMP_LIBS"

	if test "x$gmp_hdr_version_major" != "x" ; then
		gmp_comment_flag=1
	else
		gmp_comment_flag=0
	fi
	rm -f conf.gmptest
	AC_RUN_IFELSE([AC_LANG_SOURCE(
[[
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINTF_MSG_ERROR_MISMATCH_HEADER \
	printf("*** This likely indicates either a bad configuration or some other\n"); \
	printf("*** inconsistency in the development environment. If the GNU MP header\n"); \
	printf("*** is searched in different include paths, it may be sufficient either\n"); \
	printf("*** to set a proper include path through the --with-gmp-include configure\n"); \
	printf("*** option, or to specify a pertinent C preprocessor via the GMP_GPP or\n"); \
	printf("*** CPP influential environment variables.\n"); \
	printf("***\n"); \
	printf("*** If an old version is installed, it may be best to remove it and to\n"); \
	printf("*** reinstall a more recent one; although removing and then reinstalling\n"); \
	printf("*** from scratch the GNU MP library may also get things to work. The latest\n"); \
	printf("*** version of GNU MP is always available from http://gmplib.org/.\n"); \
	printf("***\n");

#define PRINTF_MSG_ERROR_MISMATCH_HEADER_LIBRARY \
	printf("*** This likely indicates either a bad configuration or some\n"); \
	printf("*** other inconsistency in the development environment. If the\n"); \
	printf("*** expected GNU MP library cannot be found, it may be sufficient\n"); \
	printf("*** either to set properly the LD_LIBRARY_PATH environment variable\n"); \
	printf("*** or to configure ldconfig(8) to consider the installed location.\n"); \
	printf("*** Otherwise a bad configuration or an inconsistency in the\n"); \
	printf("*** include/library search paths may be investigated; adjustments\n"); \
	printf("*** through the use of --with-gmp-(include|lib) configure option\n"); \
	printf("*** may help.\n"); \
	printf("***\n"); \
	printf("*** If an old version is installed, it may be best to remove it and to\n"); \
	printf("*** reinstall a more recent one; although modifying LD_LIBRARY_PATH\n"); \
	printf("*** may also get things to work. The latest version of GNU MP is always\n"); \
	printf("*** available from http://gmplib.org/.\n"); \
	printf("***\n");

int main ()
{
	int gmp_hdr_version_major = 0;
	int gmp_hdr_version_minor = 0;
	int gmp_hdr_version_micro = 0;
	int gmp_lib_version_major = 0;
	int gmp_lib_version_minor = 0;
	int gmp_lib_version_micro = 0;
	char *tmp_version_0;
	char *tmp_version_1;
	mpz_t a;
	mpz_t b;
	mpz_t c;

	mpz_init (a);
	mpz_init (b);
	mpz_init (c);
	mpz_mul (c, a, b);

	fclose (fopen ("conf.gmptest", "w"));

#ifdef __GMP_CC
#define GMPM4_CC __GMP_CC
#else
#define GMPM4_CC ""
#endif

#ifdef __GMP_CFLAGS
#define GMPM4_CFLAGS __GMP_CFLAGS
#else
#define GMPM4_CFLAGS ""
#endif

#ifdef __GNU_MP_VERSION
	gmp_hdr_version_major = __GNU_MP_VERSION;
#endif

#ifdef __GNU_MP_VERSION_MINOR
	gmp_hdr_version_minor = __GNU_MP_VERSION_MINOR;
#endif

#ifdef __GNU_MP_VERSION_PATCHLEVEL
	gmp_hdr_version_micro = __GNU_MP_VERSION_PATCHLEVEL;
#endif

	/* HP/UX 9 (%@#!) writes to sscanf strings */
	tmp_version_0 = strdup(gmp_version);
	tmp_version_1 = strdup(gmp_version);
	if (sscanf(tmp_version_0, "%d.%d.%d",
			&gmp_lib_version_major, &gmp_lib_version_minor, &gmp_lib_version_micro) != 3) {
		gmp_lib_version_micro = 0;
		if (sscanf(tmp_version_1, "%d.%d",
				&gmp_lib_version_major, &gmp_lib_version_minor) != 2) {
			printf("\n***\n");
			printf("*** unexpected GMP library version string\n");
			printf("***\n");
			exit(1);
			}
	}

#if $gmp_comment_flag
	if (
			($gmp_hdr_version_major != gmp_hdr_version_major) ||
			($gmp_hdr_version_minor != gmp_hdr_version_minor) ||
			($gmp_hdr_version_micro != gmp_hdr_version_micro)
		) {
		printf("\n***\n");
		printf("*** The preprocessed GNU MP header version numbers ($gmp_hdr_dotted_version) and\n");
		printf("*** the compiled GNU MP header version numbers (%d.%d.%d)\n",
			gmp_hdr_version_major, gmp_hdr_version_minor, gmp_hdr_version_micro);
		printf("*** do not match.\n");
		printf("***\n");
		PRINTF_MSG_ERROR_MISMATCH_HEADER
		}
	else if (strcmp("$GMP_CC",GMPM4_CC)) {
		printf("\n***\n");
		printf("*** The preprocessed GNU MP header __GMP_CC macro value (\"$GMP_CC\") and\n");
		printf("*** the compiled GNU MP header __GMP_CC macro value (\"" GMPM4_CC "\")\n");
		printf("*** do not match.\n");
		printf("***\n");
		PRINTF_MSG_ERROR_MISMATCH_HEADER
		}
	else if (strcmp("$GMP_CFLAGS",GMPM4_CFLAGS)) {
		printf("\n***\n");
		printf("*** The preprocessed GNU MP header __GMP_CFLAGS macro value (\"$GMP_CFLAGS\") and\n");
		printf("*** the compiled GNU MP header __GMP_CFLAGS macro value (\"" GMPM4_CFLAGS "\")\n");
		printf("*** do not match.\n");
		printf("***\n");
		PRINTF_MSG_ERROR_MISMATCH_HEADER
		}
	else
#endif
	if (
			(gmp_lib_version_major != gmp_hdr_version_major) ||
			(gmp_lib_version_minor != gmp_hdr_version_minor) ||
			(gmp_lib_version_micro != gmp_hdr_version_micro)
		) {
		printf("\n***\n");
		printf("*** GNU MP header version numbers (%d.%d.%d) and\n",
			gmp_hdr_version_major, gmp_hdr_version_minor, gmp_hdr_version_micro);
		printf("*** GNU MP library version numbers (%d.%d.%d)\n",
			gmp_lib_version_major, gmp_lib_version_minor, gmp_lib_version_micro);
		printf("*** do not match.\n");
		printf("***\n");
		PRINTF_MSG_ERROR_MISMATCH_HEADER_LIBRARY
		}
	else if (
			($min_gmp_version_major < gmp_hdr_version_major) ||
			(
				($min_gmp_version_major == gmp_hdr_version_major) &&
				($min_gmp_version_minor < gmp_hdr_version_minor)
				) ||
			(
				($min_gmp_version_major == gmp_hdr_version_major) &&
				($min_gmp_version_minor == gmp_hdr_version_minor) &&
				($min_gmp_version_micro <= gmp_hdr_version_micro)
				)
		) {
		return (0);
		}
	else {
		printf("\n***\n");
		printf("*** GNU MP version $min_gmp_dotted_version or higher is required:\n");
		printf("*** an older version of GNU MP (%d.%d.%d) was found.\n",
			gmp_hdr_version_major, gmp_hdr_version_minor, gmp_hdr_version_micro);
		printf("*** The latest version of GNU MP is always available from http://gmplib.org/.\n");
		printf("***\n");
		}

	return (1);
}
]]
)],[],[no_gmp=yes],[AC_MSG_WARN([$ac_n "cross compiling; assumed OK... $ac_c])])

	CPPFLAGS="$ac_save_CPPFLAGS"
	CFLAGS="$ac_save_CFLAGS"
	LDFLAGS="$ac_save_LDFLAGS"
	LIBS="$ac_save_LIBS"

	if test "x$no_gmp" = "x" ; then
		AC_MSG_RESULT([yes])
		$2
	else
		AC_MSG_RESULT([no])
		if test -f conf.gmptest ; then
			:
		else
			echo "***"
			echo "*** Could not run GNU MP test program, checking why..."
			CPPFLAGS="$CPPFLAGS $GMP_CPPFLAGS"
			CFLAGS="$CFLAGS $GMP_CFLAGS"
			LDFLAGS="$CFLAGS $GMP_LDFLAGS"
			LIBS="$LIBS $GMP_LIBS"
			AC_LINK_IFELSE([AC_LANG_PROGRAM(
[[
#include <gmp.h>
#include <stdio.h>
]],
[[ return (1); ]]
)],
[
echo "***"
echo "*** The test program compiled, but did not run. This usually means"
echo "*** that the run-time linker is not finding GNU MP or finding the wrong"
echo "*** version of GNU MP. If it is not finding GNU MP, you'll need to set your"
echo "*** LD_LIBRARY_PATH environment variable, or configure ldconfig(8) to consider"
echo "*** the installed location."
echo "***"
echo "*** If you have an old version installed, it is best to remove it; although"
echo "*** modifying LD_LIBRARY_PATH may also get things to work. The latest version"
echo "*** of GNU MP is always available from http://gmplib.org/."
echo "***"
],
[
echo "***"
echo "*** The test program failed to compile or link. See the file config.log for the"
echo "*** exact error that occured. This usually means GNU MP was incorrectly installed"
echo "*** or that you have moved GNU MP since it was installed."
echo "***"
])
			CPPFLAGS="$ac_save_CPPFLAGS"
			CFLAGS="$ac_save_CFLAGS"
			LDFLAGS="$ac_save_LDFLAGS"
			LIBS="$ac_save_LIBS"
		fi
		rm -f conf.gmptest
		m4_default([$3],[AC_MSG_ERROR([no suitable GNU MP library found])])
	fi
	rm -f conf.gmptest

AC_SUBST(GMP_LIBS)
])

dnl mpria_AC_PROG_PATH_GMP_CC([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
AC_DEFUN([mpria_AC_PROG_PATH_GMP_CC],[dnl
AC_REQUIRE([mpria_AC_PROG_GMP_CC])
mpria_AM_PATH_GMP([$1],[$2],[$3])
])

dnl eof
