# mpria.m4 serial 2
dnl mpria.m4 -- M4 macro processor include script
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

dnl mpria_AM_PATH_MPRIA([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
AC_DEFUN([mpria_AM_PATH_MPRIA],[dnl
AC_REQUIRE([AC_PROG_SED])dnl
AC_REQUIRE([mpria_AM_PATH_GMP])dnl

AC_ARG_WITH([mpria-prefix],
	[AS_HELP_STRING([--with-mpria-prefix=PREFIX],
		[specify prefix for the installed MPRIA [standard search prefixes]])],
	[mpria_config_prefix="$withval"],[mpria_config_prefix=""])
AC_ARG_WITH([mpria-include],
	[AS_HELP_STRING([--with-mpria-include=PATH],
		[specify directory for the installed MPRIA header file [standard search paths]])],
	[mpria_config_include_prefix="$withval"],[mpria_config_include_prefix=""])
AC_ARG_WITH([mpria-lib],
	[AS_HELP_STRING([--with-mpria-lib=PATH],
		[specify directory for the installed MPRIA library [standard search paths]])],
	[mpria_config_lib_prefix="$withval"],[mpria_config_lib_prefix=""])

	if test "x$mpria_config_include_prefix" = "x" ; then
		if test "x$mpria_config_prefix" != "x" ; then
			mpria_config_include_prefix="$mpria_config_prefix/include"
		fi
	fi
	if test "x$mpria_config_lib_prefix" = "x" ; then
		if test "x$mpria_config_prefix" != "x" ; then
			mpria_config_lib_prefix="$mpria_config_prefix/lib"
		fi
	fi

	MPRIA_CPPFLAGS=
	if test "x$mpria_config_include_prefix" != "x" ; then
		MPRIA_CPPFLAGS="-I$mpria_config_include_prefix"
	fi

	MPRIA_CFLAGS=

	MPRIA_LDFLAGS=
	if test "x$mpria_config_lib_prefix" != "x" ; then
		MPRIA_LDFLAGS="-L$mpria_config_lib_prefix"
	fi

	min_mpria_version=m4_default([$1],[0.7.0])
	min_mpria_version_0_0_0="$min_mpria_version.0.0.0"

	min_mpria_version_major=`echo $min_mpria_version_0_0_0 | \
		$SED 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)\(.*\)/\1/'`
	min_mpria_version_minor=`echo $min_mpria_version_0_0_0 | \
		$SED 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)\(.*\)/\2/'`
	min_mpria_version_micro=`echo $min_mpria_version_0_0_0 | \
		$SED 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)\(.*\)/\3/'`

	min_mpria_dotted_version="$min_mpria_version_major.$min_mpria_version_minor.$min_mpria_version_micro"

	MPRIA_LIBS="-lmpria"

	AC_MSG_CHECKING([for MPRIA - version >= $min_mpria_version ])

	ac_save_CPPFLAGS="$CPPFLAGS"
	ac_save_CFLAGS="$CFLAGS"
	ac_save_LDFLAGS="$LDFLAGS"
	ac_save_LIBS="$LIBS"

	CPPFLAGS="$CPPFLAGS $MPRIA_CPPFLAGS $GMP_CPPFLAGS"
	CFLAGS="$CFLAGS $MPRIA_CFLAGS $GMP_CFLAGS"
	LDFLAGS="$LDFLAGS $MPRIA_LDFLAGS $GMP_LDFLAGS"
	LIBS="$LIBS $MPRIA_LIBS $GMP_LIBS"

	rm -f conf.mpriatest
	AC_RUN_IFELSE([AC_LANG_SOURCE(
[[
#include <mpria.h>
#include <stdio.h>

int main ()
{
	int mpria_hdr_version_major = 0;
	int mpria_hdr_version_minor = 0;
	int mpria_hdr_version_micro = 0;
	int mpria_lib_version_major = 0;
	int mpria_lib_version_minor = 0;
	int mpria_lib_version_micro = 0;
	mpri_t qi;

	mpri_init (qi);

	/* (1+sqrt(2))/2 */
	mpri_set_qi_z (qi,
		__mpria_z_pos_one,
		__mpria_z_pos_two,
		__mpria_z_pos_two,
		MPRI_PREC_BITS_QUADRUPLE,
		MPRI_SRND_BCAA);

	mpri_clear (qi);

	fclose (fopen ("conf.mpriatest", "w"));

#ifdef MPRIA_VERSION_MAJOR
	mpria_hdr_version_major = MPRIA_VERSION_MAJOR;
#endif

#ifdef MPRIA_VERSION_MINOR
	mpria_hdr_version_minor = MPRIA_VERSION_MINOR;
#endif

#ifdef MPRIA_VERSION_MICRO
	mpria_hdr_version_micro = MPRIA_VERSION_MICRO;
#endif

	mpria_libversion_get_numbers(
		&mpria_lib_version_major,&mpria_lib_version_minor,&mpria_lib_version_micro);

	if (
			(mpria_lib_version_major != mpria_hdr_version_major) ||
			(mpria_lib_version_minor != mpria_hdr_version_minor) ||
			(mpria_lib_version_micro != mpria_hdr_version_micro)
		) {
		printf("\n***\n");
		printf("*** GNU MPRIA header version numbers (%d.%d.%d) and\n",
			mpria_hdr_version_major, mpria_hdr_version_minor, mpria_hdr_version_micro);
		printf("*** GNU MPRIA library version numbers (%d.%d.%d)\n",
			mpria_lib_version_major, mpria_lib_version_minor, mpria_lib_version_micro);
		printf("*** do not match.\n");
		printf("***\n");
		printf("*** This likely indicates either a bad configuration or some\n");
		printf("*** other inconsistency in the development environment. If the\n");
		printf("*** expected GNU MPRIA library cannot be found, it may be sufficient\n");
		printf("*** either to set properly the LD_LIBRARY_PATH environment variable\n");
		printf("*** or to configure ldconfig(8) to consider the installed location.\n");
		printf("*** Otherwise a bad configuration or an inconsistency in the\n");
		printf("*** include/library search paths may be investigated; adjustments\n");
		printf("*** through the use of --with-mpria-(include|lib) configure option\n");
		printf("*** may help.\n");
		printf("***\n");
		printf("*** If an old version is installed, it may be best to remove it and to\n");
		printf("*** reinstall a more recent one; although modifying LD_LIBRARY_PATH\n");
		printf("*** may also get things to work.\n");
		printf("***\n");
		printf("*** The latest version of GNU MPRIA is always available from\n");
		printf("*** http://www.gnu.org/software/mpria/.\n");
		printf("***\n");
		}
	else if (
			($min_mpria_version_major < mpria_hdr_version_major) ||
			(
				($min_mpria_version_major == mpria_hdr_version_major) &&
				($min_mpria_version_minor < mpria_hdr_version_minor)
				) ||
			(
				($min_mpria_version_major == mpria_hdr_version_major) &&
				($min_mpria_version_minor == mpria_hdr_version_minor) &&
				($min_mpria_version_micro <= mpria_hdr_version_micro)
				)
		) {
		return (0);
		}
	else {
		printf("\n***\n");
		printf("*** GNU MPRIA version $min_mpria_dotted_version or higher is required:\n");
		printf("*** an older version of GNU MPRIA (%d.%d.%d) was found.\n",
			mpria_hdr_version_major, mpria_hdr_version_minor, mpria_hdr_version_micro);
		printf("***\n");
		printf("*** The latest version of GNU MPRIA is always available from\n");
		printf("*** http://www.gnu.org/software/mpria/.\n");
		printf("***\n");
		}

	return (1);
}
]]
)],[],[no_mpria=yes],[AC_MSG_WARN([$ac_n "cross compiling; assumed OK... $ac_c])])

	CPPFLAGS="$ac_save_CPPFLAGS"
	CFLAGS="$ac_save_CFLAGS"
	LDFLAGS="$ac_save_LDFLAGS"
	LIBS="$ac_save_LIBS"

	if test "x$no_mpria" = "x" ; then
		AC_MSG_RESULT([yes])
		$2
	else
		AC_MSG_RESULT([no])
		if test -f conf.mpriatest ; then
			:
		else
			echo "***"
			echo "*** Could not run GNU MPRIA test program, checking why..."
			CPPFLAGS="$CPPFLAGS $MPRIA_CPPFLAGS $GMP_CPPFLAGS"
			CFLAGS="$CFLAGS $MPRIA_CFLAGS $GMP_CFLAGS"
			LDFLAGS="$CFLAGS $MPRIA_LDFLAGS $GMP_LDFLAGS"
			LIBS="$LIBS $MPRIA_LIBS $GMP_LIBS"
			AC_LINK_IFELSE([AC_LANG_PROGRAM(
[[
#include <mpria.h>
#include <stdio.h>
]],
[[ return (1); ]]
)],
[
echo "***"
echo "*** The test program compiled, but did not run. This usually means"
echo "*** that the run-time linker is not finding GNU MPRIA or finding the wrong"
echo "*** version of GNU MPRIA. If it is not finding GNU MPRIA, you'll need to set your"
echo "*** LD_LIBRARY_PATH environment variable, or configure ldconfig(8) to consider"
echo "*** the installed location."
echo "***"
echo "*** If you have an old version installed, it is best to remove it; although"
echo "*** modifying LD_LIBRARY_PATH may also get things to work."
echo "***"
echo "*** The latest version of GNU MPRIA is always available from"
echo "*** http://www.gnu.org/software/mpria/."
echo "***"
],
[
echo "***"
echo "*** The test program failed to compile or link. See the file config.log for the"
echo "*** exact error that occured. This usually means GNU MPRIA was incorrectly installed"
echo "*** or that you have moved GNU MPRIA since it was installed."
echo "***"
])
			CPPFLAGS="$ac_save_CPPFLAGS"
			CFLAGS="$ac_save_CFLAGS"
			LDFLAGS="$ac_save_LDFLAGS"
			LIBS="$ac_save_LIBS"
		fi
		rm -f conf.mpriatest
		m4_default([$3],[AC_MSG_ERROR([no suitable GNU MPRIA library found])])
	fi
	rm -f conf.mpriatest

AC_SUBST(MPRIA_CPPFLAGS)
AC_SUBST(MPRIA_CFLAGS)
AC_SUBST(MPRIA_LDFLAGS)
AC_SUBST(MPRIA_LIBS)
])

dnl eof
