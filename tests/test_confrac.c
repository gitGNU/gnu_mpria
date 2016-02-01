/* tests/test_confrac.c -- C confrac file */
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
/* #include <string.h> */
#include <stdio.h>
/* #include <stdlib.h> */
/* #include <stdint.h> */
/* #include <inttypes.h> */

#include <gmp.h>

#include "mpria_test.h"

#define TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT 4096

void test_mpri_2exp_atan(void);

typedef struct {
	unsigned long int exponent;
	const char * argument_lep;
	const char * argument_rep;
	mpri_prec_t bits;
	const char * mpf_expected_lep;
	const char * mpf_expected_rep;
	} test_mpri_2exp_atan_tuple;

void test_mpri_2exp_atan(void) {
#include "test_mpri_2exp_atan_table.c"
	test_mpri_2exp_atan_tuple * idx=NULL;
	unsigned long int exponent=ULONG_MAX;
	mpq_ptr argument_lep=NULL;
	mpq_ptr argument_rep=NULL;
	mpri_t argument;
	mpri_prec_t bits=0;
	mpq_ptr observed_lep=NULL;
	mpq_ptr observed_rep=NULL;
	mpri_t observed;
	mpf_t mpf_expected_lep;
	mpf_t mpf_expected_rep;
	mpf_t mpf_expected_epsilon;
	mpf_t mpf_observed_error_absolute_lep;
	mpf_t mpf_observed_error_absolute_rep;
	mpf_t mpf_observed_error_relative_lep;
	mpf_t mpf_observed_error_relative_rep;
	mpf_t mpf_observed_error_absolute;
	mpf_t mpf_observed_error_relative;
	mpf_t mpf_observed_epsilon;
	mpf_t dum;
	int adx=-1;
	int status_loop=MPRIA_SUCCESS;
	int status=MPRIA_SUCCESS;

	mpri_init(argument);
	mpri_init(observed);
	mpf_init2(mpf_expected_lep,TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_rep,TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_epsilon,TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_lep,TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_rep,TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative_lep,TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative_rep,TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute,TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative,TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_epsilon,TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(dum,TEST_MPRIA_CONFRAC_MPF_PRECISION_BITS_DEFAULT);

	argument_lep=mpri_lepref(argument);
	argument_rep=mpri_repref(argument);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->bits)!=0;idx++) {
		exponent=idx->exponent;
		mpq_set_str(argument_lep,idx->argument_lep,10);
		mpq_set_str(argument_rep,idx->argument_rep,10);
		bits=idx->bits;
		mpf_set_str(mpf_expected_lep,idx->mpf_expected_lep,10);
		mpf_set_str(mpf_expected_rep,idx->mpf_expected_rep,10);

		mpf_set_ui(mpf_expected_epsilon,1UL); mpf_div_2exp(mpf_expected_epsilon,mpf_expected_epsilon,bits);

		for(adx=0;adx<2;adx++) {

			switch (adx) {
				default:
				case 0:
					MPRI_SET_NAN(observed);
					mpri_2exp_atan(observed,exponent,argument,bits);
					break;
				case 1:
					mpri_set(observed,argument);
					mpri_2exp_atan(observed,exponent,observed,bits);
					break;
				}

			mpf_set_q(dum,observed_lep); mpf_sub(dum,mpf_expected_lep,dum); mpf_abs(mpf_observed_error_absolute_lep,dum);
			mpf_set_q(dum,observed_rep); mpf_sub(dum,dum,mpf_expected_rep); mpf_abs(mpf_observed_error_absolute_rep,dum);
			if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
				mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_rep);
				}
			else {
				mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_lep);
				}
			if (mpf_sgn(mpf_expected_lep) != 0) {
				mpf_abs(dum,mpf_expected_lep); mpf_div(mpf_observed_error_relative_lep,mpf_observed_error_absolute_lep,dum);
				}
			else {
				mpf_set(mpf_observed_error_relative_lep,mpf_observed_error_absolute_lep);
				}
			if (mpf_sgn(mpf_expected_rep) != 0) {
				mpf_abs(dum,mpf_expected_rep); mpf_div(mpf_observed_error_relative_rep,mpf_observed_error_absolute_rep,dum);
				}
			else {
				mpf_set(mpf_observed_error_relative_rep,mpf_observed_error_absolute_rep);
				}
			if (mpf_cmp(mpf_observed_error_relative_lep,mpf_observed_error_relative_rep) < 0) {
				mpf_set(mpf_observed_error_relative,mpf_observed_error_relative_rep);
				}
			else {
				mpf_set(mpf_observed_error_relative,mpf_observed_error_relative_lep);
				}
			if (mpf_cmp(mpf_observed_error_absolute,mpf_observed_error_relative) < 0) {
				mpf_set(mpf_observed_epsilon,mpf_observed_error_relative);
				}
			else {
				mpf_set(mpf_observed_epsilon,mpf_observed_error_absolute);
				}

			status_loop=MPRIA_SUCCESS;

			if (
					(mpq_cmp(observed_rep,observed_lep) < 0) ||
					(mpf_cmp(mpf_expected_epsilon,mpf_observed_epsilon) <= 0)
					) {
				status_loop=MPRIA_FAILURE;
				}

#ifdef TEST_MPRIA_VERY_VERBOSE
			gmp_fprintf(stdout,
					"%s:%i>"                                       "\t"
					"2^(%lu) atan([%Qd,%Qd])"                      "\t"
					"%d"                                           "\t"
					"(observed [%Qd,%Qd])"                         "\t"
					"[observed epsilon %g vs expected epsilon %g]" "\n"
					,
				((status_loop != MPRIA_SUCCESS)?"FAIL":"PASS"),
				adx,
				exponent,
				argument_lep,argument_rep,
				bits,
				observed_lep,observed_rep,
				mpf_get_d(mpf_observed_epsilon),mpf_get_d(mpf_expected_epsilon)
				);
#endif /* TEST_MPRIA_VERY_VERBOSE */
			}

		if (status_loop != MPRIA_SUCCESS) {
			status=MPRIA_FAILURE;
			}
		}

	mpf_clear(dum);
	mpf_clear(mpf_observed_epsilon);
	mpf_clear(mpf_observed_error_relative);
	mpf_clear(mpf_observed_error_absolute);
	mpf_clear(mpf_observed_error_relative_rep);
	mpf_clear(mpf_observed_error_relative_lep);
	mpf_clear(mpf_observed_error_absolute_rep);
	mpf_clear(mpf_observed_error_absolute_lep);
	mpf_clear(mpf_expected_epsilon);
	mpf_clear(mpf_expected_rep);
	mpf_clear(mpf_expected_lep);
	mpri_clear(observed);
	mpri_clear(argument);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_2exp_atan computes as expected");

	return ; }

int main(int nargs, char * args[]) {

#ifdef TEST_MPRIA_VERBOSE
	mpria_test_verbose(1);
#endif

	test_mpri_2exp_atan();

	return (mpria_test_summary()); }

/* End of file tests/test_confrac.c */
