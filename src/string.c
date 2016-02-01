/* src/string.c -- C source file */
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
#include <string.h>

#include "mpria.h"
#include "mpria_internal.h"

/* see `gmp/mpq/set_str.c' */

extern
int mpria_mpz_exp_set_str(mpz_ptr z,
		unsigned long int * exponent,
		const char * str, int base) {
	const char * dot=NULL;
	int status=0;

	dot=strchr(str,'.');
	if (dot == NULL) {
		status=mpz_set_str(z,str,base);
		*exponent=0UL;
		}
	else { /* (dot != NULL) */
		const size_t lengthof_numerator=strlen(str)-1;
		const size_t lengthof_intpart=(size_t)(dot-str);
		const size_t lengthof_fracpart=strlen(dot+1);
		char str_numerator[lengthof_numerator];
		memcpy(str_numerator,str,lengthof_intpart);
		memcpy(str_numerator+lengthof_intpart,dot+1,lengthof_fracpart);
		str_numerator[lengthof_numerator]='\0';
		if (!(
				(*str_numerator == '\0') ||
				((*str_numerator == '-') && (*(str_numerator+1) == '\0'))
				)) {
			status=mpz_set_str(z,str_numerator,base);
			*exponent=(unsigned long int)(lengthof_fracpart);
			}
		else {
			mpz_set_ui(z,0UL);
			*exponent=0UL;
			status=0;
			}
		}

	return (status); }

extern
int mpria_mpq_set_str(mpq_ptr q, const char * str, int base) {
	const unsigned long int ui_base=(0 < base)?(unsigned long int)(base):10UL;
	const char * slash=NULL;
	int status=0;

	slash=strchr(str,'/');
	if (slash == NULL) {
		unsigned long int exponent=0UL;
		status=mpria_mpz_exp_set_str(mpq_numref(q),&exponent,str,base);
		if (status == 0) {
			mpz_ui_pow_ui(mpq_denref(q),ui_base,exponent);
			mpq_canonicalize(q);
			}
		else { /* (status != 0) */
			MPRIA_MPQ_SET_NAN(q);
			}
		}
	else { /* (slash != NULL) */
		const size_t lengthof_numerator=(size_t)(slash-str);
		char str_numerator[lengthof_numerator+1];
		unsigned long int numerator_exponent=0UL;
		memcpy(str_numerator,str,lengthof_numerator);
		str_numerator[lengthof_numerator]='\0';
		status=mpria_mpz_exp_set_str(mpq_numref(q),&numerator_exponent,str_numerator,base);
		if (status == 0) {
			const size_t lengthof_denominator=strlen(slash+1);
			char str_denominator[lengthof_denominator+1];
			unsigned long int denominator_exponent=0UL;
			memcpy(str_denominator,slash+1,lengthof_denominator);
			str_denominator[lengthof_denominator]='\0';
			status=mpria_mpz_exp_set_str(mpq_denref(q),&denominator_exponent,str_denominator,base);
			if (status == 0) {
				if MPRIA_MPZ_IS_NONZERO(mpq_denref(q)) {
					if (numerator_exponent < denominator_exponent) {
						mpria_workspace * w=mpria_workspace_alloc();
						const unsigned long int exponent=denominator_exponent-numerator_exponent;
						mpz_ptr coeff=mpq_numref(w->dum);
						mpz_ui_pow_ui(coeff,ui_base,exponent);
						mpz_mul(mpq_numref(q),mpq_numref(q),coeff);
						mpria_workspace_free(w);
						}
					else if (denominator_exponent < numerator_exponent) {
						mpria_workspace * w=mpria_workspace_alloc();
						const unsigned long int exponent=numerator_exponent-denominator_exponent;
						mpz_ptr coeff=mpq_numref(w->dum);
						mpz_ui_pow_ui(coeff,ui_base,exponent);
						mpz_mul(mpq_denref(q),mpq_denref(q),coeff);
						mpria_workspace_free(w);
						}
					mpq_canonicalize(q);
					}
				else {
					MPRIA_MPQ_SET_NAN(q);
					}
				}
			else { /* (status != 0) */
				MPRIA_MPQ_SET_NAN(q);
				}
			}
		else { /* (status != 0) */
			MPRIA_MPQ_SET_NAN(q);
			}
		}

	return (status); }

/* End of file src/string.c */
