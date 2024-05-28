% Define predicates
happy(alice).
listens_to_music(alice).
listens_to_music(bob).
listens_to_music(carol).
listens_to_music(dave).
plays_guitar(bob).
plays_piano(carol).
plays_piano(dave).
talented(X) :-
plays_guitar(X) ; plays_piano(X).
genre(bob, rock).
genre(carol, classical).
genre(dave, jazz).
genre(alice, pop).
% Define rules
listens_to_good_music(X) :-
listens_to_music(X),
happy(X).
enjoys_genre(X, Genre) :-
listens_to_music(X),
genre(X, Genre).
enjoys_musician(X, Y) :-
listens_to_music(X),
talented(Y),
\+ X = Y. % X doesn't enjoy their own music


% listens_to_good_music(carol).
% listens_to_good_music(dave).
% listens_to_good_music(alice).
% enjoys_genre(dave,jazz).