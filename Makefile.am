## Makefile.am -- AutoMake master file
## Process this file with automake to produce Makefile.in
## (in this top directory and all subdirectories).
##
## MPRIA - GNU Multi-Precision Rational Interval Arithmetic Library
## Copyright (C) 2009-2016  Jerome Benoit <jgmbenoit@rezozer.net>
##
## This file is part of the GNU MPRIA Library.
##
## The GNU MPRIA Library is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## The GNU MPRIA Library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with the GNU MPRIA Library.  If not, see <http://www.gnu.org/licenses/>.
##

ACLOCAL_AMFLAGS = -I m4

AUTOMAKE_OPTIONS = \
	readme-alpha \
	gnu \
	check-news \
	dist-xz \
	dist-bzip2 \
	std-options

AM_DISTCHECK_CONFIGURE_FLAGS ?= \
	--disable-maintainer-mode \
	--disable-valgrind-tests

SUBDIRS = src tests doc examples #tune

m4datadir = $(datadir)/aclocal
m4data_DATA = \
	m4/mpria_ax_prog_path_gmp_cc.m4 \
	mpria.m4

EXTRA_DIST = \
	README-dev \
	m4/ax_append_flag.m4 \
	$(m4data_DATA) \
	m4/mpria_maintainer.m4 \
	m4/mpria_setup.m4

export TAR_OPTIONS = --owner=0 --group=0 --numeric-owner

## eos
