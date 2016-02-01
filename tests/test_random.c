/* tests/test_random.c -- C source file */
/*
 * MPRIA - GNU Multi-Precision Rational Interval Arithmetic Library
 * Copyright (C) 2016  Jerome Benoit <jgmbenoit@rezozer.net>
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
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
/* #include <stdint.h> */
/* #include <inttypes.h> */

#include <gmp.h>

#include "mpria_test.h"

/* #define TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_BITCOUNT_2 4UL */
/* #define TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_BITCOUNT_2 5UL */
/* #define TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_BITCOUNT_2 6UL */
#define TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_BITCOUNT_2 7UL

#define TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_BITCOUNT (TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_BITCOUNT_2 << 1)
#define TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_COUNT (1UL << TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_BITCOUNT)

#define MPRIA_TEST_M_2_3 0.666666666666666666666666666666


#define MPRIA_ENVIRONMENT_TEST_RANDSEED_SEED "MPRIA_TEST_RANDSEED_SEED"

#define MPRIA_TEST_RANDSEED_SEED_COUNTOF_ULONG 3

#define MPRIA_TEST_RANDSEED_DEV_RANDOM "/dev/urandom"

#include "test_randseed_seed_builtin_table.c"

static
void mpria_test_randseed_seed(mpz_t seed) {
	const char * env_seed=getenv(MPRIA_ENVIRONMENT_TEST_RANDSEED_SEED);

	if (env_seed == NULL) {
		unsigned long int array_seed[MPRIA_TEST_RANDSEED_SEED_COUNTOF_ULONG]={ 0UL };
		size_t numberof_read_ulong=0;
		FILE * devrandom=NULL;

		if ((devrandom=fopen(MPRIA_TEST_RANDSEED_DEV_RANDOM,"r")) != NULL) {
			numberof_read_ulong=fread(array_seed,sizeof(unsigned long int),MPRIA_TEST_RANDSEED_SEED_COUNTOF_ULONG,devrandom);
			fclose(devrandom);
			}

		if (numberof_read_ulong == MPRIA_TEST_RANDSEED_SEED_COUNTOF_ULONG) {
			mpz_import(seed,MPRIA_TEST_RANDSEED_SEED_COUNTOF_ULONG,1,sizeof(unsigned long int),0,0,array_seed);
			}
		else {
			const size_t sizeof_seed_builtin_table=sizeof(mpria_test_randseed_seed_builtin_table_b62)/sizeof(const char *);
			const time_t hcope=time(NULL);
			const size_t epoch=(0<hcope)?(size_t)(hcope):sizeof_seed_builtin_table/2;
			const size_t ppid=(size_t)(getppid());
			const size_t pid=(size_t)(getpid());
			const size_t sdx=epoch+ppid+pid;
			mpz_set_str(seed,mpria_test_randseed_seed_builtin_table_b62[sdx%sizeof_seed_builtin_table],62);
			}
		}
	else {
		mpz_set_str(seed,env_seed,10);
		}

	return ; }


/* Donald E. Knuth */
/* "The Art of Computer Programming", Volume 2, third edition */
/* ADDISON 1998 */
/* section 3.3.1, General Test Procedures for Studying Random Data */

#define MPRIA_TEST_STAT_MAX_NUMBEROF_CONSECUTIVE_REJECTION 4

#define MPRIA_TEST_STAT_STATUS_NAS     INT_MIN
#define MPRIA_TEST_STAT_STATUS_REJECT        3  /* 11 */
#define MPRIA_TEST_STAT_STATUS_SUSPECT       1  /* 01 */
#define MPRIA_TEST_STAT_STATUS_ALMOSTSUSPECT 2  /* 10 */
#define MPRIA_TEST_STAT_STATUS_ACCEPT        0  /* 00 */

#define MPRIA_TEST_STAT_STATUS_MASK_REJECT 1
#define MPRIA_TEST_STAT_STATUS_MASK_ALMOST 2

#define MPRIA_TEST_STAT_STATUS_NAS_STR           "NotAStatus"     /* 'N' */
#define MPRIA_TEST_STAT_STATUS_REJECT_STR        "Reject"         /* 'R' */
#define MPRIA_TEST_STAT_STATUS_SUSPECT_STR       "Suspect"        /* 'S' */
#define MPRIA_TEST_STAT_STATUS_ALMOSTSUSPECT_STR "AlmostSuspect"  /* 'A' */
#define MPRIA_TEST_STAT_STATUS_ACCEPT_STR        "accept"         /* 'a' */

#define MPRIA_TEST_STAT_STATUS_IO_BITS_FMT "%c%c"

#define MPRIA_TEST_STAT_STATUS_IO_BITS_ARGS(Status) \
	((Status)&MPRIA_TEST_STAT_STATUS_MASK_ALMOST)?'1':'0',\
	((Status)&MPRIA_TEST_STAT_STATUS_MASK_REJECT)?'1':'0'

static
const char * mpria_test_stat_status_table_str[MPRIA_TEST_STAT_STATUS_REJECT+2] = {
	/* 0 */ MPRIA_TEST_STAT_STATUS_ACCEPT_STR,
	/* 1 */ MPRIA_TEST_STAT_STATUS_SUSPECT_STR,
	/* 2 */ MPRIA_TEST_STAT_STATUS_ALMOSTSUSPECT_STR,
	/* 3 */ MPRIA_TEST_STAT_STATUS_REJECT_STR,
	/* 4 */ MPRIA_TEST_STAT_STATUS_NAS_STR
	};

static
const char * mpria_test_stat_status_stringify(int status) {
	return (
			((status<0)||(MPRIA_TEST_STAT_STATUS_REJECT<status))?
				MPRIA_TEST_STAT_STATUS_NAS_STR:
				 mpria_test_stat_status_table_str[status]
		); }


#define MPRIA_TEST_STAT_CHI2_TABLE_SIZE 6

static
const double mpria_test_stat_chi2_table[MPRIA_TEST_STAT_CHI2_TABLE_SIZE] = {
  -2.33, -1.64, -0.674, /* 0.0,*/ 0.674, 1.64, 2.33
	};

static
const int mpria_test_stat_chi2_table_status[MPRIA_TEST_STAT_CHI2_TABLE_SIZE+2] = {
	MPRIA_TEST_STAT_STATUS_REJECT,
	MPRIA_TEST_STAT_STATUS_SUSPECT,
	MPRIA_TEST_STAT_STATUS_ALMOSTSUSPECT,
	MPRIA_TEST_STAT_STATUS_ACCEPT,
	MPRIA_TEST_STAT_STATUS_ALMOSTSUSPECT,
	MPRIA_TEST_STAT_STATUS_SUSPECT,
	MPRIA_TEST_STAT_STATUS_REJECT,
	MPRIA_TEST_STAT_STATUS_NAS
	};

static
int mpria_test_stat_chi2(size_t dof, double sqr_Chi) {
	int status=MPRIA_TEST_STAT_STATUS_NAS;
	if ((30 < dof) && (isfinite(sqr_Chi)) && (0.0 <= sqr_Chi)) {
		const double double_dof=(double)(dof);
		const double double_sqrt_2_dof=sqrt(2.0*double_dof);
		const double double_dof_m_twothird=double_dof-MPRIA_TEST_M_2_3;
		size_t tdx=0;
		double X2=MPRIA_NAN;
		double dum=MPRIA_NAN;
		status=MPRIA_TEST_STAT_STATUS_REJECT;
		for(tdx=0;tdx<MPRIA_TEST_STAT_CHI2_TABLE_SIZE;tdx++) {
			dum=mpria_test_stat_chi2_table[tdx];
			X2=double_sqrt_2_dof+MPRIA_TEST_M_2_3*dum;
			X2=double_dof_m_twothird+dum*X2;
			if (sqr_Chi <= X2) {
				status=mpria_test_stat_chi2_table_status[tdx];
				break;
				}
			}
		}
	return (status); }


void test_mpri_urandomm(gmp_randstate_t);

typedef struct {
	const char * item_lep;
	const char * item_rep;
	mp_bitcnt_t bitcnt_numberof_category;
	} test_mpri_urandomm_tuple;

void test_mpri_urandomm(gmp_randstate_t randstate) {
	void * (*mpria_allocate_func)(size_t)=NULL;
	void (*mpria_free_func)(void *,size_t)=NULL;
test_mpri_urandomm_tuple test_table[]={
	{"0","1",6},
	{"0","1",7},
	{"0","1",8},
	{"5","6",6},
	{"5","6",7},
	{"5","6",8},
	{"5","7",6},
	{"5","7",7},
	{"5","7",8},
	{"-7/2","7/2",6},
	{"-7/2","7/2",7},
	{"-7/2","7/2",8},
	{"-3/5","7/2",6},
	{"-3/5","7/2",7},
	{"-3/5","7/2",8},
	{"-103/5","7/2",6},
	{"-103/5","7/2",7},
	{"-103/5","7/2",8},
	{"-103/5","1009/2",6},
	{"-103/5","1009/2",7},
	{"-103/5","1009/2",8},
	{NULL,NULL,0}}; /* test_table */
	test_mpri_urandomm_tuple * idx=NULL;
	mpq_ptr item_lep;
	mpq_ptr item_rep;
	mpri_t item;
	mp_bitcnt_t bitcnt_numberof_category=0;
	size_t numberof_category=1;
	size_t numberof_trial=0;
	size_t numberof_rejection=0;
	size_t * tableof_category=NULL;
	mpq_t shift;
	mpq_t scale;
	mpq_t chosen;
	mpq_t nesohc;
	mpz_t yrogetac;
	size_t category=0;
	mpq_t sqr_Zeta;
	mpq_t sqr_Chi;
	size_t * datum=NULL;
	size_t rdx=0;
	int status_chi2=MPRIA_TEST_STAT_STATUS_NAS;
	int status_test=MPRIA_TEST_STAT_STATUS_NAS;
	int status=MPRIA_SUCCESS;

	mp_get_memory_functions(&mpria_allocate_func,NULL,&mpria_free_func);

	mpri_init(item);
	mpq_init(shift);
	mpq_init(scale);
	mpq_init(chosen);
	mpq_init(nesohc);
	mpz_init(yrogetac);
	mpq_init(sqr_Zeta);
	mpq_init(sqr_Chi);

	item_lep=mpri_lepref(item);
	item_rep=mpri_repref(item);

	for(idx=test_table;(idx->bitcnt_numberof_category);idx++) {
		mpq_set_str(item_lep,idx->item_lep,10);
		mpq_set_str(item_rep,idx->item_rep,10);
		bitcnt_numberof_category=idx->bitcnt_numberof_category;
		numberof_category=1U<<bitcnt_numberof_category;
		numberof_trial=TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_COUNT*numberof_category;

		mpq_set(shift,item_lep);
		mpq_sub(scale,item_rep,item_lep);
		mpq_div_2exp(scale,scale,bitcnt_numberof_category);
		mpq_inv(scale,scale);

		tableof_category=(size_t *)((*mpria_allocate_func)((numberof_category+1)*sizeof(size_t)));

		numberof_rejection=0;
		do {
			for(rdx=0,datum=tableof_category;rdx<=numberof_category;datum++,rdx++) { *datum=0; }

			for(rdx=0;rdx<numberof_trial;rdx++) {
				mpri_urandomm(chosen,item,randstate);
				mpq_sub(nesohc,chosen,shift);
				mpq_mul(nesohc,nesohc,scale);
				mpz_fdiv_q(yrogetac,mpq_numref(nesohc),mpq_denref(nesohc));
				category=(size_t)(mpz_get_ui(yrogetac));
				datum=tableof_category+category; ++(*datum);
				}

			MPRIA_MPQ_SET_ZERO(sqr_Chi);
			for(rdx=0,datum=tableof_category;rdx<numberof_category;datum++,rdx++) {
				mpz_set_ui(yrogetac,*datum);
				mpz_sub_ui(yrogetac,yrogetac,TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_COUNT);
				mpq_set_z(sqr_Zeta,yrogetac);
				mpq_div_2exp(sqr_Zeta,sqr_Zeta,TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_BITCOUNT_2);
				mpq_mul(sqr_Zeta,sqr_Zeta,sqr_Zeta);
				mpq_add(sqr_Chi,sqr_Chi,sqr_Zeta);
				}

			status_chi2=mpria_test_stat_chi2(numberof_category-1,mpq_get_d(sqr_Chi));

#ifdef TEST_MPRIA_VERY_VERBOSE
			gmp_fprintf(stdout,
					"%s:%c%c"         " "
					"2^%02u:2^%02u"   "\t"
					"%zu:%03zu:%08zu" "\t"
					MPRIA_TEST_STAT_STATUS_IO_BITS_FMT " %-14s" "\t"
					"Chi2=%g"         "\t"
					"chi2=%g"         "\t"
					"[%Qd,%Qd]"       "\n"
					,
				((status_chi2&MPRIA_TEST_STAT_STATUS_MASK_REJECT)?"FAIL":"PASS"),
					*(mpria_test_stat_status_stringify(status_chi2)),(numberof_rejection)?'!':':',
				TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_BITCOUNT,bitcnt_numberof_category,
				TEST_MPRIA_RANDOM_PERCATEGORY_EXPECTED_COUNT,numberof_category,numberof_trial,
				MPRIA_TEST_STAT_STATUS_IO_BITS_ARGS(status_chi2),mpria_test_stat_status_stringify(status_chi2),
				mpq_get_d(sqr_Chi),
				mpq_get_d(sqr_Chi)/(double)(numberof_category-1),
				item_lep,item_rep
				);
#endif /* TEST_MPRIA_VERY_VERBOSE */

			status_test=status_chi2%2;

			if (!(status_test)) break;
			}
		while (++numberof_rejection < MPRIA_TEST_STAT_MAX_NUMBEROF_CONSECUTIVE_REJECTION);

		if (status_test) {
			status=MPRIA_FAILURE;
			}

		(*mpria_free_func)(tableof_category,(numberof_category+1)*sizeof(size_t)); tableof_category=NULL;
		}

	mpq_clear(sqr_Chi);
	mpq_clear(sqr_Zeta);
	mpz_clear(yrogetac);
	mpq_clear(nesohc);
	mpq_clear(chosen);
	mpq_clear(scale);
	mpq_clear(shift);
	mpri_clear(item);

	mpria_test(status != MPRIA_SUCCESS,
		"mpri_urandomm picks up as expected");

	return ; }

int main(int nargs, char * args[]) {
	gmp_randstate_t randstate;
	mpz_t seed;

	gmp_randinit_mt(randstate);
	mpz_init(seed);

	mpria_test_randseed_seed(seed);

	gmp_fprintf(stdout,"## " MPRIA_ENVIRONMENT_TEST_RANDSEED_SEED "=%Zd\n",seed);
	gmp_randseed(randstate,seed);

#ifdef TEST_MPRIA_VERBOSE
	mpria_test_verbose(1);
#endif

	test_mpri_urandomm(randstate);

	mpz_clear(seed);
	gmp_randclear(randstate);

	return (mpria_test_summary()); }

/* End of file tests/test_random.c */
