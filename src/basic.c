/* src/basic.c -- C source file */
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

#include "mpria.h"
#include "mpria_internal.h"

extern
void mpri_diam_rel(mpq_ptr a, mpri_srcptr b) {
	if (!(mpq_equal(mpri_lepref(b),mpri_repref(b)))) {
		mpria_workspace * w=mpria_workspace_alloc();
		mpq_ptr abs_center=w->mag;
		mpq_add(abs_center,mpri_repref(b),mpri_lepref(b));
		if MPRIA_MPQ_IS_NONZERO(abs_center) {
			mpq_ptr diam_abs=w->mig;
			mpq_div_2exp(abs_center,abs_center,1UL);
			mpq_abs(abs_center,abs_center);
			mpq_sub(diam_abs,mpri_repref(b),mpri_lepref(b));
			mpq_div(a,diam_abs,abs_center);
			}
		else { /* symmetric interval */
			MPRIA_MPQ_SET_NAN(a);
			}
		mpria_workspace_free(w);
		}
	else if MPRIA_MPQ_IS_ZERO(mpri_repref(b)) { /* zero singleton */
		MPRIA_MPQ_SET_NAN(a);
		}
	else { /* nonzero singleton */
		MPRIA_MPQ_SET_ZERO(a);
		}
	return ; }

/* End of file src/basic.c */
