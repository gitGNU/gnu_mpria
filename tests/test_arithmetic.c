/* tests/test_arithmetic.c -- C source file */
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
#include <string.h>
#include <stdio.h>
/* #include <stdlib.h> */
/* #include <stdint.h> */
/* #include <inttypes.h> */

#include <gmp.h>

#include "mpria_test.h"

void test_mpri_add(void);
void test_mpri_sub(void);
void test_mpri_mul(void);
void test_mpri_div(void);

typedef struct {
	const char * augend_lep;
	const char * augend_rep;
	const char * addend_lep;
	const char * addend_rep;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_add_tuple;

typedef struct {
	const char * minuend_lep;
	const char * minuend_rep;
	const char * subtrahend_lep;
	const char * subtrahend_rep;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_sub_tuple;

typedef struct {
	const char * multiplier_lep;
	const char * multiplier_rep;
	const char * multiplicand_lep;
	const char * multiplicand_rep;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_mul_tuple;

typedef struct {
	const char * dividend_lep;
	const char * dividend_rep;
	const char * divisor_lep;
	const char * divisor_rep;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_div_tuple;

void test_mpri_add(void) {
#include "test_mpri_add_table.c"
	test_mpri_add_tuple * idx=NULL;
	mpq_ptr augend_lep;
	mpq_ptr augend_rep;
	mpq_ptr addend_lep;
	mpq_ptr addend_rep;
	mpq_ptr expected_lep;
	mpq_ptr expected_rep;
	mpq_ptr observed_lep;
	mpq_ptr observed_rep;
	mpri_t augend;
	mpri_t addend;
	mpri_t expected;
	mpri_t observed;
	int adx=-1;
	int status=MPRIA_SUCCESS;

	mpri_init(augend);
	mpri_init(addend);
	mpri_init(expected);
	mpri_init(observed);

	augend_lep=mpri_lepref(augend);
	augend_rep=mpri_repref(augend);
	addend_lep=mpri_lepref(addend);
	addend_rep=mpri_repref(addend);
	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->expected_rep)!=NULL;idx++) {
		mpq_set_str(augend_lep,idx->augend_lep,10);
		mpq_set_str(augend_rep,idx->augend_rep,10);
		mpq_set_str(addend_lep,idx->addend_lep,10);
		mpq_set_str(addend_rep,idx->addend_rep,10);
		mpq_set_str(expected_lep,idx->expected_lep,10);
		mpq_set_str(expected_rep,idx->expected_rep,10);

		for(adx=0;adx<5;adx++) {

			switch (adx) {
				default:
				case 0:
					MPRI_SET_NAN(observed);
					mpri_add(observed,augend,addend);
					break;
				case 1:
					mpri_set(observed,augend);
					mpri_add(observed,observed,addend);
					break;
				case 2:
					mpri_set(observed,addend);
					mpri_add(observed,augend,observed);
					break;
				case 3:
					if (mpri_equal(augend,addend)) {
						MPRI_SET_NAN(observed);
						mpri_add(observed,augend,augend);
						}
					else {
						continue;
						}
					break;
				case 4:
					if (mpri_equal(augend,addend)) {
						mpri_set(observed,augend);
						mpri_add(observed,observed,observed);
						}
					else {
						continue;
						}
					break;
				}

			if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
				status=MPRIA_FAILURE;
				}

#ifdef TEST_MPRIA_VERY_VERBOSE
			gmp_fprintf(stdout,
					"%s:%i>"                                     "\t"
					"[%Qd,%Qd] + [%Qd,%Qd]"                      "\t"
					"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])" "\n"
					,
				(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
				adx,
				augend_lep,augend_rep,
				addend_lep,addend_rep,
				observed_lep,observed_rep,
				expected_lep,expected_rep
				);
#endif /* TEST_MPRIA_VERY_VERBOSE */
			}

		}

	mpri_clear(observed);
	mpri_clear(expected);
	mpri_clear(augend);
	mpri_clear(addend);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_add adds as expected");

	return ; }

void test_mpri_sub(void) {
#include "test_mpri_sub_table.c"
	test_mpri_sub_tuple * idx=NULL;
	mpq_ptr minuend_lep;
	mpq_ptr minuend_rep;
	mpq_ptr subtrahend_lep;
	mpq_ptr subtrahend_rep;
	mpq_ptr expected_lep;
	mpq_ptr expected_rep;
	mpq_ptr observed_lep;
	mpq_ptr observed_rep;
	mpri_t minuend;
	mpri_t subtrahend;
	mpri_t expected;
	mpri_t observed;
	int adx=-1;
	int status=MPRIA_SUCCESS;

	mpri_init(minuend);
	mpri_init(subtrahend);
	mpri_init(expected);
	mpri_init(observed);

	minuend_lep=mpri_lepref(minuend);
	minuend_rep=mpri_repref(minuend);
	subtrahend_lep=mpri_lepref(subtrahend);
	subtrahend_rep=mpri_repref(subtrahend);
	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->expected_rep)!=NULL;idx++) {
		mpq_set_str(minuend_lep,idx->minuend_lep,10);
		mpq_set_str(minuend_rep,idx->minuend_rep,10);
		mpq_set_str(subtrahend_lep,idx->subtrahend_lep,10);
		mpq_set_str(subtrahend_rep,idx->subtrahend_rep,10);
		mpq_set_str(expected_lep,idx->expected_lep,10);
		mpq_set_str(expected_rep,idx->expected_rep,10);

		for(adx=0;adx<5;adx++) {

			switch (adx) {
				default:
				case 0:
					MPRI_SET_NAN(observed);
					mpri_sub(observed,minuend,subtrahend);
					break;
				case 1:
					mpri_set(observed,minuend);
					mpri_sub(observed,observed,subtrahend);
					break;
				case 2:
					mpri_set(observed,subtrahend);
					mpri_sub(observed,minuend,observed);
					break;
				case 3:
					if (mpri_equal(minuend,subtrahend)) {
						MPRI_SET_NAN(observed);
						mpri_sub(observed,minuend,minuend);
						}
					else {
						continue;
						}
					break;
				case 4:
					if (mpri_equal(minuend,subtrahend)) {
						mpri_set(observed,minuend);
						mpri_sub(observed,observed,observed);
						}
					else {
						continue;
						}
					break;
				}

			if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
				status=MPRIA_FAILURE;
				}

#ifdef TEST_MPRIA_VERY_VERBOSE
			gmp_fprintf(stdout,
					"%s:%i>"                                     "\t"
					"[%Qd,%Qd] - [%Qd,%Qd]"                      "\t"
					"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])" "\n"
					,
				(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
				adx,
				minuend_lep,minuend_rep,
				subtrahend_lep,subtrahend_rep,
				observed_lep,observed_rep,
				expected_lep,expected_rep
				);
#endif /* TEST_MPRIA_VERY_VERBOSE */
			}

		}

	mpri_clear(observed);
	mpri_clear(expected);
	mpri_clear(minuend);
	mpri_clear(subtrahend);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_sub subtracts as expected");

	return ; }

void test_mpri_mul(void) {
#include "test_mpri_mul_table.c"
	test_mpri_mul_tuple * idx=NULL;
	mpq_ptr multiplier_lep;
	mpq_ptr multiplier_rep;
	mpq_ptr multiplicand_lep;
	mpq_ptr multiplicand_rep;
	mpq_ptr expected_lep;
	mpq_ptr expected_rep;
	mpq_ptr observed_lep;
	mpq_ptr observed_rep;
	mpri_t multiplier;
	mpri_t multiplicand;
	mpri_t expected;
	mpri_t observed;
	int adx=-1;
	int status=MPRIA_SUCCESS;

	mpri_init(multiplier);
	mpri_init(multiplicand);
	mpri_init(expected);
	mpri_init(observed);

	multiplier_lep=mpri_lepref(multiplier);
	multiplier_rep=mpri_repref(multiplier);
	multiplicand_lep=mpri_lepref(multiplicand);
	multiplicand_rep=mpri_repref(multiplicand);
	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->expected_rep)!=NULL;idx++) {
		mpq_set_str(multiplier_lep,idx->multiplier_lep,10);
		mpq_set_str(multiplier_rep,idx->multiplier_rep,10);
		mpq_set_str(multiplicand_lep,idx->multiplicand_lep,10);
		mpq_set_str(multiplicand_rep,idx->multiplicand_rep,10);
		mpq_set_str(expected_lep,idx->expected_lep,10);
		mpq_set_str(expected_rep,idx->expected_rep,10);

		for(adx=0;adx<5;adx++) {

			switch (adx) {
				default:
				case 0:
					MPRI_SET_NAN(observed);
					mpri_mul(observed,multiplier,multiplicand);
					break;
				case 1:
					mpri_set(observed,multiplier);
					mpri_mul(observed,observed,multiplicand);
					break;
				case 2:
					mpri_set(observed,multiplicand);
					mpri_mul(observed,multiplier,observed);
					break;
				case 3:
					if (mpri_equal(multiplier,multiplicand)) {
						MPRI_SET_NAN(observed);
						mpri_mul(observed,multiplier,multiplier);
						}
					else {
						continue;
						}
					break;
				case 4:
					if (mpri_equal(multiplier,multiplicand)) {
						mpri_set(observed,multiplier);
						mpri_mul(observed,observed,observed);
						}
					else {
						continue;
						}
					break;
				}

			if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
				status=MPRIA_FAILURE;
				}

#ifdef TEST_MPRIA_VERY_VERBOSE
			gmp_fprintf(stdout,
					"%s:%i>"                                     "\t"
					"[%Qd,%Qd] * [%Qd,%Qd]"                      "\t"
					"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])" "\n"
					,
				(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
				adx,
				multiplier_lep,multiplier_rep,
				multiplicand_lep,multiplicand_rep,
				observed_lep,observed_rep,
				expected_lep,expected_rep
				);
#endif /* TEST_MPRIA_VERY_VERBOSE */
			}

		}

	mpri_clear(observed);
	mpri_clear(expected);
	mpri_clear(multiplier);
	mpri_clear(multiplicand);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_mul multiplies as expected");

	return ; }

void test_mpri_div(void) {
#include "test_mpri_div_table.c"
	test_mpri_div_tuple * idx=NULL;
	mpq_ptr dividend_lep;
	mpq_ptr dividend_rep;
	mpq_ptr divisor_lep;
	mpq_ptr divisor_rep;
	mpq_ptr expected_lep;
	mpq_ptr expected_rep;
	mpq_ptr observed_lep;
	mpq_ptr observed_rep;
	mpri_t dividend;
	mpri_t divisor;
	mpri_t expected;
	mpri_t observed;
	int adx=-1;
	int status=MPRIA_SUCCESS;

	mpri_init(dividend);
	mpri_init(divisor);
	mpri_init(expected);
	mpri_init(observed);

	dividend_lep=mpri_lepref(dividend);
	dividend_rep=mpri_repref(dividend);
	divisor_lep=mpri_lepref(divisor);
	divisor_rep=mpri_repref(divisor);
	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->expected_rep)!=NULL;idx++) {
		mpq_set_str(dividend_lep,idx->dividend_lep,10);
		mpq_set_str(dividend_rep,idx->dividend_rep,10);
		mpq_set_str(divisor_lep,idx->divisor_lep,10);
		mpq_set_str(divisor_rep,idx->divisor_rep,10);
		if ((!(strcmp(idx->expected_lep,"nan"))) || (!(strcmp(idx->expected_rep,"nan")))) {
			MPRIA_MPQ_SET_NAN(expected_lep);
			MPRIA_MPQ_SET_NAN(expected_rep);
			}
		else {
			mpq_set_str(expected_lep,idx->expected_lep,10);
			mpq_set_str(expected_rep,idx->expected_rep,10);
			}

		for(adx=0;adx<5;adx++) {

			switch (adx) {
				default:
				case 0:
					MPRI_SET_NAN(observed);
					mpri_div(observed,dividend,divisor);
					break;
				case 1:
					mpri_set(observed,dividend);
					mpri_div(observed,observed,divisor);
					break;
				case 2:
					mpri_set(observed,divisor);
					mpri_div(observed,dividend,observed);
					break;
				case 3:
					if (mpri_equal(dividend,divisor)) {
						MPRI_SET_NAN(observed);
						mpri_div(observed,dividend,dividend);
						}
					else {
						continue;
						}
					break;
				case 4:
					if (mpri_equal(dividend,divisor)) {
						mpri_set(observed,dividend);
						mpri_div(observed,observed,observed);
						}
					else {
						continue;
						}
					break;
				}

			if ((mpria_mpq_is_finite(observed_lep)) && (mpria_mpq_is_finite(observed_rep))) {
				if ((mpria_mpq_is_finite(expected_lep)) && (mpria_mpq_is_finite(expected_rep))) {
					if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
						status=MPRIA_FAILURE;
						}
					}
				else {
					status=MPRIA_FAILURE;
					}
				}
			else {
				if ((mpria_mpq_is_finite(expected_lep)) || (mpria_mpq_is_finite(expected_rep))) {
					status=MPRIA_FAILURE;
					}
				}

#ifdef TEST_MPRIA_VERY_VERBOSE
			/* may not work for non-finite values (see TODO file for details) */
			gmp_fprintf(stdout,
					"%s:%i>"                                     "\t"
					"[%Qd,%Qd] / [%Qd,%Qd]"                      "\t"
					"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])" "\n"
					,
				(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
				adx,
				dividend_lep,dividend_rep,
				divisor_lep,divisor_rep,
				observed_lep,observed_rep,
				expected_lep,expected_rep
				);
#endif /* TEST_MPRIA_VERY_VERBOSE */
			}

		}

	mpri_clear(observed);
	mpri_clear(expected);
	mpri_clear(dividend);
	mpri_clear(divisor);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_div divides as expected");

	return ; }

int main(int nargs, char * args[]) {

#ifdef TEST_MPRIA_VERBOSE
	mpria_test_verbose(1);
#endif

	test_mpri_add();
	test_mpri_sub();
	test_mpri_mul();
	test_mpri_div();

	return (mpria_test_summary()); }

/* End of file tests/test_arithmetic.c */
