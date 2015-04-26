parinte(pandrei, ana).
parinte(pandreea, ana).
parinte(pcosmin, ionel).
parinte(pcosmina, ionel).
parinte(badrian, pandrei).
parinte(badrian, pcosmina).
parinte(badriana, pandrei).
parinte(badriana, pcosmina).

parinte(pcosmin, ionela).
parinte(pcosmina, ionela).
parinte(pandrei, emanuel).
parinte(pandreea, emanuel).


femeie(pcosmina).
femeie(pandreea).
femeie(badriana).
femeie(ana).
femeie(ionela).

barbat(pcosmin).
barbat(pandrei).
barbat(badrian).
barbat(ionel).
barbat(emanuel).

sot(pcosmin, pcosmina).
sot(pandrei, pandreea).
sotie(pcosmina, pcosmin).
sotie(pandreea, pandrei).
soti(X,Y) :- sot(X, Y).
soti(X,Y) :- sotie(X, Y).


mama(X,Y) :- parinte(X, Y), femeie(X).
tata(X,Y) :- parinte(X, Y), barbat(X).

frate(X,Y) :- parinte(Z, X), parinte(Z, Y), barbat(X).
sora(X, Y) :- parinte(Z, X), parinte(Z, Y), femeie(X).

bunic(X,Y) :- parinte(X, Z), parinte(Z, Y), barbat(X).
bunica(X,Y) :- parinte(X, Z), parinte(Z, Y), femeie(X).

unchi(X, Y) :- parinte(Z, X), parinte(Z, W),  parinte(W, Y), barbat(X).
unchi(X, Y) :- sot(X, W), parinte(Z, W), parinte(Z,U), parinte(U , Y).

matusa(X,Y) :- femeie(X), parinte(Z, X) , parinte(Z, W), parinte(W, Y).
matusa(X,Y) :- sotie(X, W), parinte(Z, W) , parinte(Z, U), parinte(U, Y).

nepot(X, Y) :- parinte(Z, X), parinte(Y, Z).


stramos(X, Y) :- parinte(X, Y).
stramos(X, Y) :- parinte(Z, Y), stramos(X, Z).

fib(0, 0).
fib(1, 1).
fib(1, 2).
fib(X, N):-
	N1 is N-1,
	fib(Z1, N1),
	N2 is N-2,
	fib(Z2, N2),
	X is Z1+Z2.

fba(N, N, FN1, FN2, F) :-
	F is FN1 + FN2.

fba(N, NI, FN1, FN2, F) :-
	NI < N,
	NI1 is NI + 1,
	NFN1 is FN1 + FN2,
	NFN2 is FN1,
	fba(N, NI1, NFN1, NFN2, F).


