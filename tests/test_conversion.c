/* tests/test_conversion.c -- C source file */
/*
 * MPRIA - GNU Multi-Precision Rational Interval Arithmetic Library
 * Copyright (C) 2009-2016  Jerome Benoit <jgmbenoit@rezozer.net>
 *
 * This file is part of the GNU MPRIA Library.
 *
 * The GNU MPRIA Library is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The GNU MPRIA Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the GNU MPRIA Library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "mpria_config.h"
/* #include "mpria_assert.h" */

#include <stddef.h>
/* #include <limits.h> */
#include <float.h>
/* #include <string.h> */
#include <stdio.h>
/* #include <stdlib.h> */
/* #include <stdint.h> */
/* #include <inttypes.h> */
#include <math.h>

#include <gmp.h>

#include "mpria_test.h"

#define TEST_CONVERSION_EPSILON (2.0*DBL_EPSILON)

void test_mpri_get_d(void);

typedef struct {
	const char * argument_lep;
	const char * argument_rep;
	double expected;
	} test_mpri_get_d_tuple;

void test_mpri_get_d(void) {
#include "test_mpri_get_d_table.c"
	test_mpri_get_d_tuple * idx=NULL;
	mpq_ptr argument_lep=NULL;
	mpq_ptr argument_rep=NULL;
	mpri_t argument;
	double observed=(0.0/0.0);
	double expected=(0.0/0.0);
	double observed_error_absolute=(0.0/0.0);
	double observed_error_relative=(0.0/0.0);
	double observed_epsilon=(0.0/0.0);
	int status=MPRIA_SUCCESS;

	mpri_init(argument);

	argument_lep=mpri_lepref(argument);
	argument_rep=mpri_repref(argument);

	for(idx=test_table;(idx->argument_lep)!=NULL;idx++) {
		mpq_set_str(argument_lep,idx->argument_lep,10);
		mpq_set_str(argument_rep,idx->argument_rep,10);
		expected=idx->expected;
		observed=mpri_get_d(argument);
		observed_error_absolute=fabs(observed-expected);
		if (expected != 0.0) {
			observed_error_relative=observed_error_absolute/expected;
			observed_epsilon=observed_error_relative;
			}
		else {
			observed_epsilon=observed_error_absolute;
			}
		if (!(observed_epsilon < TEST_CONVERSION_EPSILON)) {
			status=MPRIA_FAILURE;
			}
		}

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_get_d gets as expected");

	return ; }

int main(int nargs, char * args[]) {

#ifdef TEST_MPRIA_VERBOSE
	mpria_test_verbose(1);
#endif

	test_mpri_get_d();

	return (mpria_test_summary()); }

/* End of file tests/test_conversion.c */
