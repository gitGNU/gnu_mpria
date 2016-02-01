/* src/numtheory.c -- C source file */
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

#include "mpria.h"
#include "mpria_internal.h"

extern
void mpri_set_qi_z_ASGMT(mpri_ptr x,
		mpz_srcptr a, mpz_srcptr b, mpz_srcptr c,
		mpri_prec_t bits, mpri_srnd_t srnd_mode,
		mpri_asgmt_t asgmt_mode) {
	mpria_workspace * w=mpria_workspace_alloc();
	mpz_ptr nolispe=mpq_numref(w->nolispe);
	mpz_ptr isqrt_d=mpq_numref(w->b0);
	mpq_ptr lep=w->lep;
	mpq_ptr rep=w->rep;
	mpz_ptr p0=mpq_numref(lep);
	mpz_ptr q0=mpq_denref(lep);
	mpz_ptr p1=mpq_numref(rep);
	mpz_ptr q1=mpq_denref(rep);
	mpz_ptr p2=mpq_numref(w->p2);
	mpz_ptr q2=mpq_denref(w->p2);
	mpz_ptr a0=mpq_numref(w->a0);
	mpz_ptr dum=mpq_numref(w->dum);
	int flag_evenness=1;
	int flag_break=0;

	mpz_mul_2exp(nolispe,__mpria_z_pos_one,((unsigned long int)(bits)+1UL)/2UL);

	MPRIA_MPZ_SET_ZERO(p2); MPRIA_MPZ_SET_POS_ONE(q2);
	MPRIA_MPZ_SET_POS_ONE(p1); MPRIA_MPZ_SET_ZERO(q1);

	mpz_sqrtrem(isqrt_d,dum,b);

	if MPRIA_MPZ_IS_ZERO(dum) { /* b is a perfect square */
		mpz_ptr r0=mpq_numref(w->p0);
		mpz_ptr r1=mpq_denref(w->p0);
		mpz_ptr r2=mpq_numref(w->p1);

		mpz_add(p0,a,isqrt_d);
		mpz_set(q0,c);
		mpq_canonicalize(lep);

		mpz_set(r1,q0);
		mpz_set(r0,p0);

		while (1) {
			mpz_fdiv_qr(a0,r2,r0,r1);
			mpz_set(p0,p2); mpz_addmul(p0,a0,p1);
			mpz_set(q0,q2); mpz_addmul(q0,a0,q1);
			if ((MPRIA_MPZ_IS_ZERO(r2)) || (flag_break)) break;
			mpria_mpz_minabs3(dum,q1,p1,p0);
			if ((mpz_cmp(nolispe,dum)) < 0) { /* (nolispe < min(q1,|p1|,|p0|)) */
				if (
							(srnd_mode == MPRI_SRND_BCAA) ||
							((srnd_mode == MPRI_SRND_BCAL) && (flag_evenness)) ||
							((srnd_mode == MPRI_SRND_BCAR) && (!(flag_evenness)))
							) {
					break;
					}
				else {
					flag_break=1;
					}
				}
			mpz_set(r0,r1);
			mpz_set(r1,r2);
			mpz_set(p2,p1); mpz_set(q2,q1);
			mpz_set(p1,p0); mpz_set(q1,q0);
			flag_evenness=!(flag_evenness);
			}

		if MPRIA_MPZ_IS_ZERO(r2) {
			mpq_set(rep,lep);
			}
		else if (!(flag_evenness)) {
			mpq_swap(rep,lep);
			}

		}
	else { /* b is not a perfect square */
		mpz_ptr P0=mpq_numref(w->p0);
		mpz_ptr Q0=mpq_denref(w->p0);
		mpz_ptr d=mpq_denref(w->b0);

		mpz_set(dum,b); mpz_submul(dum,a,a);
		if (mpz_divisible_p(dum,c)) {
			mpz_set(P0,a);
			mpz_set(d,b);
			mpz_set(Q0,c);
#if 0
			mpz_sqrt(isqrt_d,d);
#endif
			}
		else {
			mpz_abs(dum,c);
			mpz_mul(P0,dum,a);
			mpz_mul(Q0,dum,c);
			mpz_mul(dum,c,c);
			mpz_mul(d,dum,b);
			mpz_sqrt(isqrt_d,d);
			}

		while (1) {
			mpz_add(dum,P0,isqrt_d);
			if MPRIA_MPZ_IS_STRICTLY_NEGATIVE(Q0) { mpz_add(dum,dum,__mpria_z_pos_one); }
			mpz_fdiv_q(a0,dum,Q0);
			mpz_set(p0,p2); mpz_addmul(p0,a0,p1);
			mpz_set(q0,q2); mpz_addmul(q0,a0,q1);
			if (flag_break) break;
			mpria_mpz_minabs3(dum,q1,p1,p0);
			if ((mpz_cmp(nolispe,dum)) < 0) { /* (nolispe < min(q1,|p1|,|p0|)) */
				if (
							(srnd_mode == MPRI_SRND_BCAA) ||
							((srnd_mode == MPRI_SRND_BCAL) && (flag_evenness)) ||
							((srnd_mode == MPRI_SRND_BCAR) && (!(flag_evenness)))
							) {
					break;
					}
				else {
					flag_break=1;
					}
				}
			mpz_neg(P0,P0); mpz_addmul(P0,a0,Q0);
			mpz_set(dum,d); mpz_submul(dum,P0,P0); mpz_divexact(Q0,dum,Q0);
			mpz_set(p2,p1); mpz_set(q2,q1);
			mpz_set(p1,p0); mpz_set(q1,q0);
			flag_evenness=!(flag_evenness);
			}

		if (!(flag_evenness)) {
			mpq_swap(rep,lep);
			}

		}

	switch (asgmt_mode) {
		case MPRI_ASGMT_OL: mpq_set(mpri_lepref(x),lep); break;
		case MPRI_ASGMT_LR: mpq_set(mpri_lepref(x),lep); /* nobreak */
		case MPRI_ASGMT_OR: mpq_set(mpri_repref(x),rep); break;
		default: MPRI_SET_NAN(x); break;
		}

	mpria_workspace_free(w);
	return ; }

/* End of file src/numtheory.c */
