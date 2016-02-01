/* src/inline_mp.c -- C source file */
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

/* #include "mpria_config.h" */

#define __GMP_FORCE_mpria_mpz_sgn 1
#define __GMP_FORCE_mpria_mpz_minabs3 1

#define __GMP_FORCE_mpria_mpq_sgn 1
#define __GMP_FORCE_mpria_mpq_min3 1
#define __GMP_FORCE_mpria_mpq_is_nan 1
#define __GMP_FORCE_mpria_mpq_is_infinite 1
#define __GMP_FORCE_mpria_mpq_is_finite 1

#include "mpria.h"

/* End of file src/inline_mp.c */
