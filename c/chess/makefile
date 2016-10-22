.PHONY: all
all: chess

FLAGS = -Wextra -Wall -Wvla -std=c++11
COMPILER = g++
OBJECT = $(COMPILER) $(FLAGS) -D NDEBUG -c 
EXECUTIVE = $(COMPILER) $(FLAGS)
PIECES_O = Pawn.o King.o Castle.o Piece.o Bishop.o Queen.o Knight.o
PIECES_OBJ = Pawn.obj King.obj Castle.obj Piece.obj Bishop.obj Queen.obj Knight.obj
HELPERS = asserts.h Position.h Chess.h
chess: chess.o HashMap.h $(PIECES_O) diagonals.o range.o
	$(EXECUTIVE) chess.o range.o diagonals.o $(PIECES_O) -o chess
chess.o: chess.cpp Position.h $(HELPERS)
	$(OBJECT) chess.cpp -o chess.o
range.o: Position.h Range.h Range.cpp
	$(OBJECT) Range.cpp -o range.o
diagonals.o: Position.h Diagonals.h Diagonals.cpp
	$(OBJECT) Diagonals.cpp -o diagonals.o
Piece.o: Piece.h Chess.h
	$(OBJECT) Piece.cpp -o Piece.o
Pawn.o: Piece.h Pawn.h Pawn.cpp $(HELPERS)
	$(OBJECT) Pawn.cpp -o Pawn.o
King.o: Piece.h King.h King.cpp $(HELPERS) Range.h Diagonals.h
	$(OBJECT) King.cpp -o King.o
Queen.o: Piece.h Queen.h Queen.cpp $(HELPERS) Range.h Diagonals.h
	$(OBJECT) Queen.cpp -o Queen.o
Castle.o: Piece.h Castle.h Castle.cpp $(HELPERS) Range.h
	$(OBJECT) Castle.cpp -o Castle.o
Bishop.o: Piece.h Bishop.h Bishop.cpp $(HELPERS) Diagonals.h
	$(OBJECT) Bishop.cpp -o Bishop.o
Knight.o: Piece.h Knight.h Knight.cpp $(HELPERS)
	$(OBJECT) Knight.cpp -o Knight.o
.PHONY: clean
clean:
	rm -rf *.o
	rm -rf *.obj
	rm -rf *.mn
	rm -rf *.out

# debugging helpers
.PHONY: debugg valgrind tar run style
RUN = chess.mn
DEBUGG = -g
debugg: chess.obj range.obj diagonals.obj $(PIECES_OBJ)
	$(EXECUTIVE) $(DEBUGG) chess.obj range.obj diagonals.obj $(PIECES_OBJ) -o chess.mn

chess.obj: chess.cpp Position.h $(HELPERS)
	$(OBJECT) $(DEBUGG) chess.cpp -o chess.obj
Piece.obj: Piece.cpp Piece.h $(HELPERS)
	$(OBJECT) $(DEBUGG) Piece.cpp -o Piece.obj
diagonals.obj: Diagonals.h Diagonals.cpp $(HELPERS)
	$(OBJECT) $(DEBUGG) Diagonals.cpp -o diagonals.obj
range.obj: Range.h Range.cpp $(HELPERS)
	$(OBJECT) $(DEBUGG) Range.cpp -o range.obj
Pawn.obj: Piece.h Pawn.h Pawn.cpp $(HELPERS)
	$(OBJECT) $(DEBUGG) Pawn.cpp -o Pawn.obj
King.obj: Piece.h King.h King.cpp $(HELPERS)
	$(OBJECT) $(DEBUGG) King.cpp -o King.obj
Queen.obj: Piece.h Queen.h Queen.cpp $(HELPERS) Range.h Diagonals.h
	$(OBJECT) $(DEBUGG) Queen.cpp -o Queen.obj
Castle.obj: Piece.h Castle.h Castle.cpp $(HELPERS) Range.h
	$(OBJECT) $(DEBUGG) Castle.cpp -o Castle.obj
Bishop.obj: Piece.h Bishop.h Bishop.cpp $(HELPERS) Diagonals.h
	$(OBJECT) $(DEBUGG) Bishop.cpp -o Bishop.obj
Knight.obj: Piece.h Knight.h Knight.cpp $(HELPERS)
	$(OBJECT) $(DEBUGG) Knight.cpp -o Knight.obj

valgrind: debugg
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes $(RUN)

run: debugg
	$(RUN)

tar: ex2.tar
	tar cvf ex2.tar Bishop.cpp Chess.h King.h Pawn.cpp Queen.cpp asserts.h Bishop.h Diagonals.cpp Knight.cpp Pawn.h Queen.h Castle.cpp Diagonals.h Knight.h Piece.cpp README makefile Castle.h HashMap.h LinkedList.cpp Piece.h Range.cpp chess.cpp King.cpp LinkedList.h Position.h Range.h

ex2.tar: clean

style:
	~labc/public/codingStyleCheck .
