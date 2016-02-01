/* tests/test_numtheory.c -- C source file */
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

#define TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT 4096

#define TEST_MPRIA_VERBOSE

void test_mpri_set_qi_z_ASGMT(void);
void test_mpri_set_qi_q(void);
void test_mpri_set_d(void);
void test_mpri_set_q(void);
void test_mpri_set_sqrt_q(void);
void test_mpri_set_rsqrt_q(void);
void test_mpri_sqrt(void);
void test_mpri_rsqrt(void);

typedef struct {
	const char * a;
	const char * b;
	const char * c;
	mpri_prec_t bits;
	mpri_srnd_t srnd_mode;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_set_qi_z_ASGMT_tuple;

typedef struct {
	const char * a;
	const char * b;
	const char * c;
	mpri_prec_t bits;
	mpri_srnd_t srnd_mode;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_set_qi_q_tuple;

typedef struct {
	const double hfloat;
	mpri_prec_t bits;
	mpri_srnd_t srnd_mode;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_set_d_tuple;

typedef struct {
	const char * rational;
	mpri_prec_t bits;
	mpri_srnd_t srnd_mode;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_set_q_tuple;

typedef struct {
	const char * radicand;
	mpri_prec_t bits;
	mpri_srnd_t srnd_mode;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_set_sqrt_q_tuple;

typedef struct {
	const char * radicand;
	mpri_prec_t bits;
	mpri_srnd_t srnd_mode;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_set_rsqrt_q_tuple;

typedef struct {
	const char * radicand_lep;
	const char * radicand_rep;
	mpri_prec_t bits;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_sqrt_tuple;

typedef struct {
	const char * radicand_lep;
	const char * radicand_rep;
	mpri_prec_t bits;
	const char * expected_lep;
	const char * expected_rep;
	} test_mpri_rsqrt_tuple;

void test_mpri_set_qi_z_ASGMT(void) {
#include "test_mpri_set_qi_z_ASGMT_table.c"
	mpq_t PiC17;
	test_mpri_set_qi_z_ASGMT_tuple * idx=NULL;
	mpz_t a;
	mpz_t b;
	mpz_t c;
	mpri_prec_t bits=0;
	mpri_srnd_t srnd_mode=MPRI_SRND_BCAA;
	mpq_ptr expected_lep=NULL;
	mpq_ptr expected_rep=NULL;
	mpq_ptr observed_lep=NULL;
	mpq_ptr observed_rep=NULL;
	mpri_t expected;
	mpri_t observed;
	mpf_t mpf_expected;
	mpf_t mpf_expected_epsilon;
	mpf_t mpf_observed_error_absolute_lep;
	mpf_t mpf_observed_error_absolute_rep;
	mpf_t mpf_observed_error_absolute;
	mpf_t mpf_observed_error_relative;
	mpf_t mpf_observed_epsilon;
	mpf_t dum;
	int status_extra=MPRIA_SUCCESS;
	int status=MPRIA_SUCCESS;

	mpq_init(PiC17);
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);
	mpri_init(expected);
	mpri_init(observed);
	mpf_init2(mpf_expected,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(dum,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);

	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	mpq_set_ui(PiC17,1068966896,340262731); /* 17th convert of Pi */

	for(idx=test_table;(idx->bits)!=0;idx++) {
		mpz_set_str(a,idx->a,10);
		mpz_set_str(b,idx->b,10);
		mpz_set_str(c,idx->c,10);
		bits=idx->bits;
		srnd_mode=idx->srnd_mode;
		mpq_set_str(expected_lep,idx->expected_lep,10);
		mpq_set_str(expected_rep,idx->expected_rep,10);

		mpf_set_z(mpf_expected,b); mpf_sqrt(mpf_expected,mpf_expected);
		mpf_set_z(dum,a); mpf_add(mpf_expected,mpf_expected,dum);
		mpf_set_z(dum,c); mpf_div(mpf_expected,mpf_expected,dum);
		mpf_set_ui(mpf_expected_epsilon,1UL); mpf_div_2exp(mpf_expected_epsilon,mpf_expected_epsilon,bits);

		MPRI_SET_NAN(observed);
		mpri_set_qi_z_ASGMT(observed,a,b,c,bits,srnd_mode,MPRI_ASGMT_LR);

		mpf_set_q(dum,observed_lep); mpf_sub(dum,mpf_expected,dum); mpf_abs(mpf_observed_error_absolute_lep,dum);
		mpf_set_q(dum,observed_rep); mpf_sub(dum,dum,mpf_expected); mpf_abs(mpf_observed_error_absolute_rep,dum);
		if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_rep);
			}
		else {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_lep);
			}
		if (mpf_sgn(mpf_expected) != 0) {
			mpf_abs(dum,mpf_expected); mpf_div(mpf_observed_error_relative,mpf_observed_error_absolute,dum);
			}
		else {
			mpf_set(mpf_observed_error_relative,mpf_observed_error_absolute);
			}
		if (mpf_cmp(mpf_observed_error_absolute,mpf_observed_error_relative) < 0) {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_relative);
			}
		else {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_absolute);
			}

		if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
			status=MPRIA_FAILURE;
			}

		if (mpq_cmp(observed_rep,observed_lep) < 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (mpf_cmp(mpf_expected_epsilon,mpf_observed_epsilon) <= 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (srnd_mode==MPRI_SRND_BCAL) {
			if (mpf_cmp(mpf_observed_error_absolute_rep,mpf_observed_error_absolute_lep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}
		else if (srnd_mode==MPRI_SRND_BCAR) {
			if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}

#ifdef TEST_MPRIA_VERY_VERBOSE
		gmp_fprintf(stdout,
				"%s:"                                          "\t"
				"(%Zd+sqrt(%Zd))/%Zd"                          "\t"
				"%d"                                           "\t"
				"%s"                                           "\t"
				"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])"   "\t"
				"[observed epsilon %g vs expected epsilon %g]" "\n"
				,
			(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
			a,b,c,
			bits,
			(srnd_mode==MPRI_SRND_BCAL)?"BCAL":
			(srnd_mode==MPRI_SRND_BCAR)?"BCAR":
				"BCAA",
			observed_lep,observed_rep,
			expected_lep,expected_rep,
			mpf_get_d(mpf_observed_epsilon),mpf_get_d(mpf_expected_epsilon)
			);
#endif /* TEST_MPRIA_VERY_VERBOSE */

		MPRI_SET_NAN(observed);
		mpq_set(observed_rep,PiC17);
		mpri_set_qi_z_ASGMT(observed,a,b,c,bits,srnd_mode,MPRI_ASGMT_OL);
		if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,PiC17))))) {
			status=MPRIA_FAILURE;
			}

		MPRI_SET_NAN(observed);
		mpq_set(observed_lep,PiC17);
		mpri_set_qi_z_ASGMT(observed,a,b,c,bits,srnd_mode,MPRI_ASGMT_OR);
		if (!(((mpq_equal(observed_lep,PiC17)) && (mpq_equal(observed_rep,expected_rep))))) {
			status=MPRIA_FAILURE;
			}
		}

	mpf_clear(dum);
	mpf_clear(mpf_observed_epsilon);
	mpf_clear(mpf_observed_error_relative);
	mpf_clear(mpf_observed_error_absolute);
	mpf_clear(mpf_observed_error_absolute_rep);
	mpf_clear(mpf_observed_error_absolute_lep);
	mpf_clear(mpf_expected_epsilon);
	mpf_clear(mpf_expected);
	mpri_clear(observed);
	mpri_clear(expected);
	mpz_clear(c);
	mpz_clear(b);
	mpz_clear(a);
	mpq_clear(PiC17);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_set_qi_z_ASGMT surrounds as expected");

	mpria_test(status_extra != MPRIA_SUCCESS,
		"mpri_set_qi_z_ASGMT does surround as expected (extra)");

	return ; }

void test_mpri_set_qi_q(void) {
#include "test_mpri_set_qi_q_table.c"
	test_mpri_set_qi_q_tuple * idx=NULL;
	mpq_t a;
	mpq_t b;
	mpq_t c;
	mpri_prec_t bits=0;
	mpri_srnd_t srnd_mode=MPRI_SRND_BCAA;
	mpq_ptr expected_lep=NULL;
	mpq_ptr expected_rep=NULL;
	mpq_ptr observed_lep=NULL;
	mpq_ptr observed_rep=NULL;
	mpri_t expected;
	mpri_t observed;
	mpf_t mpf_expected;
	mpf_t mpf_expected_epsilon;
	mpf_t mpf_observed_error_absolute_lep;
	mpf_t mpf_observed_error_absolute_rep;
	mpf_t mpf_observed_error_absolute;
	mpf_t mpf_observed_error_relative;
	mpf_t mpf_observed_epsilon;
	mpf_t dum;
	int status_extra=MPRIA_SUCCESS;
	int status=MPRIA_SUCCESS;

	mpq_init(a);
	mpq_init(b);
	mpq_init(c);
	mpri_init(expected);
	mpri_init(observed);
	mpf_init2(mpf_expected,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(dum,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);

	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->bits)!=0;idx++) {
		mpq_set_str(a,idx->a,10);
		mpq_set_str(b,idx->b,10);
		mpq_set_str(c,idx->c,10);
		bits=idx->bits;
		srnd_mode=idx->srnd_mode;
		mpq_set_str(expected_lep,idx->expected_lep,10);
		mpq_set_str(expected_rep,idx->expected_rep,10);

		mpf_set_q(mpf_expected,b); mpf_sqrt(mpf_expected,mpf_expected);
		mpf_set_q(dum,a); mpf_add(mpf_expected,mpf_expected,dum);
		mpf_set_q(dum,c); mpf_div(mpf_expected,mpf_expected,dum);
		mpf_set_ui(mpf_expected_epsilon,1UL); mpf_div_2exp(mpf_expected_epsilon,mpf_expected_epsilon,bits);

		MPRI_SET_NAN(observed);
		mpri_set_qi_q(observed,a,b,c,bits,srnd_mode);

		mpf_set_q(dum,observed_lep); mpf_sub(dum,mpf_expected,dum); mpf_abs(mpf_observed_error_absolute_lep,dum);
		mpf_set_q(dum,observed_rep); mpf_sub(dum,dum,mpf_expected); mpf_abs(mpf_observed_error_absolute_rep,dum);
		if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_rep);
			}
		else {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_lep);
			}
		if (mpf_sgn(mpf_expected) != 0) {
			mpf_abs(dum,mpf_expected); mpf_div(mpf_observed_error_relative,mpf_observed_error_absolute,dum);
			}
		else {
			mpf_set(mpf_observed_error_relative,mpf_observed_error_absolute);
			}
		if (mpf_cmp(mpf_observed_error_absolute,mpf_observed_error_relative) < 0) {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_relative);
			}
		else {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_absolute);
			}

		if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
			status=MPRIA_FAILURE;
			}

		if (mpq_cmp(observed_rep,observed_lep) < 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (mpf_cmp(mpf_expected_epsilon,mpf_observed_epsilon) <= 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (srnd_mode==MPRI_SRND_BCAL) {
			if (mpf_cmp(mpf_observed_error_absolute_rep,mpf_observed_error_absolute_lep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}
		else if (srnd_mode==MPRI_SRND_BCAR) {
			if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}

#ifdef TEST_MPRIA_VERY_VERBOSE
		gmp_fprintf(stdout,
				"%s:"                                          "\t"
				"(%Qd+sqrt(%Qd))/(%Qd)"                        "\t"
				"%d"                                           "\t"
				"%s"                                           "\t"
				"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])"   "\t"
				"[observed epsilon %g vs expected epsilon %g]" "\n"
				,
			(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
			a,b,c,
			bits,
			(srnd_mode==MPRI_SRND_BCAL)?"BCAL":
			(srnd_mode==MPRI_SRND_BCAR)?"BCAR":
				"BCAA",
			observed_lep,observed_rep,
			expected_lep,expected_rep,
			mpf_get_d(mpf_observed_epsilon),mpf_get_d(mpf_expected_epsilon)
			);
#endif /* TEST_MPRIA_VERY_VERBOSE */

		}

	mpf_clear(dum);
	mpf_clear(mpf_observed_epsilon);
	mpf_clear(mpf_observed_error_relative);
	mpf_clear(mpf_observed_error_absolute);
	mpf_clear(mpf_observed_error_absolute_rep);
	mpf_clear(mpf_observed_error_absolute_lep);
	mpf_clear(mpf_expected_epsilon);
	mpf_clear(mpf_expected);
	mpri_clear(observed);
	mpri_clear(expected);
	mpq_clear(c);
	mpq_clear(b);
	mpq_clear(a);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_set_qi_q surrounds as expected");

	mpria_test(status_extra != MPRIA_SUCCESS,
		"mpri_set_qi_q does surround as expected (extra)");

	return ; }

void test_mpri_set_d(void) {
#include "test_mpri_set_d_table.c"
	test_mpri_set_d_tuple * idx=NULL;
	double hfloat;
	mpri_prec_t bits=0;
	mpri_srnd_t srnd_mode=MPRI_SRND_BCAA;
	mpq_ptr expected_lep=NULL;
	mpq_ptr expected_rep=NULL;
	mpq_ptr observed_lep=NULL;
	mpq_ptr observed_rep=NULL;
	mpri_t expected;
	mpri_t observed;
	mpf_t mpf_expected;
	mpf_t mpf_expected_epsilon;
	mpf_t mpf_observed_error_absolute_lep;
	mpf_t mpf_observed_error_absolute_rep;
	mpf_t mpf_observed_error_absolute;
	mpf_t mpf_observed_error_relative;
	mpf_t mpf_observed_epsilon;
	mpf_t dum;
	int status_extra=MPRIA_SUCCESS;
	int status=MPRIA_SUCCESS;

	mpri_init(expected);
	mpri_init(observed);
	mpf_init2(mpf_expected,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(dum,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);

	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->bits)!=0;idx++) {
		hfloat=idx->hfloat;
		bits=idx->bits;
		srnd_mode=idx->srnd_mode;
		mpq_set_str(expected_lep,idx->expected_lep,10);
		mpq_set_str(expected_rep,idx->expected_rep,10);

		mpf_set_d(mpf_expected,hfloat);
		mpf_set_ui(mpf_expected_epsilon,1UL); mpf_div_2exp(mpf_expected_epsilon,mpf_expected_epsilon,bits);

		MPRI_SET_NAN(observed);
		mpri_set_d(observed,hfloat,bits,srnd_mode);

		mpf_set_q(dum,observed_lep); mpf_sub(dum,mpf_expected,dum); mpf_abs(mpf_observed_error_absolute_lep,dum);
		mpf_set_q(dum,observed_rep); mpf_sub(dum,dum,mpf_expected); mpf_abs(mpf_observed_error_absolute_rep,dum);
		if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_rep);
			}
		else {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_lep);
			}
		if (mpf_sgn(mpf_expected) != 0) {
			mpf_abs(dum,mpf_expected); mpf_div(mpf_observed_error_relative,mpf_observed_error_absolute,dum);
			}
		else {
			mpf_set(mpf_observed_error_relative,mpf_observed_error_absolute);
			}
		if (mpf_cmp(mpf_observed_error_absolute,mpf_observed_error_relative) < 0) {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_relative);
			}
		else {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_absolute);
			}

		if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
			status=MPRIA_FAILURE;
			}

		if (mpq_cmp(observed_rep,observed_lep) < 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (mpf_cmp(mpf_expected_epsilon,mpf_observed_epsilon) <= 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (srnd_mode==MPRI_SRND_BCAL) {
			if (mpf_cmp(mpf_observed_error_absolute_rep,mpf_observed_error_absolute_lep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}
		else if (srnd_mode==MPRI_SRND_BCAR) {
			if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}

#ifdef TEST_MPRIA_VERY_VERBOSE
		gmp_fprintf(stdout,
				"%s:"                                          "\t"
				"(%a|%+2.16e)"                                 "\t"
				"%d"                                           "\t"
				"%s"                                           "\t"
				"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])"   "\t"
				"[observed epsilon %g vs expected epsilon %g]" "\n"
				,
			(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
			hfloat,hfloat,
			bits,
			(srnd_mode==MPRI_SRND_BCAL)?"BCAL":
			(srnd_mode==MPRI_SRND_BCAR)?"BCAR":
				"BCAA",
			observed_lep,observed_rep,
			expected_lep,expected_rep,
			mpf_get_d(mpf_observed_epsilon),mpf_get_d(mpf_expected_epsilon)
			);
#endif /* TEST_MPRIA_VERY_VERBOSE */

		}

	mpf_clear(dum);
	mpf_clear(mpf_observed_epsilon);
	mpf_clear(mpf_observed_error_relative);
	mpf_clear(mpf_observed_error_absolute);
	mpf_clear(mpf_observed_error_absolute_rep);
	mpf_clear(mpf_observed_error_absolute_lep);
	mpf_clear(mpf_expected_epsilon);
	mpf_clear(mpf_expected);
	mpri_clear(observed);
	mpri_clear(expected);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_set_d surrounds as expected");

	mpria_test(status_extra != MPRIA_SUCCESS,
		"mpri_set_d does surround as expected (extra)");

	return ; }

void test_mpri_set_q(void) {
#include "test_mpri_set_q_table.c"
	test_mpri_set_q_tuple * idx=NULL;
	mpq_t rational;
	mpri_prec_t bits=0;
	mpri_srnd_t srnd_mode=MPRI_SRND_BCAA;
	mpq_ptr expected_lep=NULL;
	mpq_ptr expected_rep=NULL;
	mpq_ptr observed_lep=NULL;
	mpq_ptr observed_rep=NULL;
	mpri_t expected;
	mpri_t observed;
	mpf_t mpf_expected;
	mpf_t mpf_expected_epsilon;
	mpf_t mpf_observed_error_absolute_lep;
	mpf_t mpf_observed_error_absolute_rep;
	mpf_t mpf_observed_error_absolute;
	mpf_t mpf_observed_error_relative;
	mpf_t mpf_observed_epsilon;
	mpf_t dum;
	int status_extra=MPRIA_SUCCESS;
	int status=MPRIA_SUCCESS;

	mpq_init(rational);
	mpri_init(expected);
	mpri_init(observed);
	mpf_init2(mpf_expected,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(dum,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);

	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->bits)!=0;idx++) {
		mpq_set_str(rational,idx->rational,10);
		bits=idx->bits;
		srnd_mode=idx->srnd_mode;
		mpq_set_str(expected_lep,idx->expected_lep,10);
		mpq_set_str(expected_rep,idx->expected_rep,10);

		mpf_set_q(mpf_expected,rational);
		mpf_set_ui(mpf_expected_epsilon,1UL); mpf_div_2exp(mpf_expected_epsilon,mpf_expected_epsilon,bits);

		MPRI_SET_NAN(observed);
		mpri_set_q(observed,rational,bits,srnd_mode);

		mpf_set_q(dum,observed_lep); mpf_sub(dum,mpf_expected,dum); mpf_abs(mpf_observed_error_absolute_lep,dum);
		mpf_set_q(dum,observed_rep); mpf_sub(dum,dum,mpf_expected); mpf_abs(mpf_observed_error_absolute_rep,dum);
		if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_rep);
			}
		else {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_lep);
			}
		if (mpf_sgn(mpf_expected) != 0) {
			mpf_abs(dum,mpf_expected); mpf_div(mpf_observed_error_relative,mpf_observed_error_absolute,dum);
			}
		else {
			mpf_set(mpf_observed_error_relative,mpf_observed_error_absolute);
			}
		if (mpf_cmp(mpf_observed_error_absolute,mpf_observed_error_relative) < 0) {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_relative);
			}
		else {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_absolute);
			}

		if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
			status=MPRIA_FAILURE;
			}

		if (mpq_cmp(observed_rep,observed_lep) < 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (mpf_cmp(mpf_expected_epsilon,mpf_observed_epsilon) <= 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (srnd_mode==MPRI_SRND_BCAL) {
			if (mpf_cmp(mpf_observed_error_absolute_rep,mpf_observed_error_absolute_lep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}
		else if (srnd_mode==MPRI_SRND_BCAR) {
			if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}

#ifdef TEST_MPRIA_VERY_VERBOSE
		gmp_fprintf(stdout,
				"%s:"                                          "\t"
				"(%Qd)"                                        "\t"
				"%d"                                           "\t"
				"%s"                                           "\t"
				"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])"   "\t"
				"[observed epsilon %g vs expected epsilon %g]" "\n"
				,
			(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
			rational,
			bits,
			(srnd_mode==MPRI_SRND_BCAL)?"BCAL":
			(srnd_mode==MPRI_SRND_BCAR)?"BCAR":
				"BCAA",
			observed_lep,observed_rep,
			expected_lep,expected_rep,
			mpf_get_d(mpf_observed_epsilon),mpf_get_d(mpf_expected_epsilon)
			);
#endif /* TEST_MPRIA_VERY_VERBOSE */

		}

	mpf_clear(dum);
	mpf_clear(mpf_observed_epsilon);
	mpf_clear(mpf_observed_error_relative);
	mpf_clear(mpf_observed_error_absolute);
	mpf_clear(mpf_observed_error_absolute_rep);
	mpf_clear(mpf_observed_error_absolute_lep);
	mpf_clear(mpf_expected_epsilon);
	mpf_clear(mpf_expected);
	mpri_clear(observed);
	mpri_clear(expected);
	mpq_clear(rational);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_set_q surrounds as expected");

	mpria_test(status_extra != MPRIA_SUCCESS,
		"mpri_set_q does surround as expected (extra)");

	return ; }

void test_mpri_set_sqrt_q(void) {
#include "test_mpri_set_sqrt_q_table.c"
	test_mpri_set_sqrt_q_tuple * idx=NULL;
	mpq_t radicand;
	mpri_prec_t bits=0;
	mpri_srnd_t srnd_mode=MPRI_SRND_BCAA;
	mpq_ptr expected_lep=NULL;
	mpq_ptr expected_rep=NULL;
	mpq_ptr observed_lep=NULL;
	mpq_ptr observed_rep=NULL;
	mpri_t expected;
	mpri_t observed;
	mpf_t mpf_expected;
	mpf_t mpf_expected_epsilon;
	mpf_t mpf_observed_error_absolute_lep;
	mpf_t mpf_observed_error_absolute_rep;
	mpf_t mpf_observed_error_absolute;
	mpf_t mpf_observed_error_relative;
	mpf_t mpf_observed_epsilon;
	mpf_t dum;
	int status_extra=MPRIA_SUCCESS;
	int status=MPRIA_SUCCESS;

	mpq_init(radicand);
	mpri_init(expected);
	mpri_init(observed);
	mpf_init2(mpf_expected,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(dum,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);

	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->bits)!=0;idx++) {
		mpq_set_str(radicand,idx->radicand,10);
		bits=idx->bits;
		srnd_mode=idx->srnd_mode;
		mpq_set_str(expected_lep,idx->expected_lep,10);
		mpq_set_str(expected_rep,idx->expected_rep,10);

		mpf_set_q(mpf_expected,radicand); mpf_sqrt(mpf_expected,mpf_expected);
		mpf_set_ui(mpf_expected_epsilon,1UL); mpf_div_2exp(mpf_expected_epsilon,mpf_expected_epsilon,bits);

		MPRI_SET_NAN(observed);
		mpri_set_sqrt_q(observed,radicand,bits,srnd_mode);

		mpf_set_q(dum,observed_lep); mpf_sub(dum,mpf_expected,dum); mpf_abs(mpf_observed_error_absolute_lep,dum);
		mpf_set_q(dum,observed_rep); mpf_sub(dum,dum,mpf_expected); mpf_abs(mpf_observed_error_absolute_rep,dum);
		if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_rep);
			}
		else {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_lep);
			}
		if (mpf_sgn(mpf_expected) != 0) {
			mpf_abs(dum,mpf_expected); mpf_div(mpf_observed_error_relative,mpf_observed_error_absolute,dum);
			}
		else {
			mpf_set(mpf_observed_error_relative,mpf_observed_error_absolute);
			}
		if (mpf_cmp(mpf_observed_error_absolute,mpf_observed_error_relative) < 0) {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_relative);
			}
		else {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_absolute);
			}

		if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
			status=MPRIA_FAILURE;
			}

		if (mpq_cmp(observed_rep,observed_lep) < 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (mpf_cmp(mpf_expected_epsilon,mpf_observed_epsilon) <= 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (srnd_mode==MPRI_SRND_BCAL) {
			if (mpf_cmp(mpf_observed_error_absolute_rep,mpf_observed_error_absolute_lep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}
		else if (srnd_mode==MPRI_SRND_BCAR) {
			if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}

#ifdef TEST_MPRIA_VERY_VERBOSE
		gmp_fprintf(stdout,
				"%s:"                                          "\t"
				"sqrt(%Qd)"                                    "\t"
				"%d"                                           "\t"
				"%s"                                           "\t"
				"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])"   "\t"
				"[observed epsilon %g vs expected epsilon %g]" "\n"
				,
			(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
			radicand,
			bits,
			(srnd_mode==MPRI_SRND_BCAL)?"BCAL":
			(srnd_mode==MPRI_SRND_BCAR)?"BCAR":
				"BCAA",
			observed_lep,observed_rep,
			expected_lep,expected_rep,
			mpf_get_d(mpf_observed_epsilon),mpf_get_d(mpf_expected_epsilon)
			);
#endif /* TEST_MPRIA_VERY_VERBOSE */

		}

	mpf_clear(dum);
	mpf_clear(mpf_observed_epsilon);
	mpf_clear(mpf_observed_error_relative);
	mpf_clear(mpf_observed_error_absolute);
	mpf_clear(mpf_observed_error_absolute_rep);
	mpf_clear(mpf_observed_error_absolute_lep);
	mpf_clear(mpf_expected_epsilon);
	mpf_clear(mpf_expected);
	mpri_clear(observed);
	mpri_clear(expected);
	mpq_clear(radicand);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_set_sqrt_q surrounds as expected");

	mpria_test(status_extra != MPRIA_SUCCESS,
		"mpri_set_sqrt_q does surround as expected (extra)");

	return ; }

void test_mpri_set_rsqrt_q(void) {
#include "test_mpri_set_rsqrt_q_table.c"
	test_mpri_set_rsqrt_q_tuple * idx=NULL;
	mpq_t radicand;
	mpq_t inv_radicand;
	mpri_prec_t bits=0;
	mpri_srnd_t srnd_mode=MPRI_SRND_BCAA;
	mpq_ptr expected_lep=NULL;
	mpq_ptr expected_rep=NULL;
	mpq_ptr observed_lep=NULL;
	mpq_ptr observed_rep=NULL;
	mpri_t expected;
	mpri_t observed;
	mpf_t mpf_expected;
	mpf_t mpf_expected_epsilon;
	mpf_t mpf_observed_error_absolute_lep;
	mpf_t mpf_observed_error_absolute_rep;
	mpf_t mpf_observed_error_absolute;
	mpf_t mpf_observed_error_relative;
	mpf_t mpf_observed_epsilon;
	mpf_t dum;
	int status_extra=MPRIA_SUCCESS;
	int status=MPRIA_SUCCESS;

	mpq_init(radicand);
	mpq_init(inv_radicand);
	mpri_init(expected);
	mpri_init(observed);
	mpf_init2(mpf_expected,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(dum,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);

	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->bits)!=0;idx++) {
		mpq_set_str(radicand,idx->radicand,10);
		bits=idx->bits;
		srnd_mode=idx->srnd_mode;
		mpq_set_str(expected_lep,idx->expected_lep,10);
		mpq_set_str(expected_rep,idx->expected_rep,10);

		mpq_inv(inv_radicand,radicand);
		mpf_set_q(mpf_expected,inv_radicand); mpf_sqrt(mpf_expected,mpf_expected);
		mpf_set_ui(mpf_expected_epsilon,1UL); mpf_div_2exp(mpf_expected_epsilon,mpf_expected_epsilon,bits);

		MPRI_SET_NAN(observed);
		mpri_set_rsqrt_q(observed,radicand,bits,srnd_mode);

		mpf_set_q(dum,observed_lep); mpf_sub(dum,mpf_expected,dum); mpf_abs(mpf_observed_error_absolute_lep,dum);
		mpf_set_q(dum,observed_rep); mpf_sub(dum,dum,mpf_expected); mpf_abs(mpf_observed_error_absolute_rep,dum);
		if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_rep);
			}
		else {
			mpf_set(mpf_observed_error_absolute,mpf_observed_error_absolute_lep);
			}
		if (mpf_sgn(mpf_expected) != 0) {
			mpf_abs(dum,mpf_expected); mpf_div(mpf_observed_error_relative,mpf_observed_error_absolute,dum);
			}
		else {
			mpf_set(mpf_observed_error_relative,mpf_observed_error_absolute);
			}
		if (mpf_cmp(mpf_observed_error_absolute,mpf_observed_error_relative) < 0) {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_relative);
			}
		else {
			mpf_set(mpf_observed_epsilon,mpf_observed_error_absolute);
			}

		if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
			status=MPRIA_FAILURE;
			}

		if (mpq_cmp(observed_rep,observed_lep) < 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (mpf_cmp(mpf_expected_epsilon,mpf_observed_epsilon) <= 0) {
			status_extra=MPRIA_FAILURE;
			}

		if (srnd_mode==MPRI_SRND_BCAL) {
			if (mpf_cmp(mpf_observed_error_absolute_rep,mpf_observed_error_absolute_lep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}
		else if (srnd_mode==MPRI_SRND_BCAR) {
			if (mpf_cmp(mpf_observed_error_absolute_lep,mpf_observed_error_absolute_rep) < 0) {
				status_extra=MPRIA_FAILURE;
				}
			}

#ifdef TEST_MPRIA_VERY_VERBOSE
		gmp_fprintf(stdout,
				"%s:"                                          "\t"
				"1/sqrt(%Qd)"                                  "\t"
				"%d"                                           "\t"
				"%s"                                           "\t"
				"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])"   "\t"
				"[observed epsilon %g vs expected epsilon %g]" "\n"
				,
			(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
			radicand,
			bits,
			(srnd_mode==MPRI_SRND_BCAL)?"BCAL":
			(srnd_mode==MPRI_SRND_BCAR)?"BCAR":
				"BCAA",
			observed_lep,observed_rep,
			expected_lep,expected_rep,
			mpf_get_d(mpf_observed_epsilon),mpf_get_d(mpf_expected_epsilon)
			);
#endif /* TEST_MPRIA_VERY_VERBOSE */

		}

	mpf_clear(dum);
	mpf_clear(mpf_observed_epsilon);
	mpf_clear(mpf_observed_error_relative);
	mpf_clear(mpf_observed_error_absolute);
	mpf_clear(mpf_observed_error_absolute_rep);
	mpf_clear(mpf_observed_error_absolute_lep);
	mpf_clear(mpf_expected_epsilon);
	mpf_clear(mpf_expected);
	mpri_clear(observed);
	mpri_clear(expected);
	mpq_clear(inv_radicand);
	mpq_clear(radicand);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_set_rsqrt_q surrounds as expected");

	mpria_test(status_extra != MPRIA_SUCCESS,
		"mpri_set_rsqrt_q does surround as expected (extra)");

	return ; }

void test_mpri_sqrt(void) {
#include "test_mpri_sqrt_table.c"
	test_mpri_sqrt_tuple * idx=NULL;
	mpq_ptr radicand_lep=NULL;
	mpq_ptr radicand_rep=NULL;
	mpri_t radicand;
	mpri_prec_t bits=0;
	mpq_ptr expected_lep=NULL;
	mpq_ptr expected_rep=NULL;
	mpq_ptr observed_lep=NULL;
	mpq_ptr observed_rep=NULL;
	mpri_t expected;
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
	int status_extra=MPRIA_SUCCESS;
	int status=MPRIA_SUCCESS;

	mpri_init(radicand);
	mpri_init(expected);
	mpri_init(observed);
	mpf_init2(mpf_expected_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(dum,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);

	radicand_lep=mpri_lepref(radicand);
	radicand_rep=mpri_repref(radicand);
	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->bits)!=0;idx++) {
		mpq_set_str(radicand_lep,idx->radicand_lep,10);
		mpq_set_str(radicand_rep,idx->radicand_rep,10);
		bits=idx->bits;
		mpq_set_str(expected_lep,idx->expected_lep,10);
		mpq_set_str(expected_rep,idx->expected_rep,10);

		mpf_set_q(mpf_expected_lep,radicand_lep); mpf_sqrt(mpf_expected_lep,mpf_expected_lep);
		mpf_set_q(mpf_expected_rep,radicand_rep); mpf_sqrt(mpf_expected_rep,mpf_expected_rep);
		mpf_set_ui(mpf_expected_epsilon,1UL); mpf_div_2exp(mpf_expected_epsilon,mpf_expected_epsilon,bits);

		for(adx=0;adx<2;adx++) {

			switch (adx) {
				default:
				case 0:
					MPRI_SET_NAN(observed);
					mpri_sqrt(observed,radicand,bits);
					break;
				case 1:
					mpri_set(observed,radicand);
					mpri_sqrt(observed,observed,bits);
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

			if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
				status=MPRIA_FAILURE;
				}

			if (mpq_cmp(observed_rep,observed_lep) < 0) {
				status_extra=MPRIA_FAILURE;
				}

			if (mpf_cmp(mpf_expected_epsilon,mpf_observed_epsilon) <= 0) {
				status_extra=MPRIA_FAILURE;
				}

#ifdef TEST_MPRIA_VERY_VERBOSE
			gmp_fprintf(stdout,
					"%s:%i>"                                       "\t"
					"sqrt([%Qd,%Qd])"                              "\t"
					"%d"                                           "\t"
					"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])"   "\t"
					"[observed epsilon %g vs expected epsilon %g]" "\n"
					,
				(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
				adx,
				radicand_lep,radicand_rep,
				bits,
				observed_lep,observed_rep,
				expected_lep,expected_rep,
				mpf_get_d(mpf_observed_epsilon),mpf_get_d(mpf_expected_epsilon)
				);
#endif /* TEST_MPRIA_VERY_VERBOSE */
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
	mpri_clear(expected);
	mpri_clear(radicand);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_sqrt computes as expected");

	mpria_test(status_extra != MPRIA_SUCCESS,
		"mpri_sqrt does compute as expected (extra)");

	return ; }

void test_mpri_rsqrt(void) {
#include "test_mpri_rsqrt_table.c"
	test_mpri_rsqrt_tuple * idx=NULL;
	mpq_ptr radicand_lep=NULL;
	mpq_ptr radicand_rep=NULL;
	mpq_t inv_radicand_aep;
	mpri_t radicand;
	mpri_prec_t bits=0;
	mpq_ptr expected_lep=NULL;
	mpq_ptr expected_rep=NULL;
	mpq_ptr observed_lep=NULL;
	mpq_ptr observed_rep=NULL;
	mpri_t expected;
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
	int status_extra=MPRIA_SUCCESS;
	int status=MPRIA_SUCCESS;

	mpq_init(inv_radicand_aep);
	mpri_init(radicand);
	mpri_init(expected);
	mpri_init(observed);
	mpf_init2(mpf_expected_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_expected_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative_lep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative_rep,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_absolute,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_error_relative,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(mpf_observed_epsilon,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);
	mpf_init2(dum,TEST_MPRIA_NUMTHEORY_MPF_PRECISION_BITS_DEFAULT);

	radicand_lep=mpri_lepref(radicand);
	radicand_rep=mpri_repref(radicand);
	expected_lep=mpri_lepref(expected);
	expected_rep=mpri_repref(expected);
	observed_lep=mpri_lepref(observed);
	observed_rep=mpri_repref(observed);

	for(idx=test_table;(idx->bits)!=0;idx++) {
		mpq_set_str(radicand_lep,idx->radicand_lep,10);
		mpq_set_str(radicand_rep,idx->radicand_rep,10);
		bits=idx->bits;
		mpq_set_str(expected_lep,idx->expected_lep,10);
		mpq_set_str(expected_rep,idx->expected_rep,10);

		mpq_inv(inv_radicand_aep,radicand_rep); mpf_set_q(mpf_expected_lep,inv_radicand_aep); mpf_sqrt(mpf_expected_lep,mpf_expected_lep);
		mpq_inv(inv_radicand_aep,radicand_lep); mpf_set_q(mpf_expected_rep,inv_radicand_aep); mpf_sqrt(mpf_expected_rep,mpf_expected_rep);
		mpf_set_ui(mpf_expected_epsilon,1UL); mpf_div_2exp(mpf_expected_epsilon,mpf_expected_epsilon,bits);

		for(adx=0;adx<2;adx++) {

			switch (adx) {
				default:
				case 0:
					MPRI_SET_NAN(observed);
					mpri_rsqrt(observed,radicand,bits);
					break;
				case 1:
					mpri_set(observed,radicand);
					mpri_rsqrt(observed,observed,bits);
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

			if (!(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep))))) {
				status=MPRIA_FAILURE;
				}

			if (mpq_cmp(observed_rep,observed_lep) < 0) {
				status_extra=MPRIA_FAILURE;
				}

			if (mpf_cmp(mpf_expected_epsilon,mpf_observed_epsilon) <= 0) {
				status_extra=MPRIA_FAILURE;
				}

#ifdef TEST_MPRIA_VERY_VERBOSE
			gmp_fprintf(stdout,
					"%s:%i>"                                       "\t"
					"1/sqrt([%Qd,%Qd])"                            "\t"
					"%d"                                           "\t"
					"(observed [%Qd,%Qd] vs expected [%Qd,%Qd])"   "\t"
					"[observed epsilon %g vs expected epsilon %g]" "\n"
					,
				(((mpq_equal(observed_lep,expected_lep)) && (mpq_equal(observed_rep,expected_rep)))?"PASS":"FAIL"),
				adx,
				radicand_lep,radicand_rep,
				bits,
				observed_lep,observed_rep,
				expected_lep,expected_rep,
				mpf_get_d(mpf_observed_epsilon),mpf_get_d(mpf_expected_epsilon)
				);
#endif /* TEST_MPRIA_VERY_VERBOSE */
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
	mpri_clear(expected);
	mpri_clear(radicand);
	mpq_clear(inv_radicand_aep);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_rsqrt computes as expected");

	mpria_test(status_extra != MPRIA_SUCCESS,
		"mpri_rsqrt does compute as expected (extra)");

	return ; }

int main(int nargs, char * args[]) {

#ifdef TEST_MPRIA_VERBOSE
	mpria_test_verbose(1);
#endif

	test_mpri_set_qi_q();
	test_mpri_set_d();
	test_mpri_set_q();
	test_mpri_set_sqrt_q();
	test_mpri_set_rsqrt_q();
	test_mpri_sqrt();
	test_mpri_rsqrt();

	return (mpria_test_summary()); }

/* End of file tests/test_numtheory.c */
