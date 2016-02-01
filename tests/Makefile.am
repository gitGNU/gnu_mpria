## tests/Makefile.am
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

check_HEADERS = \
	mpria_test.h

check_PROGRAMS = \
	test_constants \
	test_string \
	test_conversion \
	test_random \
	test_arithmetic \
	test_numtheory \
	test_confrac \
	test_libversion

check_LTLIBRARIES = libmpriatest.la

TESTS = $(check_PROGRAMS)
TESTS_ENVIRONMENT = MPRIA_TEST_VERBOSITY=2 $(VALGRIND)

libmpriatest_la_SOURCES = \
	results.c

AM_CPPFLAGS = \
	-I$(top_builddir)/src \
	$(GMP_CPPFLAGS)

AM_CFLAGS = \
	$(GMP_CFLAGS)

LDADD = \
	libmpriatest.la \
	$(top_builddir)/src/libmpria.la

AM_LDFLAGS = \
	$(GMP_LDFLAGS) $(GMP_LIBS) \
	$(LIBM)

test_conversion_INPUTS = \
	test_mpri_get_d_table.c

test_random_INPUTS = \
	test_randseed_seed_builtin_table.c

test_arithmetic_INPUTS = \
	test_mpri_add_table.c \
	test_mpri_sub_table.c \
	test_mpri_mul_table.c \
	test_mpri_div_table.c

test_numtheory_INPUTS = \
	test_mpri_set_qi_z_ASGMT_table.c \
	test_mpri_set_qi_q_table.c \
	test_mpri_set_d_table.c \
	test_mpri_set_q_table.c \
	test_mpri_set_sqrt_q_table.c \
	test_mpri_set_rsqrt_q_table.c \
	test_mpri_sqrt_table.c \
	test_mpri_rsqrt_table.c

test_confrac_INPUTS = \
	test_mpri_2exp_atan_table.c

mpria_test.h: $(top_builddir)/src/mpria.h

results.c: mpria_test.h
test_constants.c: mpria_test.h
test_string.c: mpria_test.h
test_conversion.c: mpria_test.h $(test_conversion_INPUTS)
test_random.c: mpria_test.h $(test_random_INPUTS)
test_arithmetic.c: mpria_test.h $(test_arithmetic_INPUTS)
test_numtheory.c: mpria_test.h $(test_numtheory_INPUTS)
test_confrac.c: mpria_test.h $(test_confrac_INPUTS)
test_libversion.c: mpria_test.h

TEST_BH_INPUTS = \
	$(test_random_INPUTS)

TEST_CG_INPUTS = \
	$(test_conversion_INPUTS) \
	$(test_arithmetic_INPUTS) \
	$(test_numtheory_INPUTS) \
	$(test_confrac_INPUTS)

MAINTAINER_EXTRA_DIST = \
	mpria_test.gi \
		mpria_numtheory.gi\
	$(TEST_CG_INPUTS:%.c=%.cg)

EXTRA_DIST = \
	$(TEST_BH_INPUTS) \
	$(TEST_CG_INPUTS) \
	$(MAINTAINER_EXTRA_DIST)

if MAINTAINER_MODE

SUFFIXES = .cg

.cg.c:
	$(GAP) -q -T $<

mpria_test.gi: mpria_numtheory.gi

$(TEST_CG_INPUTS): mpria_test.gi

BUILT_SOURCES = \
	$(TEST_CG_INPUTS)

MAINTAINERCLEANFILES = \
	$(BUILT_SOURCES)

endif

$(top_builddir)/src/mpria.h: FORCE
	cd $(top_builddir)/src && $(MAKE) $(AM_MAKEFLAGS) mpria.h

$(top_builddir)/src/libmpria.la: FORCE
	cd $(top_builddir)/src && $(MAKE) $(AM_MAKEFLAGS) libmpria.la

FORCE:

## eos
