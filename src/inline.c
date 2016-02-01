/* src/inline.c -- C source file */
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

#define __GMP_FORCE_mpri_init 1
#define __GMP_FORCE_mpri_clear 1
#define __GMP_FORCE_mpri_set 1

#define __GMP_FORCE_mpri_set_qi_q 1
#define __GMP_FORCE_mpri_set_q 1
#define __GMP_FORCE_mpri_set_d 1
#define __GMP_FORCE_mpri_set_sqrt_q 1
#define __GMP_FORCE_mpri_set_rsqrt_q 1
#define __GMP_FORCE_mpri_swap 1

#define __GMP_FORCE_mpri_diam_abs 1
#define __GMP_FORCE_mpri_diam 1
#define __GMP_FORCE_mpri_mig 1
#define __GMP_FORCE_mpri_mag 1
#define __GMP_FORCE_mpri_mid 1

#define __GMP_FORCE_mpri_get_q 1

#define __GMP_FORCE_mpri_add 1
#define __GMP_FORCE_mpri_sub 1

#define __GMP_FORCE_mpri_add_q 1
#define __GMP_FORCE_mpri_sub_q 1
#define __GMP_FORCE_mpri_q_sub 1
#define __GMP_FORCE_mpri_mul_q 1
#define __GMP_FORCE_mpri_mul_2exp 1
#define __GMP_FORCE_mpri_div_q 1
#define __GMP_FORCE_mpri_q_div 1
#define __GMP_FORCE_mpri_div_2exp 1

#define __GMP_FORCE_mpri_neg 1
#define __GMP_FORCE_mpri_abs 1
#define __GMP_FORCE_mpri_inv 1
#define __GMP_FORCE_mpri_sqr 1

#define __GMP_FORCE_mpri_sqrt 1
#define __GMP_FORCE_mpri_rsqrt 1

#define __GMP_FORCE_mpri_atan 1

#define __GMP_FORCE_mpri_equal 1

#define __GMP_FORCE_mpri_is_zero 1
#define __GMP_FORCE_mpri_is_nonzero 1
#define __GMP_FORCE_mpri_has_zero 1
#define __GMP_FORCE_mpri_hasnot_zero 1

#define __GMP_FORCE_mpri_get_left 1
#define __GMP_FORCE_mpri_get_right 1

#include "mpria.h"

/* End of file src/inline.c */
