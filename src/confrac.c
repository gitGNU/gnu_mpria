/* src/confrac.c -- C source file */
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

#include <math.h>

#include "mpria.h"
#include "mpria_internal.h"

#if 0
#define MPRI_ATAN_CONFRAC_EXPECTED_ORDER 5 /* odd number: (2 * (number of iterations) + 1) */
#define MPRI_ATAN_CONFRAC_LOG2_EXPECTED_ORDER 1.60943791243410037460075933323 /* log_2 (5) */
#define MPRI_ATAN_NUMBEROF_ARGUMENT_REDUCTION_MIN 2
#else
#if 0
#define MPRI_ATAN_CONFRAC_EXPECTED_ORDER 11 /* odd number: (2 * (number of iterations) + 1) */
#define MPRI_ATAN_CONFRAC_LOG2_EXPECTED_ORDER 2.39789527279837054406194357797 /* log_2 (11) */
#define MPRI_ATAN_NUMBEROF_ARGUMENT_REDUCTION_MIN 2
#else
#if 0
#define MPRI_ATAN_CONFRAC_EXPECTED_ORDER 21 /* odd number: (2 * (number of iterations) + 1) */
#define MPRI_ATAN_CONFRAC_LOG2_EXPECTED_ORDER 3.04452243772342299650059798037 /* log_2 (21) */
#define MPRI_ATAN_NUMBEROF_ARGUMENT_REDUCTION_MIN 3
#else

#define MPRI_ATAN_CONFRAC_EXPECTED_ORDER 41 /* odd number: (2 * (number of iterations) + 1) */
#define MPRI_ATAN_CONFRAC_LOG2_EXPECTED_ORDER 3.71357206670430780386676337304 /* log_2 (41) */
#define MPRI_ATAN_NUMBEROF_ARGUMENT_REDUCTION_MIN 4

#endif
#endif
#endif

static
void mpri_atan_confrac_q_ASGMT(mpri_ptr x,
		mpq_srcptr a,
		mpri_prec_t bits, mpri_srnd_t srnd_mode,
		mpri_asgmt_t asgmt_mode) {
	mpria_workspace * w=mpria_workspace_alloc();
	const int signof_a=mpria_mpq_sgn(a);
	mpq_ptr lep=w->lep;
	mpq_ptr rep=w->rep;

	if (signof_a) {
		mpq_ptr nolispe=w->nolispe;
		mpq_ptr abs_a=w->qi_radicand;
		mpq_ptr kdx=w->qi_augend;
		mpq_ptr p0=w->p0;
		mpq_ptr q0=w->q0;
		mpq_ptr p1=w->p1;
		mpq_ptr q1=w->q1;
		mpq_ptr p2=w->p2;
		mpq_ptr q2=w->q2;
		mpq_ptr a0=w->a0;
		mpq_ptr b0=w->b0;
		mpq_ptr dum=w->dum;
		int flag_directness=0;
		int flag_break=0;

		mpq_abs(abs_a,a);

		mpz_mul(mpq_numref(nolispe),mpq_numref(abs_a),mpq_denref(abs_a));
		mpz_sqrt(mpq_numref(nolispe),mpq_numref(nolispe));
		mpz_add_ui(mpq_numref(nolispe),mpq_numref(nolispe),1UL);
		mpz_set(mpq_denref(nolispe),mpq_denref(abs_a));
		mpq_canonicalize(nolispe);
		mpq_mul_2exp(nolispe,nolispe,((unsigned long int)(bits)+1UL)/2UL);

		MPRIA_MPQ_SET_POS_ONE(p2); MPRIA_MPQ_SET_ZERO(q2);
		MPRIA_MPQ_SET_ZERO(p1); MPRIA_MPQ_SET_POS_ONE(q1);

		MPRIA_MPQ_SET_ZERO(kdx);
		MPRIA_MPQ_SET_POS_ONE(a0);
		mpq_set(b0,abs_a);

		if (0 < signof_a) {
			flag_directness=0;
			}
		else { /* (signof_a < 0) */
			flag_directness=1;
			}

		while (1) {
			mpq_mul(p0,a0,p1); mpq_mul(dum,b0,p2); mpq_add(p0,p0,dum);
			mpq_mul(q0,a0,q1); mpq_mul(dum,b0,q2); mpq_add(q0,q0,dum);
			if (flag_break) break;
			mpria_mpq_min3(dum,q1,p1,p0);
			if ((mpq_cmp(nolispe,dum)) < 0) { /* (nolispe < min(q1,p1,p0)) */
				if (
							(srnd_mode == MPRI_SRND_BCAA) ||
							((srnd_mode == MPRI_SRND_BCAL) && (flag_directness)) ||
							((srnd_mode == MPRI_SRND_BCAR) && (!(flag_directness)))
							) {
					break;
					}
				else {
					flag_break=1;
					}
				}
			mpq_add(kdx,kdx,__mpria_q_pos_one);
			mpq_add(a0,a0,__mpria_q_pos_two);
			mpq_mul(b0,kdx,abs_a);
			mpq_mul(nolispe,nolispe,b0);
			mpq_mul(b0,b0,b0);
			mpq_set(p2,p1); mpq_set(q2,q1);
			mpq_set(p1,p0); mpq_set(q1,q0);
			flag_directness=!(flag_directness);
			}

		if (signof_a < 0) {
			mpq_neg(p0,p0);
			mpq_neg(p1,p1);
			}

		if (flag_directness) {
			mpq_div(lep,p0,q0);
			mpq_div(rep,p1,q1);
			}
		else {
			mpq_div(lep,p1,q1);
			mpq_div(rep,p0,q0);
			}

		}
	else {
		MPRIA_MPQ_SET_ZERO(lep);
		MPRIA_MPQ_SET_ZERO(rep);
		}

	switch (asgmt_mode) {
		case MPRI_ASGMT_OL: mpq_set(mpri_lepref(x),lep); break;
		case MPRI_ASGMT_LR: mpq_set(mpri_lepref(x),lep); /* nobreak */
		case MPRI_ASGMT_OR: mpq_set(mpri_repref(x),rep); break;
		default: MPRI_SET_NAN(x); break;
		}

	mpria_workspace_free(w);
	return ; }

extern
void mpri_2exp_atan(mpri_ptr x, unsigned long int n, mpri_srcptr a, mpri_prec_t bits) {

	if (mpri_is_nonzero(a)) {
		mpria_workspace * w=mpria_workspace_alloc();
		mpq_ptr mag=w->mag;
		mpz_ptr qi_augend=mpq_numref(w->qi_augend);
		mpz_ptr qi_radicand=mpq_numref(w->qi_radicand);
		mpz_ptr qi_denominator=mpq_numref(w->qi_denominator);
		mpri_prec_t numberof_argument_reduction=MPRI_PREC_BITS_NIL;
		mpri_prec_t stib=MPRI_PREC_BITS_NIL;
		mpri_prec_t ardx=0;
		double dum=-1.0;
		mpq_ptr reduced_argument_L=mpri_lepref(x);
		mpq_ptr reduced_argument_R=mpri_repref(x);

#define PROCNAME_REDUCE_ARGUMENT(EndPointIndex) \
	mpz_neg(qi_augend,mpq_denref( reduced_argument_ ## EndPointIndex )); \
	mpz_set(qi_denominator,mpq_numref( reduced_argument_ ## EndPointIndex )); \
	mpz_mul(qi_radicand,qi_augend,qi_augend); mpz_addmul(qi_radicand,qi_denominator,qi_denominator); \
	mpri_set_qi_z_ASGMT(x,qi_augend,qi_radicand,qi_denominator,stib, MPRI_SRND_BCA ## EndPointIndex , MPRI_ASGMT_O ## EndPointIndex );

#define PROCNAME_ATAN_REDUCED_ARGUMENT(EndPointIndex) \
	mpri_atan_confrac_q_ASGMT(x, reduced_argument_ ## EndPointIndex ,stib, MPRI_SRND_BCA ## EndPointIndex , MPRI_ASGMT_O ## EndPointIndex );

#define PROCNAME_ANGLE_BEST_APPROXIMATION(EndPointIndex) \
	mpri_set_qi_z_ASGMT(x,mpq_numref( reduced_argument_ ## EndPointIndex ),__mpria_z_zero,mpq_denref( reduced_argument_ ## EndPointIndex ), \
		stib, MPRI_SRND_BCA ## EndPointIndex , MPRI_ASGMT_O ## EndPointIndex );

		mpri_mag(mag,a);

		dum=
			+((double)(bits)-MPRI_ATAN_CONFRAC_LOG2_EXPECTED_ORDER)/(double)(MPRI_ATAN_CONFRAC_EXPECTED_ORDER)
			+log2(mpq_get_d(mag));
		if (0.0 < dum) {
			numberof_argument_reduction=(mpri_prec_t)(ceil(dum));
			if (numberof_argument_reduction < MPRI_ATAN_NUMBEROF_ARGUMENT_REDUCTION_MIN) {
				numberof_argument_reduction=MPRI_ATAN_NUMBEROF_ARGUMENT_REDUCTION_MIN;
				}
			}
		else {
			numberof_argument_reduction=MPRI_ATAN_NUMBEROF_ARGUMENT_REDUCTION_MIN;
			}

		stib=numberof_argument_reduction+2+n;
		dum=log2((double)(stib));
		stib=bits+stib+(mpri_prec_t)(ceil(dum));

		if (x != a) {
			mpq_set(reduced_argument_L,mpri_lepref(a));
			mpq_set(reduced_argument_R,mpri_repref(a));
			}
		for(ardx=0;ardx<numberof_argument_reduction;ardx++) {
			PROCNAME_REDUCE_ARGUMENT(L)
			PROCNAME_REDUCE_ARGUMENT(R)
			}
		PROCNAME_ATAN_REDUCED_ARGUMENT(L)
		PROCNAME_ATAN_REDUCED_ARGUMENT(R)
		mpri_mul_2exp(x,x,numberof_argument_reduction+n);
		PROCNAME_ANGLE_BEST_APPROXIMATION(L)
		PROCNAME_ANGLE_BEST_APPROXIMATION(R)

#undef PROCNAME_ANGLE_BEST_APPROXIMATION
#undef PROCNAME_ATAN_REDUCED_ARGUMENT
#undef PROCNAME_REDUCE_ARGUMENT

		mpria_workspace_free(w);
		}
	else {
		MPRI_SET_ZERO(x);
		}

	return ; }

/* End of file src/confrac.c */
