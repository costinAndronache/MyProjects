size(4, 3).
map(1,1, '1,1').
map(1,2, '1,2').
map(1,3, '1,3').

map(2,1, '2,1').
map(2,2, '2,2').
map(2,3, '2,3').

map(3,1, '3,1').
map(3,2, '3,2').
map(3,3, '3,3').

map(4,1, '4,1').
map(4,2, '4,2').
map(4,3, '4,3').

enter(1,1, 'Te afli la 1,1').

:-dynamic explorer/2.

south:-
	explorer(X,Y),
	size(MX,_),
	X < MX,
	X1 is X + 1,
	retract(explorer(X,Y)),
	assert(explorer(X1, Y)),
	map(X1, Y, M),
	write(M).

north:-
	explorer(X,Y),
	X > 1,
	X1 is X - 1,
	retract(explorer(X,Y)),
	assert(explorer(X1, Y)),
	map(X1, Y, M),
	write(M).

east:-
	explorer(X,Y),
	size(_,MY),
	Y < MY,
	Y1 is Y + 1,
	retract(explorer(X,Y)),
	assert(explorer(X,Y1)),
	map(X, Y1, M),
	write(M).



west:-
	explorer(X,Y),
	Y > 1,
	Y1 is Y - 1,
	retract(explorer(X,Y)),
	assert(explorer(X, Y1)),
	map(X, Y1, M),
	write(M).

start :-
	retractall(explorer(_,_)),
	enter(X,Y, M),
	assert(explorer(X,Y)),
	write(M).


teleport :-
	retractall(explorer(_,_)),
	random_between(1, 4, X),
	random_between(1, 3, Y),
	assert(explorer(X,Y)),
	map(X,Y, M),
	write(M).
