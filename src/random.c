/* src/random.c -- C source file */
/*
 * MPRIA - GNU Multi-Precision Rational Interval Arithmetic Library
 * Copyright (C) 2016  Jerome Benoit <jgmbenoit@rezozer.net>
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
#include <stdlib.h>

#include "mpria.h"
#include "mpria_internal.h"

#define LENGTHOF_MODULUS_TABLE 1

static const char * __mpria_urandom_modulus_table_hexatrigesimal[LENGTHOF_MODULUS_TABLE] = {
	"3AVVJ5TC0" /* 18th colossally number */
	};

static __mpz_struct __mpria_urandom_modulus_table[LENGTHOF_MODULUS_TABLE] = { {0,0,NULL} };

static void __mpria_urandom_modulus_table_clear(void) {
	if (__mpria_urandom_modulus_table->_mp_alloc) {
		mpz_ptr modulus=__mpria_urandom_modulus_table;
		size_t idx=0;
		for(idx=0;idx<LENGTHOF_MODULUS_TABLE;++modulus,++idx) {
			mpz_clear(modulus);
			}
		}
	return ; }

static void __mpria_urandom_modulus_table_init(void) {
	if (!(__mpria_urandom_modulus_table->_mp_alloc)) {
		const char ** str_modulus=__mpria_urandom_modulus_table_hexatrigesimal;
		mpz_ptr modulus=__mpria_urandom_modulus_table;
		size_t idx=0;
		for(idx=0;idx<LENGTHOF_MODULUS_TABLE;++modulus,++str_modulus,++idx) {
			mpz_init_set_str(modulus,*str_modulus,36);
			}
		atexit(__mpria_urandom_modulus_table_clear);
		}
	return ; }

static
size_t mpri_urandomm_get_modulus_idx(void) { /* might evolve */
	static int uninitialized=1;
	size_t idx=0;

	if (uninitialized) {
		__mpria_urandom_modulus_table_init();
		uninitialized=0;
		}

	return (idx); }

extern
void mpri_urandomm(mpq_ptr a, mpri_srcptr b, gmp_randstate_t state) {
	if (!(mpq_equal(mpri_lepref(b),mpri_repref(b)))) {
		if (mpria_mpq_is_finite(mpri_lepref(b))) {
			if (mpria_mpq_is_finite(mpri_repref(b))) {
				if (mpq_cmp(mpri_lepref(b),mpri_repref(b)) < 0) {
					mpria_workspace * w=mpria_workspace_alloc();
					mpq_ptr urand=w->a0;
					mpq_ptr dnaru=w->b0;
					mpq_ptr lep=w->lep;
					mpq_ptr rep=w->rep;
					const mpz_ptr modulus=__mpria_urandom_modulus_table+mpri_urandomm_get_modulus_idx();
					mpz_ptr dom=mpq_numref(w->dum);
					mpz_add_ui(dom,modulus,1UL);
					mpz_urandomm(mpq_numref(urand),state,dom);
					mpz_sub(mpq_numref(dnaru),dom,mpq_numref(urand));
					mpz_set(mpq_denref(urand),modulus); mpq_canonicalize(urand);
					mpz_set(mpq_denref(dnaru),modulus); mpq_canonicalize(dnaru);
					mpq_mul(lep,dnaru,mpri_lepref(b));
					mpq_mul(rep,urand,mpri_repref(b));
					mpq_add(a,lep,rep);
					mpria_workspace_free(w);
					}
				else { /* empty interval */
					MPRIA_MPQ_SET_NAN(a);
					}
				}
			else if (0 < (mpria_mpq_is_infinite(mpri_repref(b)))) {
#if 0
				mpria_workspace * w=mpria_workspace_alloc();
				/* WIP */
				mpria_workspace_free(w);
#else
				MPRIA_MPQ_SET_POS_INF(a);
#endif
				}
			else { /* invalid interval */
				MPRIA_MPQ_SET_NAN(a);
				}
			}
		else if ((mpria_mpq_is_infinite(mpri_lepref(b))) < 0) {
#if 0
			mpria_workspace * w=mpria_workspace_alloc();
			/* WIP */
			mpria_workspace_free(w);
#else
			MPRIA_MPQ_SET_NEG_INF(a);
#endif
			}
		else { /* invalid interval */
			MPRIA_MPQ_SET_NAN(a);
			}
		}
	else { /* singleton */
		mpq_set(a,mpri_lepref(b));
		}
	return ; }

/* End of file src/random.c */
