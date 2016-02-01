/* tests/test_constants.c -- C source file */
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

void test_mpria_constants(void);

void test_mpria_constants(void) {
	mpz_t z_constant;
	mpq_t q_constant;
	int status=MPRIA_SUCCESS;

	mpz_init(z_constant);
	mpq_init(q_constant);

	mpz_set_ui(z_constant,0UL);
#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"%Zd\n",__mpria_z_zero);
#endif
	if (mpz_cmp(z_constant,__mpria_z_zero)) {
		status=MPRIA_FAILURE;
		}

	mpz_set_ui(z_constant,1UL);
#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"%+Zd\n",__mpria_z_pos_one);
#endif
	if (mpz_cmp(z_constant,__mpria_z_pos_one)) {
		status=MPRIA_FAILURE;
		}

	mpz_set_si(z_constant,-1L);
#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"%+Zd\n",__mpria_z_neg_one);
#endif
	if (mpz_cmp(z_constant,__mpria_z_neg_one)) {
		status=MPRIA_FAILURE;
		}

	mpz_set_ui(z_constant,2UL);
#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"%+Zd\n",__mpria_z_pos_two);
#endif
	if (mpz_cmp(z_constant,__mpria_z_pos_two)) {
		status=MPRIA_FAILURE;
		}

	mpz_set_si(z_constant,-2L);
#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"%+Zd\n",__mpria_z_neg_two);
#endif
	if (mpz_cmp(z_constant,__mpria_z_neg_two)) {
		status=MPRIA_FAILURE;
		}

	mpq_set_ui(q_constant,0UL,1UL);
#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"%Qd\n",__mpria_q_zero);
#endif
	if (!(mpq_equal(q_constant,__mpria_q_zero))) {
		status=MPRIA_FAILURE;
		}

	mpq_set_ui(q_constant,1UL,1UL);
#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"%+Qd\n",__mpria_q_pos_one);
#endif
	if (!(mpq_equal(q_constant,__mpria_q_pos_one))) {
		status=MPRIA_FAILURE;
		}

	mpq_set_si(q_constant,-1L,1UL);
#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"%+Qd\n",__mpria_q_neg_one);
#endif
	if (!(mpq_equal(q_constant,__mpria_q_neg_one))) {
		status=MPRIA_FAILURE;
		}

	mpq_set_ui(q_constant,2UL,1UL);
#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"%+Qd\n",__mpria_q_pos_two);
#endif
	if (!(mpq_equal(q_constant,__mpria_q_pos_two))) {
		status=MPRIA_FAILURE;
		}

	mpq_set_si(q_constant,-2L,1UL);
#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"%+Qd\n",__mpria_q_neg_two);
#endif
	if (!(mpq_equal(q_constant,__mpria_q_neg_two))) {
		status=MPRIA_FAILURE;
		}

#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"[%+Qd,%+Qd]\n",mpri_lepref(__mpria_ri_zero),mpri_repref(__mpria_ri_zero));
#endif
	if ((!(mpq_equal(__mpria_q_zero,mpri_lepref(__mpria_ri_zero)))) || (!(mpq_equal(__mpria_q_zero,mpri_repref(__mpria_ri_zero))))) {
		status=MPRIA_FAILURE;
		}

#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"[%+Qd,%+Qd]\n",mpri_lepref(__mpria_ri_pos_one),mpri_repref(__mpria_ri_pos_one));
#endif
	if ((!(mpq_equal(__mpria_q_pos_one,mpri_lepref(__mpria_ri_pos_one)))) || (!(mpq_equal(__mpria_q_pos_one,mpri_repref(__mpria_ri_pos_one))))) {
		status=MPRIA_FAILURE;
		}

#ifdef TEST_MPRIA_VERY_VERBOSE
	gmp_fprintf(stdout,"[%+Qd,%+Qd]\n",mpri_lepref(__mpria_ri_neg_one),mpri_repref(__mpria_ri_neg_one));
#endif
	if ((!(mpq_equal(__mpria_q_neg_one,mpri_lepref(__mpria_ri_neg_one)))) || (!(mpq_equal(__mpria_q_neg_one,mpri_repref(__mpria_ri_neg_one))))) {
		status=MPRIA_FAILURE;
		}

	mpq_clear(q_constant);
	mpz_clear(z_constant);

	mpria_test(status != MPRIA_SUCCESS,
		"mpria constants are set as required");

	return ; }

int main(int nargs, char * args[]) {

#ifdef TEST_MPRIA_VERBOSE
	mpria_test_verbose(1);
#endif

	test_mpria_constants();

	return (mpria_test_summary()); }

/* End of file tests/test_constants.c */
