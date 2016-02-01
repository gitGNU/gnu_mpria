/* tests/mpria_test.h -- C header file */
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

#ifndef __MPRIA_TEST_H__
#define __MPRIA_TEST_H__

#include "mpria.h"

#ifndef MPRIA_SUCCESS
#define MPRIA_SUCCESS  0
#define MPRIA_FAILURE -1
#endif

/* borrow from GSL */
#ifdef NAN
# define MPRIA_NAN NAN
#elif defined(INFINITY)
# define MPRIA_NAN (INFINITY/INFINITY)
#else
# define MPRIA_NAN (0.0/0.0)
#endif

#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

__BEGIN_DECLS


void mpria_test_verbose(int);

void mpria_test(int, const char *, ... );

int mpria_test_summary(void);


__END_DECLS

#endif /* __MPRIA_TEST_H__ */

/* End of file tests/mpria_test.h */
