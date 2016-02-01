/* src/workspace.c -- C source file */
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
#include <stdlib.h>

#include "mpria.h"
#include "mpria_internal.h"

static mpria_workspace * reservoirof_workspace=NULL;

static
void mpria_workspace_clear_free(mpria_workspace * w) {
	static void (*mpria_free_func)(void *,size_t)=NULL;
	static int uninitialized=1;

	if (uninitialized) {
		mp_get_memory_functions(NULL,NULL,&mpria_free_func);
		uninitialized=0;
		}

	if (w != NULL) {
		mpria_workspace_clear_free(w->next); w->next=NULL;
		mpri_clear(w->qi);
		mpq_clear(w->qi_denominator);
		mpq_clear(w->qi_radicand);
		mpq_clear(w->qi_augend);
		mpq_clear(w->rep);
		mpq_clear(w->lep);
		mpq_clear(w->q2);
		mpq_clear(w->p2);
		mpq_clear(w->q1);
		mpq_clear(w->p1);
		mpq_clear(w->q0);
		mpq_clear(w->p0);
		mpq_clear(w->b0);
		mpq_clear(w->a0);
		mpq_clear(w->mag);
		mpq_clear(w->mig);
		mpq_clear(w->nolispe);
		mpq_clear(w->dum);
		(*mpria_free_func)(w,sizeof(mpria_workspace));
		}

	return ; }

static
void mpria_workspace_clear(void) {
	mpria_workspace_clear_free(reservoirof_workspace);
	return ; }

extern
mpria_workspace * mpria_workspace_alloc(void) {
	static void * (*mpria_allocate_func)(size_t)=NULL;
	static int uninitialized=1;
	mpria_workspace * w=NULL;

	if ((w=reservoirof_workspace) != NULL) {
		reservoirof_workspace=w->next;
		}
	else {

		if (uninitialized) {
			mp_get_memory_functions(&mpria_allocate_func,NULL,NULL);
#if HAVE_ATEXIT
			atexit(mpria_workspace_clear);
#endif
			uninitialized=0;
			}

		w=(mpria_workspace *)((*mpria_allocate_func)(sizeof(mpria_workspace)));

		mpq_init(w->dum);
		mpq_init(w->nolispe);
		mpq_init(w->mig);
		mpq_init(w->mag);
		mpq_init(w->a0);
		mpq_init(w->b0);
		mpq_init(w->p0);
		mpq_init(w->q0);
		mpq_init(w->p1);
		mpq_init(w->q1);
		mpq_init(w->p2);
		mpq_init(w->q2);
		mpq_init(w->lep);
		mpq_init(w->rep);
		mpq_init(w->qi_augend);
		mpq_init(w->qi_radicand);
		mpq_init(w->qi_denominator);
		mpri_init(w->qi);

		}

	w->next=NULL;

	return (w); }

extern
void mpria_workspace_free(mpria_workspace * w) {

	if (w != NULL) {
		w->next=reservoirof_workspace;
		reservoirof_workspace=w;
		}

	return ; }

/* End of file src/workspace.c */
