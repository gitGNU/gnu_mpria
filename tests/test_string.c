/* tests/test_string.c -- C source file */
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
#include <limits.h>
/* #include <string.h> */
#include <stdio.h>
/* #include <stdlib.h> */
/* #include <stdint.h> */
/* #include <inttypes.h> */

#include <gmp.h>

#include "mpria_test.h"

void test_mpria_mpz_exp_set_str(void);
void test_mpria_mpq_set_str(void);

typedef struct {
	int base;
	const char * str;
	const char * expected_integer;
	unsigned long int expected_exponent;
	} test_mpria_mpz_exp_set_str_tuple;

typedef struct {
	int base;
	const char * str;
	const char * expected_rational;
	} test_mpria_mpq_set_str_tuple;

void test_mpria_mpz_exp_set_str(void) {
	test_mpria_mpz_exp_set_str_tuple test_table[]={
		{10,"31415","31415",0UL},
		{10,"3.","3",0UL},
		{10,"3.1","31",1UL},
		{10,"3.14","314",2UL},
		{10,"3.141","3141",3UL},
		{10,"3.1415","31415",4UL},
		{10,"-3.14","-314",2UL},
		{10,".3","3",1UL},
		{10,".03","3",2UL},
		{10,".00003","3",5UL},
		{10,"-.03","-3",2UL},
		{10,".","0",0UL},
		{10,"-.","0",0UL},
		{INT_MIN,NULL,NULL,ULONG_MAX}};
	test_mpria_mpz_exp_set_str_tuple * idx=NULL;
	const char * str=NULL;
	int base=INT_MIN;
	mpz_t observed_integer;
	unsigned long int observed_exponent=ULONG_MAX;
	mpz_t expected_integer;
	unsigned long int expected_exponent=ULONG_MAX;
	int status_loop=MPRIA_SUCCESS;
	int status=MPRIA_SUCCESS;

	mpz_init(observed_integer);
	mpz_init(expected_integer);

	for(idx=test_table;(idx->str)!=NULL;idx++) {
		str=idx->str;
		base=idx->base;
		mpz_set_str(expected_integer,idx->expected_integer,base);
		expected_exponent=idx->expected_exponent;

		MPRIA_MPZ_SET_ZERO(observed_integer);
		observed_exponent=ULONG_MAX;
		mpria_mpz_exp_set_str(observed_integer,&observed_exponent,str,base);

		status_loop=MPRIA_SUCCESS;
		if (
				(mpz_cmp(observed_integer,expected_integer)) ||
				(observed_exponent != expected_exponent)
				) {
			status_loop=MPRIA_FAILURE;
			}

#ifdef TEST_MPRIA_VERY_VERBOSE
		gmp_fprintf(stdout,
				"%s:"                                           "\t"
				"(%d)"                                          "\t"
				">%s<"                                          "\t"
				"(observed >%Zd< {%lu} vs expected >%Zd< {%lu}" "\n"
				,
			((status_loop != MPRIA_SUCCESS)?"FAIL":"PASS"),
			base,
			str,
			observed_integer,observed_exponent,
			expected_integer,expected_exponent
			);
#endif /* TEST_MPRIA_VERY_VERBOSE */

		if (status_loop != MPRIA_SUCCESS) {
			status=MPRIA_FAILURE;
			}
		}

	mpz_clear(expected_integer);
	mpz_clear(observed_integer);

	mpria_test(status != MPRIA_SUCCESS,
		"mpria_mpz_exp_set_str sets as required");

	return ; }

void test_mpria_mpq_set_str() {
	test_mpria_mpq_set_str_tuple test_table[]={
		{10,"27182818284590","27182818284590"},
		{10,"2","2"},
		{10,"2.7","27/10"},
		{10,"2.718","1359/500"},
		{10,"2721/1001","2721/1001"},
		{10,"2.721/1.001","2721/1001"},
		{10,"27.21/10","2721/1000"},
		{10,"10/27.21","1000/2721"},
		{10,"-2.721/1.001","-2721/1001"},
		{10,"2.721/-1.001","-2721/1001"},
		{10,"-2.721/-1.001","2721/1001"},
		{10,"0.0/0.0",NULL},
		{10,"2.71/0.0",NULL},
		{10,".","0"},
		{10,"2.71/.",NULL},
		{10,"./.",NULL},
		{10,"-.","0"},
		{10,"2.71/-.",NULL},
		{10,"-./-.",NULL},
		{INT_MIN,NULL,NULL}};
	test_mpria_mpq_set_str_tuple * idx=NULL;
	const char * str=NULL;
	int base=INT_MIN;
	mpq_t observed_rational;
	mpq_t expected_rational;
	int status_loop=MPRIA_SUCCESS;
	int status=MPRIA_SUCCESS;

	mpq_init(observed_rational);
	mpq_init(expected_rational);

	for(idx=test_table;(idx->str)!=NULL;idx++) {
		str=idx->str;
		base=idx->base;
		if ((idx->expected_rational) != NULL) {
			mpq_set_str(expected_rational,idx->expected_rational,base);
			}
		else {
			MPRIA_MPQ_SET_NAN(expected_rational);
			}

		MPRIA_MPQ_SET_NAN(observed_rational);
		mpria_mpq_set_str(observed_rational,str,base);

		status_loop=MPRIA_SUCCESS;
		if (!(mpq_equal(observed_rational,expected_rational))) {
			status_loop=MPRIA_FAILURE;
			}

#ifdef TEST_MPRIA_VERY_VERBOSE
		gmp_fprintf(stdout,
				"%s:"                               "\t"
				"(%d)"                              "\t"
				">%s<"                              "\t"
				"(observed >%Qd< vs expected >%Qd<" "\n"
				,
			((status_loop != MPRIA_SUCCESS)?"FAIL":"PASS"),
			base,
			str,
			observed_rational,
			expected_rational
			);
#endif /* TEST_MPRIA_VERY_VERBOSE */

		if (status_loop != MPRIA_SUCCESS) {
			status=MPRIA_FAILURE;
			}
		}

	mpq_clear(expected_rational);
	mpq_clear(observed_rational);

	mpria_test(status != MPRIA_SUCCESS,
		"mpria_mpq_set_str sets as required");

	return ; }

int main(int nargs, char * args[]) {

#ifdef TEST_MPRIA_VERBOSE
	mpria_test_verbose(1);
#endif

	test_mpria_mpz_exp_set_str();
	test_mpria_mpq_set_str();

	return (mpria_test_summary()); }

/* End of file tests/test_string.c */
