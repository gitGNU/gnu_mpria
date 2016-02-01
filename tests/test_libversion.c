/* tests/test_libversion.c -- C source file */
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
/* #include <limits.h> */
#include <string.h>
#include <stdio.h>
/* #include <stdlib.h> */
/* #include <stdint.h> */
/* #include <inttypes.h> */

#include <gmp.h>

#include "mpria_test.h"

void test_inconsistency_gmp(void);
void test_mpria_libversion_get(void);
void test_mpria_libversion_check(void);

void test_inconsistency_gmp(void) {
	char gmp_hdr_packed_version_number[]="MM.mm.pp";
	const char * gmp_lib_packed_version_number=NULL;
	int status=MPRIA_SUCCESS;

	gmp_lib_packed_version_number=gmp_version;
	snprintf(gmp_hdr_packed_version_number,sizeof(gmp_hdr_packed_version_number),
			"%u.%u.%u",
		__GNU_MP_VERSION,
		__GNU_MP_VERSION_MINOR,
		__GNU_MP_VERSION_PATCHLEVEL
		);
	if (strcmp(gmp_hdr_packed_version_number,gmp_lib_packed_version_number)) {
		if (__GNU_MP_VERSION_PATCHLEVEL == 0) {
			snprintf(gmp_hdr_packed_version_number,sizeof(gmp_hdr_packed_version_number),
					"%u.%u",
				__GNU_MP_VERSION,
				__GNU_MP_VERSION_MINOR
				);
			if (strcmp(gmp_hdr_packed_version_number,gmp_lib_packed_version_number)) {
				status=MPRIA_FAILURE;
				}
			}
		else {
			status=MPRIA_FAILURE;
			}
		}

	mpria_test(status != MPRIA_SUCCESS,
			"the version numbers of gmp.h (%s) and libgmp (%s) match",
		gmp_hdr_packed_version_number,
		gmp_lib_packed_version_number
		);

	return ; }

void test_mpria_libversion_get(void) {
	int observed_major=-1;
	int observed_minor=-1;
	int observed_micro=-1;
	int observed_packed_version_number=-1;
	int expected_packed_version_number=-1;
	const char * observed_packed_version_string=NULL;
	char expected_packed_version_string[]="MM.mm.pp-EXTRAextraEXTRAextraEXTRAextraEXTRA";
	int status=MPRIA_SUCCESS;

	/* status=MPRIA_SUCCESS; */
	mpria_libversion_get_numbers(&observed_major,&observed_minor,&observed_micro);
	if (
			(observed_major != MPRIA_VERSION_MAJOR) ||
			(observed_minor != MPRIA_VERSION_MINOR) ||
			(observed_micro != MPRIA_VERSION_MICRO)
		) {
		status=MPRIA_FAILURE;
		}
	mpria_test(status != MPRIA_SUCCESS,
		"mpria_libversion_get_numbers gets the correct version numbers");

	status=MPRIA_SUCCESS;
	expected_packed_version_number=MPRIA_VERSION_NUMBER_PACK(
		MPRIA_VERSION_MAJOR,
		MPRIA_VERSION_MINOR,
		MPRIA_VERSION_MICRO
		);
	observed_packed_version_number=mpria_libversion_get_number();
	if (observed_packed_version_number != expected_packed_version_number) {
		status=MPRIA_FAILURE;
		}
	mpria_test(status != MPRIA_SUCCESS,
		"mpria_libversion_get_number gets the correct packed version number");

	status=MPRIA_SUCCESS;
#if 1
	snprintf(expected_packed_version_string,sizeof(expected_packed_version_string),
			"%u.%u.%u%s",
		MPRIA_VERSION_MAJOR,
		MPRIA_VERSION_MINOR,
		MPRIA_VERSION_MICRO,
		MPRIA_VERSION_EXTRA
		);
#else
	snprintf(expected_packed_version_string,sizeof(expected_packed_version_string),
			"%s",
		MPRIA_VERSION_STRING_PACK(
			MPRIA_VERSION_MAJOR,
			MPRIA_VERSION_MINOR,
			MPRIA_VERSION_MICRO,
			MPRIA_VERSION_EXTRA
			)
		);
#endif
	observed_packed_version_string=mpria_libversion_get_string();
	if (strcmp(observed_packed_version_string,expected_packed_version_string)) {
		status=MPRIA_FAILURE;
		}
	mpria_test(status != MPRIA_SUCCESS,
		"mpria_libversion_get_string gets the correct packed version string");

	return ; }

void test_mpria_libversion_check(void) {
	int status=MPRIA_SUCCESS;

	/* status=MPRIA_SUCCESS */
	if ((mpria_libversion_check_numbers(MPRIA_VERSION_MAJOR,MPRIA_VERSION_MINOR,MPRIA_VERSION_MICRO)) != 1) {
		status=MPRIA_FAILURE;
		}
	if ((mpria_libversion_check_numbers(MPRIA_VERSION_MAJOR+1,MPRIA_VERSION_MINOR,MPRIA_VERSION_MICRO)) != 0) {
		status=MPRIA_FAILURE;
		}
	if ((mpria_libversion_check_numbers(MPRIA_VERSION_MAJOR,MPRIA_VERSION_MINOR+1,MPRIA_VERSION_MICRO)) != 0) {
		status=MPRIA_FAILURE;
		}
	if ((mpria_libversion_check_numbers(MPRIA_VERSION_MAJOR,MPRIA_VERSION_MINOR,MPRIA_VERSION_MICRO+1)) != 2) {
		status=MPRIA_FAILURE;
		}
#if (1 < MPRIA_VERSION_MAJOR)
	if ((mpria_libversion_check_numbers(MPRIA_VERSION_MAJOR-1,MPRIA_VERSION_MINOR,MPRIA_VERSION_MICRO)) != 0) {
		status=MPRIA_FAILURE;
		}
#endif
#if (1 < MPRIA_VERSION_MINOR)
	if ((mpria_libversion_check_numbers(MPRIA_VERSION_MAJOR,MPRIA_VERSION_MINOR-1,MPRIA_VERSION_MICRO)) != 2) {
		status=MPRIA_FAILURE;
		}
#endif
	mpria_test(status != MPRIA_SUCCESS,
		"mpria_libversion_check_numbers checks as expected");

	status=MPRIA_FAILURE;
	if (mpria_libversion_check()) {
		status=MPRIA_SUCCESS;
		}
	mpria_test(status != MPRIA_SUCCESS,
		"mpria_libversion_check checks as expected");

	return ; }

int main(int nargs, char * args[]) {

#ifdef TEST_MPRIA_VERBOSE
	mpria_test_verbose(1);
#endif

	test_inconsistency_gmp();
	test_mpria_libversion_get();
	test_mpria_libversion_check();

	return (mpria_test_summary()); }

/* End of file tests/test_libversion.c */
