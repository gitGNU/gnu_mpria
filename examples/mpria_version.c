/* examples/mpria_version.c -- C source file */
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

/*
 * cc -o mpria_version mpria_version.c -lmpria -lgmp -lm
 * ./mpria_version
 */

#include <stdio.h>
#include <gmp.h>
#include <mpria.h>

int main(void) {

	printf("GMP:   %s\n",gmp_version);
	printf("MPRIA: %s\n",mpria_version);

	return 0;
}

/* End of file examples/mpria_version.c */
