## src/Mafile.am
## MPRIA - GNU Multi-Precision Rational Interval Arithmetic Library
## Copyright (C) 2009-2016  Jerome Benoit <jgmbenoit@rezozer.net>
##
## This file is part of the GNU MPRIA Library.
##
## The GNU MPRIA Library is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## The GNU MPRIA Library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with the GNU MPRIA Library.  If not, see <http://www.gnu.org/licenses/>.
##

nodist_include_HEADERS = mpria.h

lib_LTLIBRARIES = libmpria.la

noinst_HEADERS = \
	mpria_assert.h \
	mpria_internal.h

nodist_noinst_HEADERS = \
	mpria_config.h

libmpria_la_LT_INFO = -version-info $(MPRIA_LT_INFO)

libmpria_la_LD_VERSION_SCRIPT=
if HAVE_LD_VERSION_SCRIPT
  libmpria_la_LD_VERSION_SCRIPT+= -Wl,--version-script=$(top_srcdir)/src/mpria.map
endif

libmpria_la_CPPFLAGS = \
	$(GMP_CPPFLAGS)

libmpria_la_CFLAGS = \
	$(GMP_CFLAGS)

libmpria_la_SOURCES = \
	constants.c \
	workspace.c \
	string.c \
	conversion.c \
	basic.c \
	random.c \
	arithmetic.c \
	numtheory.c \
	confrac.c \
	adhoc.c \
	libversion.c \
	inline.c \
	inline_mp.c

libmpria_la_LDFLAGS = \
	$(libmpria_la_LT_INFO) \
	$(libmpria_la_LD_VERSION_SCRIPT) \
	$(GMP_LDFLAGS)

libmpria_la_LIBADD = \
	$(GMP_LIBS) \
	$(LIBM)

mpria_internal.h: mpria.h

constants.c: mpria.h
workspace.c: mpria_internal.h
string.c: mpria_internal.h
conversion.c: mpria_internal.h
basic.c: mpria_internal.h
arithmetic.c: mpria_internal.h
numtheory.c: mpria_internal.h
confrac.c: mpria_internal.h
adhoc.c: mpria_internal.h
libversion.c: mpria.h
inline.c: mpria.h
inline_mp.c: mpria.h

EXTRA_DIST = \
	mpria_internal.h \
	mpria_assert.h \
	mpria.map

## eos
