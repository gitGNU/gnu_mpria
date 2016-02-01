/* tests/test_mpri_sub_table.c -- C input file */
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
 * generation date: 2016/01/21 21:17:37 UTC
 * generation place: NeN
 * generated with: test_mpri_sub_table.cg (GAP 4.7.5)
 * generated by: jgmb <jgmb@NeN>
 *
 * comment: not human readable
 *
 */

test_mpri_sub_tuple test_table[]={
	{"-7/2","-1/3","-7/2","-1/3","-19/6","19/6"},
	{"-7/2","-1/3","-1/7","-1/7","-47/14","-4/21"},
	{"-7/2","-1/3","-1/7","1/7","-51/14","-4/21"},
	{"-7/2","-1/3","0","0","-7/2","-1/3"},
	{"-7/2","-1/3","1/7","1/7","-51/14","-10/21"},
	{"-7/2","17/11","-7/2","17/11","-111/22","111/22"},
	{"-7/2","17/11","-2/3","-2/3","-17/6","73/33"},
	{"-7/2","17/11","-2/3","2/3","-25/6","73/33"},
	{"-7/2","17/11","0","0","-7/2","17/11"},
	{"-7/2","17/11","2/3","2/3","-25/6","29/33"},
	{"-17/5","-7/3","-17/5","-7/3","-16/15","16/15"},
	{"-17/5","-7/3","-4/3","-1/2","-29/10","-1"},
	{"-17/5","-7/3","-1/23","0","-17/5","-158/69"},
	{"-17/5","-7/3","-1/23","3/7","-134/35","-158/69"},
	{"-17/5","-7/3","0","1/23","-396/115","-7/3"},
	{"-17/5","-7/3","1/23","4/3","-71/15","-164/69"},
	{"-17/5","7/3","-17/5","7/3","-86/15","86/15"},
	{"-17/5","7/3","-4/3","-1/2","-29/10","11/3"},
	{"-17/5","7/3","-1/31","0","-17/5","220/93"},
	{"-17/5","7/3","-1/31","2/5","-19/5","220/93"},
	{"-17/5","7/3","0","1/31","-532/155","7/3"},
	{"-17/5","7/3","1/31","4/3","-71/15","214/93"},
	{"-7/3","-1/31","-7/3","-1/31","-214/93","214/93"},
	{"-7/3","-1/31","-7/3","17/5","-86/15","214/93"},
	{"-7/3","0","-7/3","0","-7/3","7/3"},
	{"-7/3","0","-4/3","-1/2","-11/6","4/3"},
	{"-7/3","0","-1/11","0","-7/3","1/11"},
	{"-7/3","0","-1/11","11/7","-82/21","1/11"},
	{"-7/3","0","0","1/11","-80/33","0"},
	{"-7/3","0","1/11","4/3","-11/3","-1/11"},
	{"-7/3","17/5","-7/3","-1/31","-214/93","86/15"},
	{"-7/3","17/5","-7/3","17/5","-86/15","86/15"},
	{"-7/3","17/5","-1/31","0","-7/3","532/155"},
	{"-7/3","17/5","-1/31","1/7","-52/21","532/155"},
	{"-7/3","17/5","0","1/31","-220/93","17/5"},
	{"-7/3","17/5","1/31","7/3","-14/3","522/155"},
	{"-4/3","-1/2","-17/5","-7/3","1","29/10"},
	{"-4/3","-1/2","-17/5","7/3","-11/3","29/10"},
	{"-4/3","-1/2","-7/3","0","-4/3","11/6"},
	{"-4/3","-1/2","-4/3","-1/2","-5/6","5/6"},
	{"-4/3","-1/2","0","7/3","-11/3","-1/2"},
	{"-4/3","-1/2","7/3","17/5","-71/15","-17/6"},
	{"-2/3","-2/3","-7/2","17/11","-73/33","17/6"},
	{"-2/3","-2/3","-2/3","-2/3","0","0"},
	{"-2/3","2/3","-7/2","17/11","-73/33","25/6"},
	{"-2/3","2/3","-2/3","2/3","-4/3","4/3"},
	{"-1/2","-1/2","-1/2","-1/2","0","0"},
	{"-1/2","-1/2","0","7/11","-25/22","-1/2"},
	{"-1/2","0","-1/2","0","-1/2","1/2"},
	{"-1/2","0","0","7/3","-17/6","0"},
	{"-1/2","0","7/3","17/5","-39/10","-7/3"},
	{"-1/2","5/17","-1/2","5/17","-27/34","27/34"},
	{"-1/2","5/17","7/3","17/5","-39/10","-104/51"},
	{"-1/2","1/2","-1/2","1/2","-1","1"},
	{"-1/2","1/2","0","7/11","-25/22","1/2"},
	{"-1/2","7/11","-1/2","7/11","-25/22","25/22"},
	{"-1/2","7/11","0","7/3","-17/6","7/11"},
	{"-1/3","-1/3","-1/3","-1/3","0","0"},
	{"-1/3","-1/3","-5/17","0","-1/3","-2/51"},
	{"-1/3","1/3","-1/3","1/3","-2/3","2/3"},
	{"-1/3","1/3","-5/17","0","-1/3","32/51"},
	{"-5/17","0","-1/3","-1/3","2/51","1/3"},
	{"-5/17","0","-1/3","1/3","-32/51","1/3"},
	{"-5/17","0","-5/17","0","-5/17","5/17"},
	{"-5/17","0","0","0","-5/17","0"},
	{"-5/17","0","1/3","1/3","-32/51","-1/3"},
	{"-1/7","-1/7","-7/2","-1/3","4/21","47/14"},
	{"-1/7","-1/7","-1/7","-1/7","0","0"},
	{"-1/7","-1/7","1/2","11/3","-80/21","-9/14"},
	{"-1/7","1/7","-7/2","-1/3","4/21","51/14"},
	{"-1/7","1/7","-1/7","1/7","-2/7","2/7"},
	{"-1/7","1/7","1/2","11/3","-80/21","-5/14"},
	{"-1/11","0","-7/3","0","-1/11","7/3"},
	{"-1/11","0","-1/11","0","-1/11","1/11"},
	{"-1/11","11/7","-7/3","0","-1/11","82/21"},
	{"-1/11","11/7","-1/11","11/7","-128/77","128/77"},
	{"-1/23","0","-17/5","-7/3","158/69","17/5"},
	{"-1/23","0","-1/23","0","-1/23","1/23"},
	{"-1/23","3/7","-17/5","-7/3","158/69","134/35"},
	{"-1/23","3/7","-1/23","3/7","-76/161","76/161"},
	{"-1/31","0","-17/5","7/3","-220/93","17/5"},
	{"-1/31","0","-7/3","17/5","-532/155","7/3"},
	{"-1/31","0","-1/31","0","-1/31","1/31"},
	{"-1/31","1/7","-7/3","17/5","-532/155","52/21"},
	{"-1/31","1/7","-1/31","1/7","-38/217","38/217"},
	{"-1/31","2/5","-17/5","7/3","-220/93","19/5"},
	{"-1/31","2/5","-1/31","2/5","-67/155","67/155"},
	{"0","0","-7/2","-1/3","1/3","7/2"},
	{"0","0","-7/2","17/11","-17/11","7/2"},
	{"0","0","-5/17","0","0","5/17"},
	{"0","0","0","0","0","0"},
	{"0","0","0","7/11","-7/11","0"},
	{"0","0","1/2","11/3","-11/3","-1/2"},
	{"0","1/31","-17/5","7/3","-7/3","532/155"},
	{"0","1/31","-7/3","17/5","-17/5","220/93"},
	{"0","1/31","0","1/31","-1/31","1/31"},
	{"0","1/23","-17/5","-7/3","7/3","396/115"},
	{"0","1/23","0","1/23","-1/23","1/23"},
	{"0","1/11","-7/3","0","0","80/33"},
	{"0","1/11","0","1/11","-1/11","1/11"},
	{"0","1/2","0","1/2","-1/2","1/2"},
	{"0","1/2","0","7/3","-7/3","1/2"},
	{"0","1/2","7/3","17/5","-17/5","-11/6"},
	{"0","7/11","-1/2","-1/2","1/2","25/22"},
	{"0","7/11","-1/2","1/2","-1/2","25/22"},
	{"0","7/11","0","0","0","7/11"},
	{"0","7/11","0","7/11","-7/11","7/11"},
	{"0","7/11","1/2","1/2","-1/2","3/22"},
	{"0","7/3","-4/3","-1/2","1/2","11/3"},
	{"0","7/3","-1/2","0","0","17/6"},
	{"0","7/3","-1/2","7/11","-7/11","17/6"},
	{"0","7/3","0","1/2","-1/2","7/3"},
	{"0","7/3","0","7/3","-7/3","7/3"},
	{"0","7/3","1/2","4/3","-4/3","11/6"},
	{"1/31","4/3","-17/5","7/3","-214/93","71/15"},
	{"1/31","4/3","1/31","4/3","-121/93","121/93"},
	{"1/31","7/3","-7/3","17/5","-522/155","14/3"},
	{"1/31","7/3","1/31","7/3","-214/93","214/93"},
	{"1/23","4/3","-17/5","-7/3","164/69","71/15"},
	{"1/23","4/3","1/23","4/3","-89/69","89/69"},
	{"1/11","4/3","-7/3","0","1/11","11/3"},
	{"1/11","4/3","1/11","4/3","-41/33","41/33"},
	{"1/7","1/7","-7/2","-1/3","10/21","51/14"},
	{"1/7","1/7","1/7","1/7","0","0"},
	{"1/7","1/7","1/2","11/3","-74/21","-5/14"},
	{"1/3","1/3","-5/17","0","1/3","32/51"},
	{"1/3","1/3","1/3","1/3","0","0"},
	{"1/2","1/2","0","7/11","-3/22","1/2"},
	{"1/2","1/2","1/2","1/2","0","0"},
	{"1/2","4/3","0","7/3","-11/6","4/3"},
	{"1/2","4/3","1/2","4/3","-5/6","5/6"},
	{"1/2","4/3","7/3","17/5","-29/10","-1"},
	{"1/2","11/3","-1/7","-1/7","9/14","80/21"},
	{"1/2","11/3","-1/7","1/7","5/14","80/21"},
	{"1/2","11/3","0","0","1/2","11/3"},
	{"1/2","11/3","1/7","1/7","5/14","74/21"},
	{"1/2","11/3","1/2","11/3","-19/6","19/6"},
	{"2/3","2/3","-7/2","17/11","-29/33","25/6"},
	{"2/3","2/3","2/3","2/3","0","0"},
	{"7/3","17/5","-4/3","-1/2","17/6","71/15"},
	{"7/3","17/5","-1/2","0","7/3","39/10"},
	{"7/3","17/5","-1/2","5/17","104/51","39/10"},
	{"7/3","17/5","0","1/2","11/6","17/5"},
	{"7/3","17/5","1/2","4/3","1","29/10"},
	{"7/3","17/5","7/3","17/5","-16/15","16/15"},
	{NULL,NULL,NULL,NULL,NULL,NULL}}; /* test_table */

/* End of file tests/test_mpri_sub_table.c */
