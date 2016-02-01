/* tests/results.c -- C source file */
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
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "mpria_test.h"

static unsigned long int mpria_test_numberof_test=0;
static unsigned long int mpria_test_numberof_passed=0;
static unsigned long int mpria_test_numberof_failed=0;

static int mpria_test_verbosity=0;
static int mpria_test_uninitialized=1;

extern
void mpria_test_verbose(int verbosity) {

	mpria_test_verbosity=verbosity;

	return ; }

#define MPRIA_TEST_UPDATE(Status) \
	mpria_test_numberof_test++; \
	if (Status) { \
		mpria_test_numberof_failed++; \
		} \
	else { \
		mpria_test_numberof_passed++; \
		}

static
void mpria_test_initialize(void) {
	const char * ENV_MPRIA_TEST_VERBOSITY=getenv("MPRIA_TEST_VERBOSITY");
	int verbosity=0;

	if (ENV_MPRIA_TEST_VERBOSITY != NULL) {
		if (*ENV_MPRIA_TEST_VERBOSITY != '\0') {
			verbosity=(int)(strtol(ENV_MPRIA_TEST_VERBOSITY,NULL,10));
			}
		}

	mpria_test_verbose(verbosity);

#if 1
	if (1 < mpria_test_verbosity) {
		fprintf(stdout,"==================\n");
		fflush(stdout);
		}
#endif

	mpria_test_uninitialized=0;

	return ; }

extern
void mpria_test(int status, const char * description_template, ... ) {

	if (mpria_test_uninitialized) {
		mpria_test_initialize();
		}

	MPRIA_TEST_UPDATE(status)

	if (mpria_test_verbosity) {
		va_list description_data;
		va_start(description_data,description_template);
		fprintf(stdout,"%s: ",((status)?"FAIL":"PASS"));
		vfprintf(stdout,description_template,description_data);
		fprintf(stdout,"\n");
		fflush(stdout);
		va_end(description_data);
		}
	else if (status) {
		fprintf(stdout,"FAIL: ");
		fprintf(stdout," [%lu]\n",mpria_test_numberof_test);
		fflush(stdout);
		}

	return ; }

#undef MPRIA_TEST_UPDATE

extern
int mpria_test_summary(void) {

	if (mpria_test_uninitialized) {
		mpria_test_initialize();
		}

#if 1
	if (2 < mpria_test_verbosity) {
		fprintf(stdout,
				"SUMMARY: %lu test%s: passed %lu/%lu, failed %lu/%lu\n",
			mpria_test_numberof_test,(mpria_test_numberof_test == 1)?"":"s",
			mpria_test_numberof_passed,mpria_test_numberof_test,
			mpria_test_numberof_failed,mpria_test_numberof_test
			);
		}
#endif

	if (mpria_test_numberof_failed) {
		return (EXIT_FAILURE);
		}

	if (mpria_test_numberof_test != (mpria_test_numberof_passed+mpria_test_numberof_failed)) {
		if (mpria_test_verbosity) {
			fprintf(stdout,
					"TEST RESULTS DO NOT ADD UP %lu != %lu + %lu\n",
				mpria_test_numberof_test,
				mpria_test_numberof_passed,
				mpria_test_numberof_failed
				);
			}
		return (EXIT_FAILURE);
		}

	if (mpria_test_numberof_test == mpria_test_numberof_passed) {
#if 0
		if (!(mpria_test_verbosity)) {
			fprintf(stdout,
					"Completed [%lu/%lu]\n",
				mpria_test_numberof_test,
				mpria_test_numberof_passed
				);
			}
#endif
		return (EXIT_SUCCESS);
		}

	return (EXIT_FAILURE); }

/* End of file tests/results.c */
