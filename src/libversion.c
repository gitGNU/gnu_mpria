/* src/libversion.c -- C source file */
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

#include "mpria.h"

extern
void mpria_libversion_get_numbers(int * major, int * minor, int * micro) {
	if (major) *major=MPRIA_VERSION_MAJOR;
	if (minor) *minor=MPRIA_VERSION_MINOR;
	if (micro) *micro=MPRIA_VERSION_MICRO;
	return ; }

extern
int mpria_libversion_get_number(void) {
	return (MPRIA_VERSION_NUMBER); }

extern
const char * mpria_libversion_get_string(void) {
	return (MPRIA_VERSION_STRING); }

/* see `mpria/m4/mpria_setup.m4' for authoritative details:
 *  return 0 for incompatible library
 *  return 1 for compatible and equal library
 *  return 2 for compatible but not equal library
 */
extern
int mpria_libversion_check_numbers(int major, int minor, int micro) {
	int status=0;

#if 0
	if (major < MPRIA_VERSION_MAJOR) {
		status=1;
		}
	else
#endif
	if (major == MPRIA_VERSION_MAJOR) {
		if (minor < MPRIA_VERSION_MINOR) {
			status=2;
			}
		else if (minor == MPRIA_VERSION_MINOR) {
			if (micro == MPRIA_VERSION_MICRO) {
				status=1;
				}
			else {
				status=2;
				}
			}
		}

	return (status); }

/* End of file src/libversion.c */
