.PHONY: all
all: mastermindplay mastermindsolver

FLAGS = -Wextra -Wall -Wvla -std=c++11 -g
COMPILER = g++
OBJECT = $(COMPILER) $(FLAGS) -c
EXECUTIVE = $(COMPILER) $(FLAGS)

Game.o: Game.cpp Game.h
	$(OBJECT) Game.cpp -o Game.o

mastermindplay: MasterMindPlay.o Game.o
	$(EXECUTIVE) MasterMindPlay.o -o mastermindplay Game.o

MasterMindPlay.o: MasterMindPlay.cpp erand.h Game.h asserts.h
	$(OBJECT) MasterMindPlay.cpp -o MasterMindPlay.o

mastermindsolver: mastermindsolver.o Game.o
	$(EXECUTIVE) MasterMindSolver.o Game.o

MasterMindSolver.o: MasterMindSolver.cpp Game.h erand.h
	$(OBJECT) MasterMindSolver.o

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf *.mn
	rm -rf *.out

# debugging helpers
.PHONY: debugg valgrind tar run style
RUN = mastermindplay.mn w 4
debugg: MasterMindPlay.o Game.o
	$(EXECUTIVE) Game.o MasterMindPlay.o -o mastermindplay.mn

valgrind: debugg
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes $(RUN)

run: debugg
	$(RUN)

tar: ex1.tar
	tar cvf ex1.tar makefile MasterMindPlay.c MasterMindSolver.c MasterMindgame.h
ex1.tar: clean

style:
	~labc/public/codingStyleCheck .
