/* src/mpria_internal.h -- C header file */
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

#ifndef __MPRIA_INTERNAL_H__
#define __MPRIA_INTERNAL_H__

#include "mpria.h"

/* borrow from GSL */
#ifdef NAN
# define MPRIA_NAN NAN
#elif defined(INFINITY)
# define MPRIA_NAN (INFINITY/INFINITY)
#else
# define MPRIA_NAN (0.0/0.0)
#endif

typedef struct _mpria_workspace mpria_workspace;

struct _mpria_workspace {
	mpq_t dum;
	mpq_t nolispe;
	mpq_t mig;
	mpq_t mag;
	mpq_t a0;
	mpq_t b0;
	mpq_t p0;
	mpq_t q0;
	mpq_t p1;
	mpq_t q1;
	mpq_t p2;
	mpq_t q2;
	mpq_t lep;
	mpq_t rep;
	mpq_t qi_augend;
	mpq_t qi_radicand;
	mpq_t qi_denominator;
	mpri_t qi;
	mpria_workspace * next;
	};

mpria_workspace * mpria_workspace_alloc(void);

void mpria_workspace_free(mpria_workspace * w);


#endif /* __MPRIA_INTERNAL_H__ */

/* End of file src/mpria_internal.h */
