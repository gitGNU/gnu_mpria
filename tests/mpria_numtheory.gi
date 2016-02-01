## tests/mpria_numtheory.gi -- GAP Input file
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

ContinuedFractionExpansionOfRational:=function(a,n)
	local A, r_0, r_1, r_2, i, A_i;
	if not IsRat(a) or not (IsPosInt(n) or IsZero(n)) then
		Error("usage: ContinuedFractionExpansionOfRational( <a>, <n>)\n",
					"for a rational <a> and a nonnegative integer <n>.\n");
	fi;
	A:=[]; i:=1;
	r_0:=NumeratorRat(a); r_1:=DenominatorRat(a);
	while true do
		A_i:=QuoInt(r_0,r_1); r_2:=RemInt(r_0,r_1);
		Add(A,A_i);
		if r_2 = 0 then break; fi;
		if (n <> 0) and (n <= i) then break; else i:=i+1; fi;
		r_0:=r_1; r_1:=r_2;
	od;
	return A;
end;

ContinuedFractionApproximationOfRational:=function(a,n)
	local A, M;
	if not IsRat(a) or not (IsPosInt(n) or IsZero(n)) then
		Error("usage: ContinuedFractionApproximationOfRational( <a>, <n>)\n",
					"for a rational <a> and a nonnegative integer <n>.\n");
	fi;
	A:=ContinuedFractionExpansionOfRational(a,n);
	M:=Product(A,A_i->[[A_i,1],[1,0]]);
	return M[1][1]/M[2][1];
end;


ContinuedFractionExpansionOfQuadraticIrrational:=function(a,b,d,n)
	local A, s, isqrt_D, P, D, Q, i, A_i, pool;
	Q:=false;
	if IsRat(a)
		and IsRat(b) and not IsZero(b)
		and IsPosRat(d)
		and (IsPosInt(n) or IsZero(n))
	then
		P:=DenominatorRat(d);
		b:=b/P;
		d:=NumeratorRat(d)*P;
		isqrt_D:=RootInt(d);
		Q:= isqrt_D^2 <> d ;
	fi;
	if not Q then
		Error("usage: ContinuedFractionExpansionOfQuadraticIrrational( <a>, <b>, <d>, <n>)\n",
					"for a quadratic irrational of the form <a> + <b> Sqrt( <d> ) ",
					"(where <a> is a rational, <b> a nonzero rational, and <d> a positive rational) ",
					"and a nonnegative integer <n>.\n");
	fi;
	P:=DenominatorRat(a); D:=DenominatorRat(b);
	a:=NumeratorRat(a)*D;
	b:=NumeratorRat(b); s:=SignInt(b); b:=b*P;
	Q:=D*P;
	D:=b*Q; D:=d*D^2;
	P:=s*Q*a; Q:=s*Q^2;
	isqrt_D:=RootInt(D);
	A:=[]; i:=1;
	if n = 0 then pool:=[[P,Q]]; else pool:=[]; fi;
	while true do
		A_i:=Int((P+isqrt_D)/Q);
		Add(A,A_i);
		P:=A_i*Q-P;
		Q:=(D-P^2)/Q;
		if (n = 0) then
			if [P,Q] in pool then break; else Add(pool,[P,Q]); fi;
		elif (n <= i) then break; else i:=i+1; fi;
	od;
	return A;
end;

ContinuedFractionApproximationOfQuadraticIrrational:=function(a,b,d,n)
	local A, isqrt_d, M;
	M:=false;
	if IsRat(a)
		and IsRat(b) and not IsZero(b)
		and IsPosRat(d)
		and (IsPosInt(n) or IsZero(n))
	then
		A:=DenominatorRat(d);
		b:=b/A;
		d:=NumeratorRat(d)*A;
		isqrt_d:=RootInt(d);
		M:= isqrt_d^2 <> d ;
	fi;
	if not M then
		Error("usage: ContinuedFractionApproximationOfQuadraticIrrational( <a>, <b>, <d>, <n>)\n",
					"for a quadratic irrational of the form <a> + <b> Sqrt( <d> ) ",
					"(where <a> is a rational, <b> a nonzero rational, and <d> a positive rational) ",
					"and a nonnegative integer <n>.\n");
	fi;
	A:=ContinuedFractionExpansionOfQuadraticIrrational(a,b,d,n);
	M:=Product(A,A_i->[[A_i,1],[1,0]]);
	return M[1][1]/M[2][1];
end;

##
## vim:syntax=gap
##
## End of file tests/mpria_numtheory.gi
