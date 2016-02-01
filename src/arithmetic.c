/* src/arithmetic.c -- C source file */
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
void mpri_mul(mpri_ptr a, mpri_srcptr b, mpri_srcptr c) {
	const int signof_lepof_b=mpria_mpq_sgn(mpri_lepref(b));
	const int signof_repof_b=mpria_mpq_sgn(mpri_repref(b));
	const int signof_lepof_c=mpria_mpq_sgn(mpri_lepref(c));
	const int signof_repof_c=mpria_mpq_sgn(mpri_repref(c));
	if (signof_lepof_b == 0) { /* (lepof_b == 0) */
		if (signof_repof_b == 0) { /* (b == 0) */
			MPRI_SET_ZERO(a);
			}
		else { /* ((lepof_b == 0) and (0 < repof_b)) */
			if (signof_lepof_c == 0) { /* ((lepof_b == 0) and (0 < repof_b)) and (lepof_c == 0) */
				if (signof_repof_c == 0) { /* (c == 0) */
					MPRI_SET_ZERO(a);
					}
				else { /* ((lepof_b == 0) and (0 < repof_b)) and ((lepof_c == 0) and (0 < repof_c)) */
					MPRIA_MPQ_SET_ZERO(mpri_lepref(a));
					mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(c));
					}
				}
			else if (0 < signof_lepof_c) { /* ((lepof_b == 0) and (0 < repof_b)) and (0 < lepof_c <= repof_c) */
				MPRIA_MPQ_SET_ZERO(mpri_lepref(a));
				mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(c));
				}
			else if (signof_repof_c <= 0) { /* ((lepof_b == 0) and (0 < repof_b)) and (lepof_c != 0) and (lepof_c <= repof_c <= 0) */
				mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_lepref(c));
				MPRIA_MPQ_SET_ZERO(mpri_repref(a));
				}
			else { /* ((lepof_b == 0) and (0 < repof_b)) and (lepof_c < 0 < repof_c) */
				if (a != b) {
					mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_lepref(c));
					mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(c));
					}
				else { /* (a == b) */
					mpria_workspace * w=mpria_workspace_alloc();
					mpq_ptr repof_b=w->dum;
					mpq_set(repof_b,mpri_repref(b));
					mpq_mul(mpri_lepref(a),repof_b,mpri_lepref(c));
					mpq_mul(mpri_repref(a),repof_b,mpri_repref(c));
					mpria_workspace_free(w);
					}
				}
			}
		}
	else if (signof_repof_b == 0) { /* ((lepof_b < 0) and (repof_b == 0)) */
		if (signof_lepof_c == 0) { /* ((lepof_b < 0) and (repof_b == 0)) and (lepof_c == 0) */
			if (signof_repof_c == 0) { /* (c == 0) */
				MPRI_SET_ZERO(a);
				}
			else { /* ((lepof_b < 0) and (repof_b == 0)) and ((lepof_c == 0) and (0 < repof_c)) */
				mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
				MPRIA_MPQ_SET_ZERO(mpri_repref(a));
				}
			}
		else if (0 < signof_lepof_c) { /* ((lepof_b < 0) and (repof_b == 0)) and (0 < lepof_c <= repof_c) */
			mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
			MPRIA_MPQ_SET_ZERO(mpri_repref(a));
			}
		else if (signof_repof_c <= 0) { /* ((lepof_b < 0) and (repof_b == 0)) and (lepof_c != 0) and (lepof_c <= repof_c <= 0) */
			mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_lepref(c));
			MPRIA_MPQ_SET_ZERO(mpri_lepref(a));
			}
		else { /* ((lepof_b < 0) and (repof_b == 0)) and (lepof_c < 0 < repof_c) */
			if (a != c) {
				if (a != b) {
					mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
					mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_lepref(c));
					}
				else { /* (a == b) */
					mpria_workspace * w=mpria_workspace_alloc();
					mpq_ptr lepof_b=w->dum;
					mpq_set(lepof_b,mpri_lepref(b));
					mpq_mul(mpri_lepref(a),lepof_b,mpri_repref(c));
					mpq_mul(mpri_repref(a),lepof_b,mpri_lepref(c));
					mpria_workspace_free(w);
					}
				}
			else { /* (a == c) */
				mpq_swap(mpri_lepref(a),mpri_repref(a));
				mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_lepref(a));
				mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_repref(a));
				}
			}
		}
	else if (0 < signof_lepof_b) { /* (0 < lepof_b <= repof_b) */
		if (signof_lepof_c == 0) { /* (0 < lepof_b <= repof_b) and (lepof_c == 0) */
			if (signof_repof_c == 0) { /* (c == 0) */
				MPRI_SET_ZERO(a);
				}
			else { /* (0 < lepof_b <= repof_b) and ((lepof_c == 0) and (0 < repof_c)) */
				MPRIA_MPQ_SET_ZERO(mpri_lepref(a));
				mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(c));
				}
			}
		else if (signof_repof_c == 0) { /* (0 < lepof_b <= repof_b) and (lepof_c < 0) and (repof_c == 0) */
			mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_lepref(c));
			MPRIA_MPQ_SET_ZERO(mpri_repref(a));
			}
		else if (0 < signof_lepof_c) { /* (0 < lepof_b <= repof_b) and (0 < lepof_c <= repof_c) */
			mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_lepref(c));
			mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(c));
			}
		else if (signof_repof_c < 0) { /* (0 < lepof_b <= repof_b) and (lepof_c <= repof_c < 0) */
			if (a != b) {
				mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_lepref(c));
				mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_repref(c));
				}
			else { /* (a == b) */
				mpq_swap(mpri_lepref(a),mpri_repref(a));
				mpq_mul(mpri_lepref(a),mpri_lepref(a),mpri_lepref(c));
				mpq_mul(mpri_repref(a),mpri_repref(a),mpri_repref(c));
				}
			}
		else { /* (0 < lepof_b <= repof_b) and (lepof_c < 0 < repof_c) */
			if (a != b) {
				mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_lepref(c));
				mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(c));
				}
			else { /* (a == b) */
				mpria_workspace * w=mpria_workspace_alloc();
				mpq_ptr repof_b=w->dum;
				mpq_set(repof_b,mpri_repref(b));
				mpq_mul(mpri_lepref(a),repof_b,mpri_lepref(c));
				mpq_mul(mpri_repref(a),repof_b,mpri_repref(c));
				mpria_workspace_free(w);
				}
			}
		}
	else if (signof_repof_b < 0) { /* (lepof_b <= repof_b < 0) */
		if (signof_lepof_c == 0) { /* (lepof_b <= repof_b < 0) and (lepof_c == 0) */
			if (signof_repof_c == 0) { /* (c == 0) */
				MPRI_SET_ZERO(a);
				}
			else { /* (lepof_b <= repof_b < 0) and ((lepof_c == 0) and (0 < repof_c)) */
				mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
				MPRIA_MPQ_SET_ZERO(mpri_repref(a));
				}
			}
		else if (signof_repof_c == 0) { /* (lepof_b <= repof_b < 0) and (lepof_c < 0) and (repof_c == 0) */
			mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_lepref(c));
			MPRIA_MPQ_SET_ZERO(mpri_lepref(a));
			}
		else if (0 < signof_lepof_c) { /* (lepof_b <= repof_b < 0) and (0 < lepof_c <= repof_c) */
			if (a != c) {
				mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
				mpq_mul(mpri_repref(a),mpri_repref(b),mpri_lepref(c));
				}
			else { /* (a == c) */
				mpq_swap(mpri_lepref(a),mpri_repref(a));
				mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_lepref(a));
				mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(a));
				}
			}
		else if (signof_repof_c < 0) { /* (lepof_b <= repof_b < 0) and (lepof_c <= repof_c < 0) */
			if (b != c) {
				if (a != c) {
					if (a != b) { /* (a != b) and (b != c) and (c != a)  */
						mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_repref(c));
						mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_lepref(c));
						}
					else { /* (a == b) and (a != c) */
						mpq_swap(mpri_lepref(a),mpri_repref(a));
						mpq_mul(mpri_lepref(a),mpri_lepref(a),mpri_repref(c));
						mpq_mul(mpri_repref(a),mpri_repref(a),mpri_lepref(c));
						}
					}
				else { /* (a == c) and (a != b) */
					mpq_swap(mpri_lepref(a),mpri_repref(a));
					mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_lepref(a));
					mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_repref(a));
					}
				}
			else { /* (b == c) */
				if (a != b) { /* ((b == c) and (a != b)) => (a != c) */
					mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_repref(b));
					mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_lepref(b));
					}
				else { /* ((a == b) and (b ==c)) => (c == a) */
					mpq_mul(mpri_repref(a),mpri_repref(a),mpri_repref(a));
					mpq_mul(mpri_lepref(a),mpri_lepref(a),mpri_lepref(a));
					mpq_swap(mpri_lepref(a),mpri_repref(a));
					}
				}
			}
		else { /* (lepof_b <= repof_b < 0) and (lepof_c < 0 < repof_c) */
			if (a != c) {
				if (a != b) {
					mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
					mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_lepref(c));
					}
				else { /* (a == b) */
					mpria_workspace * w=mpria_workspace_alloc();
					mpq_ptr lepof_b=w->dum;
					mpq_set(lepof_b,mpri_lepref(b));
					mpq_mul(mpri_lepref(a),lepof_b,mpri_repref(c));
					mpq_mul(mpri_repref(a),lepof_b,mpri_lepref(c));
					mpria_workspace_free(w);
					}
				}
			else { /* (a == c) */
				mpq_swap(mpri_lepref(a),mpri_repref(a));
				mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_lepref(a));
				mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_repref(a));
				}
			}
		}
	else { /* (lepof_b < 0 < repof_b) */
		if (signof_lepof_c == 0) { /* (lepof_b < 0 < repof_b) and (lepof_c == 0) */
			if (signof_repof_c == 0) { /* (c == 0) */
				MPRI_SET_ZERO(a);
				}
			else { /* (lepof_b < 0 < repof_b) and ((lepof_c == 0) and (0 < repof_c)) */
				if (a != c) {
					mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
					mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(c));
					}
				else { /* (a == c) */
					mpria_workspace * w=mpria_workspace_alloc();
					mpq_ptr repof_c=w->dum;
					mpq_set(repof_c,mpri_repref(c));
					mpq_mul(mpri_lepref(a),mpri_lepref(b),repof_c);
					mpq_mul(mpri_repref(a),mpri_repref(b),repof_c);
					mpria_workspace_free(w);
					}
				}
			}
		else if (signof_repof_c == 0) { /* (lepof_b < 0 < repof_b) and (lepof_c < 0) and (repof_c == 0) */
			if (a != c) {
				if (a != b) {
					mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_lepref(c));
					mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_lepref(c));
					}
				else { /* (a == b) */
					mpq_swap(mpri_lepref(a),mpri_repref(a));
					mpq_mul(mpri_lepref(a),mpri_lepref(a),mpri_lepref(c));
					mpq_mul(mpri_repref(a),mpri_repref(a),mpri_lepref(c));
					}
				}
			else { /* (a == c) */
				mpria_workspace * w=mpria_workspace_alloc();
				mpq_ptr lepof_c=w->dum;
				mpq_set(lepof_c,mpri_lepref(c));
				mpq_mul(mpri_lepref(a),mpri_repref(b),lepof_c);
				mpq_mul(mpri_repref(a),mpri_lepref(b),lepof_c);
				mpria_workspace_free(w);
				}
			}
		else if (0 < signof_lepof_c) { /* (lepof_b < 0 < repof_b) and (0 < lepof_c <= repof_c) */
			if (a != c) {
				mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
				mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(c));
				}
			else { /* (a == c) */
				mpria_workspace * w=mpria_workspace_alloc();
				mpq_ptr repof_c=w->dum;
				mpq_set(repof_c,mpri_repref(c));
				mpq_mul(mpri_lepref(a),mpri_lepref(b),repof_c);
				mpq_mul(mpri_repref(a),mpri_repref(b),repof_c);
				mpria_workspace_free(w);
				}
			}
		else if (signof_repof_c < 0) { /* (lepof_b < 0 < repof_b) and (lepof_c <= repof_c < 0) */
			if (a != c) {
				if (a != b) {
					mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_lepref(c));
					mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_lepref(c));
					}
				else { /* (a == b) */
					mpq_swap(mpri_lepref(a),mpri_repref(a));
					mpq_mul(mpri_lepref(a),mpri_lepref(a),mpri_lepref(c));
					mpq_mul(mpri_repref(a),mpri_repref(a),mpri_lepref(c));
					}
				}
			else { /* (a == c) */
				mpria_workspace * w=mpria_workspace_alloc();
				mpq_ptr lepof_c=w->dum;
				mpq_set(lepof_c,mpri_lepref(c));
				mpq_mul(mpri_lepref(a),mpri_repref(b),lepof_c);
				mpq_mul(mpri_repref(a),mpri_lepref(b),lepof_c);
				mpria_workspace_free(w);
				}
			}
		else { /* (lepof_b < 0 < repof_b) and (lepof_c < 0 < repof_c) */
			int cmp=0;
			cmp=mpria_mpq_cmpabs(mpri_lepref(b),mpri_repref(b));
			if (cmp == 0) { /* (|lepof_b| == repof_b) */
				cmp=mpria_mpq_cmpabs(mpri_lepref(c),mpri_repref(c));
				if (cmp <= 0) { /* ((|lepof_b| == repof_b) and ((|lepof_c| == repof_c) or (|lepof_c| < repof_c))) */
					mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
					}
				else { /* (|lepof_b| == repof_b) and (|lepof_c| > repof_c) */
					mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_lepref(c));
					}
				mpq_neg(mpri_repref(a),mpri_lepref(a));
				}
			else if (cmp < 0) { /* (|lepof_b| < repof_b) */
				cmp=mpria_mpq_cmpabs(mpri_lepref(c),mpri_repref(c));
				if (cmp == 0) { /* (|lepof_c| == repof_c) and (|lepof_b| < repof_b) */
					mpq_mul(mpri_lepref(a),mpri_repref(b),mpri_lepref(c));
					mpq_neg(mpri_repref(a),mpri_lepref(a));
					}
				else if (cmp < 0) { /* ((|lepof_b| < repof_b) and (|lepof_c| < repof_c)) => (|lepof_b|.|lepof_c| < repof_b.repof_c) */
					if (b != c) {
						mpria_workspace * w=mpria_workspace_alloc();
						mpq_ptr repof_a=w->dum;
						mpq_mul(repof_a,mpri_repref(b),mpri_repref(c));
						if (a != c) { /* (a != c) and (b != c) */
							mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
							mpq_mul(mpri_repref(a),mpri_repref(b),mpri_lepref(c));
							}
						else { /* ((a == c) and (b != c)) => (a != b) */
							mpq_swap(mpri_lepref(a),mpri_repref(a));
							mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_lepref(a));
							mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(a));
							}
						cmp=mpq_cmp(mpri_lepref(a),mpri_repref(a));
						if (0 < cmp) { /* (repof_b.lepof_c < lepof_b.repof_c) */
							mpq_swap(mpri_lepref(a),mpri_repref(a));
							}
#if 0
						else { /* (lepof_b.repof_c <= repof_b.lepof_c) */
							}
#endif
						mpq_set(mpri_repref(a),repof_a);
						mpria_workspace_free(w);
						}
					else { /* (b == c) */
						mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(b));
						mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(b));
						}
					}
				else { /* ((|lepof_b| < repof_b) and (|lepof_c| > repof_c)) => (|lepof_b|.repof_c < repof_b.|lepof_c|) */
					mpria_workspace * w=mpria_workspace_alloc();
					mpq_ptr lepof_a=w->dum;
					mpq_mul(lepof_a,mpri_repref(b),mpri_lepref(c));
					mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_lepref(c));
					mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(c));
					cmp=mpq_cmp(mpri_lepref(a),mpri_repref(a));
					if (0 < cmp) { /* (repof_b.repof_c < lepof_b.lepof_c) */
						mpq_swap(mpri_repref(a),mpri_lepref(a));
						}
#if 0
					else { /* (lepof_b.lepof_c <= repof_b.repof_c) */
						}
#endif
					mpq_set(mpri_lepref(a),lepof_a);
					mpria_workspace_free(w);
					}
				}
			else { /* (|lepof_b| > repof_b) */
				cmp=mpria_mpq_cmpabs(mpri_lepref(c),mpri_repref(c));
				if (cmp == 0) { /* (|lepof_c| == repof_c) and (|lepof_b| > repof_b) */
					mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
					mpq_neg(mpri_repref(a),mpri_lepref(a));
					}
				else if (cmp < 0) { /* ((|lepof_b| > repof_b) and (|lepof_c| < repof_c)) => (repof_b.|lepof_c| < |lepof_b|.repof_c) */
					mpria_workspace * w=mpria_workspace_alloc();
					mpq_ptr lepof_a=w->dum;
					mpq_mul(lepof_a,mpri_lepref(b),mpri_repref(c));
					mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_lepref(c));
					mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(c));
					cmp=mpq_cmp(mpri_lepref(a),mpri_repref(a));
					if (0 < cmp) { /* (repof_b.repof_c < lepof_b.lepof_c) */
						mpq_swap(mpri_repref(a),mpri_lepref(a));
						}
#if 0
					else { /* (lepof_b.lepof_c <= repof_b.repof_c) */
						}
#endif
					mpq_set(mpri_lepref(a),lepof_a);
					mpria_workspace_free(w);
					}
				else { /* ((|lepof_b| > repof_b) and (|lepof_c| > repof_c)) => (repof_b.repof_c < |lepof_b|.|lepof_c|) */
					if (b != c) {
						mpria_workspace * w=mpria_workspace_alloc();
						mpq_ptr repof_a=w->dum;
						mpq_mul(repof_a,mpri_lepref(b),mpri_lepref(c));
						if (a != c) { /* (a != c) and (b != c) */
							mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
							mpq_mul(mpri_repref(a),mpri_repref(b),mpri_lepref(c));
							}
						else { /* (a == c) and (b != c) => (a != b) */
							mpq_swap(mpri_lepref(a),mpri_repref(a));
							mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_lepref(a));
							mpq_mul(mpri_repref(a),mpri_repref(b),mpri_repref(a));
							}
						cmp=mpq_cmp(mpri_lepref(a),mpri_repref(a));
						if (0 < cmp) { /* (repof_b.lepof_c < lepof_b.repof_c) */
							mpq_swap(mpri_lepref(a),mpri_repref(a));
							}
#if 0
						else { /* (lepof_b.repof_c <= repof_b.lepof_c) */
							}
#endif
						mpq_set(mpri_repref(a),repof_a);
						mpria_workspace_free(w);
						}
					else { /* (b == c) */
						if (a != b) { /* ((a != b) and (b == c)) => (a != c) */
							mpq_mul(mpri_lepref(a),mpri_lepref(b),mpri_repref(b));
							mpq_mul(mpri_repref(a),mpri_lepref(b),mpri_lepref(b));
							}
						else { /* ((a == b) and (b == c)) => (c == a) */
							mpq_mul(mpri_repref(a),mpri_lepref(a),mpri_repref(a));
							mpq_mul(mpri_lepref(a),mpri_lepref(a),mpri_lepref(a));
							mpq_swap(mpri_lepref(a),mpri_repref(a));
							}
						}
					}
				}
			}
		}
	return ; }

extern
void mpri_div(mpri_ptr a, mpri_srcptr b, mpri_srcptr c) {
	const int signof_lepof_b=mpria_mpq_sgn(mpri_lepref(b));
	const int signof_repof_b=mpria_mpq_sgn(mpri_repref(b));
	const int signof_lepof_c=mpria_mpq_sgn(mpri_lepref(c));
	const int signof_repof_c=mpria_mpq_sgn(mpri_repref(c));
	if (0 < signof_lepof_c) { /* (0 < lepof_c <= repof_c) */
		if (signof_lepof_b == 0) { /* (lepof_b == 0) and (0 < lepof_c <= repof_c) */
			if (signof_repof_b == 0) { /* (b == 0) */
				MPRI_SET_ZERO(a);
				}
			else { /* (lepof_b == 0) and (0 < repof_b) and (0 < lepof_c <= repof_c) */
				mpq_div(mpri_repref(a),mpri_repref(b),mpri_lepref(c));
				MPRIA_MPQ_SET_ZERO(mpri_lepref(a));
				}
			}
		else if (signof_repof_b == 0) { /* (repof_b == 0) and (lepof_b < 0) and (0 < lepof_c <= repof_c) */
			mpq_div(mpri_lepref(a),mpri_lepref(b),mpri_lepref(c));
			MPRIA_MPQ_SET_ZERO(mpri_repref(a));
			}
		else if (0 < signof_lepof_b) { /* (0 < lepof_b <= repof_b) and (0 < lepof_c <= repof_c) */
			if (b != c) {
				if (a != c) { /* (a != c) and  (b != c) */
					mpq_div(mpri_lepref(a),mpri_lepref(b),mpri_repref(c));
					mpq_div(mpri_repref(a),mpri_repref(b),mpri_lepref(c));
					}
				else { /* (a == c) and (b != c) */
					mpq_swap(mpri_lepref(a),mpri_repref(a));
					mpq_div(mpri_lepref(a),mpri_lepref(b),mpri_lepref(a));
					mpq_div(mpri_repref(a),mpri_repref(b),mpri_repref(a));
					}
				}
			else { /* (b == c) */
				mpq_div(mpri_lepref(a),mpri_lepref(b),mpri_repref(b));
				mpq_inv(mpri_repref(a),mpri_lepref(a));
				}
			}
		else if (signof_repof_b < 0) { /* (lepof_b <= repof_b < 0) and (0 < lepof_c <= repof_c) */
			mpq_div(mpri_lepref(a),mpri_lepref(b),mpri_lepref(c));
			mpq_div(mpri_repref(a),mpri_repref(b),mpri_repref(c));
			}
		else { /* (lepof_b < 0 < repof_b) and (0 < lepof_c <= repof_c) */
			if (a != c) {
				mpq_div(mpri_lepref(a),mpri_lepref(b),mpri_lepref(c));
				mpq_div(mpri_repref(a),mpri_repref(b),mpri_lepref(c));
				}
			else { /* (a == c) */
				mpria_workspace * w=mpria_workspace_alloc();
				mpq_ptr lepof_c=w->dum;
				mpq_set(lepof_c,mpri_lepref(c));
				mpq_div(mpri_lepref(a),mpri_lepref(b),lepof_c);
				mpq_div(mpri_repref(a),mpri_repref(b),lepof_c);
				mpria_workspace_free(w);
				}
			}
		}
	else if (signof_repof_c < 0) { /* (lepof_c <= repof_c < 0) */
		if (signof_lepof_b == 0) { /* (lepof_b == 0) and (lepof_c <= repof_c < 0) */
			if (signof_repof_b == 0) { /* (b == 0) */
				MPRI_SET_ZERO(a);
				}
			else { /* (lepof_b == 0) and (0 < repof_b) and (lepof_c <= repof_c < 0) */
				mpq_div(mpri_lepref(a),mpri_repref(b),mpri_repref(c));
				MPRIA_MPQ_SET_ZERO(mpri_repref(a));
				}
			}
		else if (signof_repof_b == 0) { /* (repof_b == 0) and (lepof_b < 0) and (lepof_c <= repof_c < 0) */
			mpq_div(mpri_repref(a),mpri_lepref(b),mpri_repref(c));
			MPRIA_MPQ_SET_ZERO(mpri_lepref(a));
			}
		else if (0 < signof_lepof_b) { /* (0 < lepof_b <= repof_b) and (lepof_c <= repof_c < 0) */
			if (a != b) {
				if (a != c) {
					mpq_div(mpri_lepref(a),mpri_repref(b),mpri_repref(c));
					mpq_div(mpri_repref(a),mpri_lepref(b),mpri_lepref(c));
					}
				else { /* (a == c) */
					mpq_swap(mpri_lepref(a),mpri_repref(a));
					mpq_div(mpri_lepref(a),mpri_repref(b),mpri_lepref(a));
					mpq_div(mpri_repref(a),mpri_lepref(b),mpri_repref(a));
					}
				}
			else { /* (a == b) */
				mpq_swap(mpri_lepref(a),mpri_repref(a));
				mpq_div(mpri_lepref(a),mpri_lepref(a),mpri_repref(c));
				mpq_div(mpri_repref(a),mpri_repref(a),mpri_lepref(c));
				}
			}
		else if (signof_repof_b < 0) { /* (lepof_b <= repof_b < 0) and (lepof_c <= repof_c < 0) */
			if (b != c) {
				if (a != b) { /* (a != b) and (b != c) */
					mpq_div(mpri_lepref(a),mpri_repref(b),mpri_lepref(c));
					mpq_div(mpri_repref(a),mpri_lepref(b),mpri_repref(c));
					}
				else { /* (a == b) and (b != c) */
					mpq_swap(mpri_lepref(a),mpri_repref(a));
					mpq_div(mpri_lepref(a),mpri_lepref(a),mpri_lepref(c));
					mpq_div(mpri_repref(a),mpri_repref(a),mpri_repref(c));
					}
				}
			else { /* (b == c */
				mpq_div(mpri_lepref(a),mpri_repref(b),mpri_lepref(b));
				mpq_inv(mpri_repref(a),mpri_lepref(a));
				}
			}
		else { /* (lepof_b < 0 < repof_b) and (lepof_c <= repof_c < 0) */
			if (a != b) {
				if (a != c) {
					mpq_div(mpri_lepref(a),mpri_repref(b),mpri_repref(c));
					mpq_div(mpri_repref(a),mpri_lepref(b),mpri_repref(c));
					}
				else { /* (a == c) */
					mpria_workspace * w=mpria_workspace_alloc();
					mpq_ptr repof_c=w->dum;
					mpq_set(repof_c,mpri_repref(c));
					mpq_div(mpri_lepref(a),mpri_repref(b),repof_c);
					mpq_div(mpri_repref(a),mpri_lepref(b),repof_c);
					mpria_workspace_free(w);
					}
				}
			else { /* (a == b) */
				mpq_swap(mpri_lepref(a),mpri_repref(a));
				mpq_div(mpri_lepref(a),mpri_lepref(a),mpri_repref(c));
				mpq_div(mpri_repref(a),mpri_repref(a),mpri_repref(c));
				}
			}
		}
	else { /* (lepof_c <= 0 <= repof_c) */
		MPRI_SET_NAN(a);
		}
	return ; }

/* End of file src/arithmetic.c */
