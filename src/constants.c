/* src/constants.c -- C source file */
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


static const mp_limb_t __mpria_limb_zero[1]= { 0 & GMP_NUMB_MASK };
static const mp_limb_t __mpria_limb_one[1]=  { 1 & GMP_NUMB_MASK };
static const mp_limb_t __mpria_limb_two[1]=  { 2 & GMP_NUMB_MASK };



const mpz_t __mpria_z_zero= {{1,0,(mp_limb_t *)(__mpria_limb_zero)}};

const mpz_t __mpria_z_pos_one= {{1,+1,(mp_limb_t *)(__mpria_limb_one)}};
const mpz_t __mpria_z_neg_one= {{1,-1,(mp_limb_t *)(__mpria_limb_one)}};
const mpz_t __mpria_z_pos_two= {{1,+1,(mp_limb_t *)(__mpria_limb_two)}};
const mpz_t __mpria_z_neg_two= {{1,-1,(mp_limb_t *)(__mpria_limb_two)}};


const mpq_t __mpria_q_zero= {{{1,0,(mp_limb_t *)(__mpria_limb_zero)},{1,+1,(mp_limb_t *)(__mpria_limb_one)}}};

const mpq_t __mpria_q_pos_one= {{{1,+1,(mp_limb_t *)(__mpria_limb_one)},{1,+1,(mp_limb_t *)(__mpria_limb_one)}}};
const mpq_t __mpria_q_neg_one= {{{1,-1,(mp_limb_t *)(__mpria_limb_one)},{1,+1,(mp_limb_t *)(__mpria_limb_one)}}};
const mpq_t __mpria_q_pos_two= {{{1,+1,(mp_limb_t *)(__mpria_limb_two)},{1,+1,(mp_limb_t *)(__mpria_limb_one)}}};
const mpq_t __mpria_q_neg_two= {{{1,-1,(mp_limb_t *)(__mpria_limb_two)},{1,+1,(mp_limb_t *)(__mpria_limb_one)}}};


const mpri_t __mpria_ri_zero= {{
	{{1,0,(mp_limb_t *)(__mpria_limb_zero)},{1,+1,(mp_limb_t *)(__mpria_limb_one)}},
	{{1,0,(mp_limb_t *)(__mpria_limb_zero)},{1,+1,(mp_limb_t *)(__mpria_limb_one)}}
	}};

const mpri_t __mpria_ri_pos_one= {{
	{{1,+1,(mp_limb_t *)(__mpria_limb_one)},{1,+1,(mp_limb_t *)(__mpria_limb_one)}},
	{{1,+1,(mp_limb_t *)(__mpria_limb_one)},{1,+1,(mp_limb_t *)(__mpria_limb_one)}}
	}};
const mpri_t __mpria_ri_neg_one= {{
	{{1,-1,(mp_limb_t *)(__mpria_limb_one)},{1,+1,(mp_limb_t *)(__mpria_limb_one)}},
	{{1,-1,(mp_limb_t *)(__mpria_limb_one)},{1,+1,(mp_limb_t *)(__mpria_limb_one)}}
	}};

/* End of file src/constants.c */
