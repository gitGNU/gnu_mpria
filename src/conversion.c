/* src/conversion.c -- C source file */
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
double mpri_get_d(mpri_srcptr a) {
	mpria_workspace * w=mpria_workspace_alloc();
	mpq_ptr response=w->dum;
	double double_response=MPRIA_NAN;
	mpri_get_q(response,a);
	double_response=mpq_get_d(response);
	mpria_workspace_free(w);
	return (double_response); }

/* End of file src/conversion.c */
