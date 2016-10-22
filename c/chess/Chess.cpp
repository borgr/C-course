/*
 ============================================================================
 Name        : Chess.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : care for a game of chess?
 ============================================================================
 */
#include <iostream>
#include <unordered_map> 
#include <string>
#include <cassert>

using namespace std;

#include "asserts.h"
#include "Chess.h"
#include "Position.h"
#include "Piece.h"
#include "Pawn.h"
#include "Castle.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"

#define LETTERS "  ABCDEFGH"
#define UP 1
#define FIRST_DIGIT '0'

//gplayer names macros
#define WHITE_PLAYER "white"
#define BLACK_PLAYER "black"
#define ASK "Enter "
#define PLAYER_NAME " player name:"

//printing macros
#define CONTROL_START "\33["
#define CONTROL_END "m"
#define RESET "0"
#define COLOR_SEPARATE ";"
#define GREEN_REP "42"
#define AZUR_REP "46"
#define RED_REP "41"
#define WHITE_REP "37"
#define BLACK_REP "30"
#define MOVE ": Please enter your move:"
#define WARNING "37;41millegal move"
#define CHECK_WARNING "37;41mCheck!"
#define CLEAN "2j"

//end of game prints
#define DRAW_OUT "its a Draw!"
#define WON_OUT " won!"

//input macros
#define INPUT_LENGTH 4
#define FROM_COL 0
#define FROM_ROW 1
#define TO_COL 2
#define TO_ROW 3
#define FIRST 'A'

//starting positions
#define COL_KING 'E'
#define WHITE_MAIN 1
#define BLACK_MAIN LINES
#define LONG_CASTLE_POSITION 3
#define SHORT_CASTLE_POSITION 6
#define CASTLE_POS 1
#define BISHOP_LEFT_POS 3
#define BISHOP_RIGHT_POS 6
#define QUEEN_POS 4
#define KNIGHT_RIGHT_POS 7
#define KNIGHT_LEFT_POS 2

/**
 * prints necessary prints for draw and each player that wins
 */
bool Chess::_finish(int state) const
{
	if (state < 0)
	{
		_printBoard();
		switch(state)
		{
			case DRAW:
				cout << DRAW_OUT << endl;
				break;
			case -WHITE_RES:
				cout << _whitePlayer << WON_OUT << endl;
				break;
			case -BLACK_RES:
				cout << _blackPlayer << WON_OUT << endl;
				break;
		}
		return true;
	}
	return false;
}
/**
 *@isWhite is white winning?
 *@return the right result for this player to win
 */
inline int wins(bool isWhite)
{
	return isWhite ? -WHITE_RES : -BLACK_RES;
}
/**
 * finds piece color
 * @return unicode color representation
 */
string pieceColor(const Piece& piece)
{
	return piece.isWhite() ? WHITE_REP : BLACK_REP;
}

void Chess::_askForNames()
{
	cout << ASK << WHITE_PLAYER << PLAYER_NAME << endl;
	cin >> _whitePlayer;
	cout << ASK << BLACK_PLAYER << PLAYER_NAME << endl;
	cin >> _blackPlayer;
}

/**
 * ask for names and print the empty board
 */
Chess::Chess():_whitePlays(true), _whiteKing(Position(WHITE_MAIN, COL_KING)),
			   _blackKing(Position(BLACK_MAIN, COL_KING)), 
			   _pieces(new unordered_map<Position, Piece*>())
{
	//create kings
	King* white = new King(_whiteKing, true);
	_setContent(_whiteKing, white);
	King* black = new King(_blackKing, false); 
	_setContent(_blackKing, black);

	//create queens
	Position pos = Position(WHITE_MAIN, QUEEN_POS);
	Queen* queen = new Queen(pos, true);
	_setContent(pos, queen);
	pos = Position(BLACK_MAIN, QUEEN_POS);
	queen = new Queen(pos, false); 
	_setContent(pos, queen);

	//create knights
	pos = Position(WHITE_MAIN, KNIGHT_RIGHT_POS);
	Knight* knight = new Knight(pos, true);
	_setContent(pos, knight);
	pos = Position(BLACK_MAIN, KNIGHT_RIGHT_POS);
	knight = new Knight(pos, false); 
	_setContent(pos, knight);
	pos = Position(WHITE_MAIN, KNIGHT_LEFT_POS);
	knight = new Knight(pos, true);
	_setContent(pos, knight);
	pos = Position(BLACK_MAIN, KNIGHT_LEFT_POS);
	knight = new Knight(pos, false); 
	_setContent(pos, knight);

	//create castles
	pos = Position(WHITE_MAIN, CASTLE_POS);
	Castle* castle = new Castle(pos, true);
	_setContent(pos, castle);
	pos = Position(WHITE_MAIN, LINES);
	castle = new Castle(pos, true);
	_setContent(pos, castle);
	pos = Position(BLACK_MAIN, LINES);
	castle = new Castle(pos, false);
	_setContent(pos, castle);
	pos = Position(BLACK_MAIN, CASTLE_POS);
	castle = new Castle(pos, false);
	_setContent(pos, castle);

	//create bishops
	pos = Position(WHITE_MAIN, BISHOP_RIGHT_POS);
	Bishop* bishop = new Bishop(pos, true);
	_setContent(pos, bishop);
	pos = Position(WHITE_MAIN, BISHOP_LEFT_POS);
	bishop = new Bishop(pos, true);
	_setContent(pos, bishop);
	pos = Position(BLACK_MAIN, BISHOP_RIGHT_POS);
	bishop = new Bishop(pos, false);
	_setContent(pos, bishop);
	pos = Position(BLACK_MAIN, BISHOP_LEFT_POS);
	bishop = new Bishop(pos, false);
	_setContent(pos, bishop);


	//create pawns
	int i;
	for(i = 1; i <= LINES; i++)
	{
		//create a pawn on ther white row
		Position whitePosition = Position(WHITE_MAIN + UP, i);
		Pawn* whitePiece = new Pawn(whitePosition, true);
		_setContent(whitePosition, whitePiece);
		assert(!emptySquare(whitePosition));

		//create a pawn on the white row
		Position blackPosition = Position(BLACK_MAIN - UP, i);
		Pawn* blackPiece = new Pawn(blackPosition, false);
		_setContent(blackPosition, blackPiece);
	}
	_askForNames();
	ASSERT_PRINT("game initialized");
	_printBoard();
}

void Chess::_setContent(Position pos, Piece* piece)
{
	assert(emptySquare(pos));
	(*_pieces)[pos] = piece;
}

Chess::~Chess()
{
	unordered_map<Position, Piece*>::iterator it = _pieces->begin();
	while(it != _pieces->cend())
	{
		Piece* p = it->second;
		delete p;
		it++;
	}
	delete _pieces;
}

/**
 * checks in the array and returns content
 * assumes square is not empty otherwise undefined behaviour
 */
Piece* Chess::_getContent(const Position& pos) const
{
	return (*_pieces)[pos];
}

bool Chess::isThreatened(const bool& isWhite, const Position& pos) const
{
	unordered_map<Position, Piece*>::const_iterator it = _pieces->cbegin();
	while(it != _pieces->cend())
	{
		if (isEnemy(isWhite, it->first) && it->second->threaten(pos, *this))
		{
			//ASSERT_PRINT("threatened");
			return true;
		}
		it++;
	}
	//ASSERT_PRINT("unthreatened");
	return false;
}

/**
 * gets input from the player
 */
bool Chess::_nextMove(Position& from, Position& to)
{
	if(_check(_whiteNext()))
	{
		cout << CONTROL_START << CHECK_WARNING << CONTROL_START << RESET << CONTROL_END << endl;
	}
	//ask for a move
	cout << getName(_whiteNext()) << MOVE << endl;
	string move;
	cin >> move;
	ASSERT_PRINT("got move " << move);
	from = Position(move[FROM_ROW] - FIRST_DIGIT, move[FROM_COL]);
	to = Position(move[TO_ROW] - FIRST_DIGIT, move[TO_COL]);
	ASSERT_PRINT("got move " << move[FROM_ROW] << move[FROM_COL] << move[TO_ROW] << move[TO_COL]);
	return from != to && onBoard(from) && onBoard(to);
}

/**
 * checks if a piece is in the right color
 * @param white boolean, true if white
 * @param Piece
 * @return true iff Piece is in the right color
 */
bool rightColor(const Piece& piece, bool isWhite)
{
	return piece.isWhite() == isWhite;
}

/**
 * tells the color of a position on the board
 *@param pos a position on the board
 *@return a string that represents the color on unicode
 **/
string backgroundColor(const Position& pos)
{
	return (pos.getRow() + pos.getCol()) % 2 == 0 ? GREEN_REP : AZUR_REP;
}

inline void printPiece(const Piece& piece, const string& color)
{
	cout << CONTROL_START << pieceColor(piece) << COLOR_SEPARATE
		 << color << CONTROL_END << piece.unicode();
}

 /**
  * prints to the standard output
  */
void Chess::_printBoard() const
{
	ASSERT_PRINT("printing board");
	cout << LETTERS << endl;
	cout << endl;
	unsigned int row;
	for (row = LINES; row > 0; --row)
	{
		cout << row << " ";
		unsigned int col;
		for (col = 1; col <= LINES; ++col)
		{
			Position pos = Position(row, col);
			if (!emptySquare(pos))
			{
				printPiece(*_getContent(pos), backgroundColor(pos));
			}
			else
			{
				cout << CONTROL_START << RESET << COLOR_SEPARATE
				<< backgroundColor(pos) << CONTROL_END << " ";
			}
			cout << CONTROL_START << RESET << CONTROL_END;
		}
		cout << " " << row << endl;
	}
	cout << endl;
	cout << LETTERS << endl;
}

/**
 * prints the warning
 */
void Chess::_warn() const
{
	cout << CONTROL_START << WARNING << CONTROL_START << RESET << CONTROL_END << endl;

	_printBoard();
}

/**
 * returns the same number as the one represented this turn's player
 */
inline int samePlayer(bool isWhite)
{
	return  isWhite ? WHITE_RES : BLACK_RES;
}

bool Chess::_check(bool isWhite) const
{
	return isThreatened(isWhite, _kingPos(isWhite));
}

void Chess::_remove(const Position& pos)
{
	_pieces->erase(pos);
}

void Chess::_updateKing(const Position& from, const Position& to)
{
	if(from == _kingPos(true))
	{
		assert(_kingPos(true) != _kingPos(false));
		ASSERT_PRINT("changing white king place");
		ASSERT_PRINT("white king Position" << POS_PRINT(_kingPos(true)));
		_whiteKing = to;
	}
	else if(from == _kingPos(false))
	{
		ASSERT_PRINT("changing black king place");
		ASSERT_PRINT("black king Position" << POS_PRINT(_kingPos(false)));
		_blackKing = to;
	}
}

void Chess::_move(const Position& from, const Position& to)
{
	assert(from != to);
	ASSERT_PRINT("moving from " << POS_PRINT(from) << "to" << POS_PRINT(to) );
	_updateKing(from, to);

	if(!emptySquare(to))
	{
		Piece* p = _getContent(to);
		_remove(to);
		delete p;
	}
	ASSERT_PRINT("from " <<  char('A' - 1 + from.getCol()) << "row" << from.getRow() << ".");
	Piece* const temp = _getContent(from);
	temp->move(to);
	_setContent(temp->getPosition(), temp);
	_remove(from);
}

/**
 * returns the nearest side
 */
int side(const Position& pos)
{
	return pos.getCol() > 4 ? LINES : 1; 
}

/**
 * checks if this move is castle
 * assumes legal move and from points to a king
 *@param king a position of the king
 *@param to the position to which the king is directed
 *@return true iff king is asked to castle
 */
inline bool isCastle(const Position& king, const Position& to)
{
	ASSERT_PRINT("king col " << king.getCol());
	ASSERT_PRINT("to col " << to.getCol());
	return abs(king.getCol() - to.getCol()) > 1;
}

/**
 * finds the nearest position to the king from the castle to castle
 */
Position toKing(const Position& king, const Position& castle)
{
	assert(king.getRow() == castle.getRow());
	const int row = king.getRow();
	const int col = (king.getCol() - castle.getCol()) > 0
					? SHORT_CASTLE_POSITION : LONG_CASTLE_POSITION;
	ASSERT_PRINT("chosen col" << col);
	return Position(row, col);
}

/**
 * not changing the seen game state, but do change the object status,
 * this implementation is faster although a const member function
 * implementation is possible.
 * decided to use a non const method even though it is public
 * in order not to copy the inner list of pieces or other const options of implementation
 */
bool Chess::safeMove(const Position& from, const Position& to)
{
	//simulate conditions after given move and make a takeback
	ASSERT_PRINT("check safety from " << POS_PRINT(from) << " to " << POS_PRINT(to));
	Piece* temp = nullptr;
	// take to if it had a piece
	if(!emptySquare(to))
	{
		ASSERT_PRINT("not empty");
		temp = _getContent(to);
		_remove(to);
	}
	//simulate move pieces 
	//(_move will update pieces positions and might change inner states)
	//since .move is not a const function
	_setContent(to, _getContent(from));
	_remove(from);
	_updateKing(from, to);
	//check
	bool result = !_check(_getContent(to)->isWhite());
	//restore state
	_updateKing(to, from);
	ASSERT_PRINT("will this resolve in check?" << (!result));
	_setContent(from, _getContent(to));
	_remove(to);
	if (temp != nullptr)
	{
		_setContent(to, temp);
	}
	return result;
}

void Chess::_createQueen(const Position& pos)
{
	Pawn temp = Pawn(pos, _whiteNext());

	//if has a pawn stamp
	if(_getContent(pos)->unicode() == temp.unicode())
	{
		//and is on last row
		if(pos.getRow() == WHITE_MAIN || pos.getRow() == BLACK_MAIN)
		{
			Piece* p = _getContent(pos);
			_remove(pos);

			//make a queen out of it
			_setContent(pos, new Queen(pos, p->isWhite()));
			delete p;
		}
	}
}

/**
 * although not const function does not change the board state
 */
bool Chess::_noLegal(bool isWhite) 
{
	unordered_map<Position, Piece*>::const_iterator it = _pieces->cbegin();
	assert(it != _pieces->cend());
		
	const int size = _pieces->size();
	Position* positions = new Position[size];
	//necessary evil, iterating invalidates iterator
	int i;
	for(i = 0; i < size; i++)
	{
		positions[i] = it->first;
		it++;
	}
	for(i = 0; i < size; i++)
	{
		ASSERT_PRINT("another go " << POS_PRINT(positions[i]));
		if (_getContent(positions[i])->isWhite() == isWhite && 
			_getContent(positions[i])->hasLegal(*this))
		{
			ASSERT_PRINT("the piece in " << POS_PRINT(positions[i]) << " can move");
			delete [] positions;
			return false;
		}
	}
	delete[] positions;
	return true;
}

/**
 * default implementations
 */
int Chess::_turn()
{
	Position from;
	Position to;

	//find where to move
	if (!_nextMove(from, to))
	{
		ASSERT_PRINT("illegal input");
		_warn();
		return samePlayer(_whiteNext());
	}
	assert(from.getCol() > 0 && from.getCol() <= LINES);
	assert(to.getCol() > 0 && to.getCol() <= LINES);
	assert(from.getRow() > 0 && from.getRow() <= LINES);
	assert(to.getRow() > 0 && to.getRow() <= LINES);
	ASSERT_PRINT("move recieved");
	// check a piece to move was choshen
	if (emptySquare(from))
	{
		ASSERT_PRINT("there is no piece in this square");
		_warn();
		return samePlayer(_whiteNext());
	}
	const Piece& moving = *_getContent(from);
	ASSERT_PRINT("choshen piece" << moving.unicode() << "white?" << moving.isWhite());

	// check the legality of the move
	 /**
	  * BONUS::OPTION IMPLEMENTATION WAS NOT IN THE MANDATORY REQUIERMENTS
	  * this includes checking if eating a piece will end check
	  * and if blocking will end chess
	  * it also forbids a move of a bound/tied piece
	  */
	if(!rightColor(moving, _whiteNext()) ||
	   !moving.canMove(to, *this) ||
	   !safeMove(from, to))
	{
		ASSERT_PRINT("was this a safe move?" << safeMove(from, to));
		ASSERT_PRINT("can move?" << moving.canMove(to, *this));
		ASSERT_PRINT("unable to move. is it a white turn?" << _whiteNext());
		_warn();
		return samePlayer(_whiteNext());
	}

	ASSERT_PRINT("move accepted");
	ASSERT_PRINT("castle?" << isCastle(_kingPos(_whiteNext()), to));
	ASSERT_PRINT("king pos?" << ((_kingPos(_whiteNext())) == from));
	// check if trying to castle
	if((_kingPos(_whiteNext())) == from && isCastle(_kingPos(_whiteNext()), to))
	{
		ASSERT_PRINT("castling");
		Position corner = Position(to.getRow(), side(to));
		if(!emptySquare(corner) && _getContent(corner)->canCastle())
		{
			_move(corner, Position(toKing(corner, _kingPos(_whiteNext()))));
		}
		else
		{
			ASSERT_PRINT("castle is forbidden");
			_warn();
			return samePlayer(_whiteNext());
		}
	}
	ASSERT_PRINT("checks ended piece is moving");
	_move(from, to);
	_createQueen(to);

	//check if opponent can move
	if(_noLegal(!_whiteNext()))
	{
		if (_check(!_whiteNext()))
		{
			ASSERT_PRINT("someone won, white?" << _whiteNext());
			return wins(_whiteNext());
		}
		ASSERT_PRINT("DRAW");
		return DRAW;
	}
	ASSERT_PRINT("white?" << !_whiteNext() << " has legal move");
	//print the board after move was accepted
	_printBoard();
	return samePlayer(_turnPlayed());
}

/**
 * checks if an enemy is in the position
 *@param isWhite tells if player is white
 *@param pos where should an enemy be checked
 *@return true iff there is a piece of another color in the position
 **/
bool Chess::isEnemy(const bool& isWhite, const Position& pos) const
{
	if (emptySquare(pos))
	{
		return false;
	}
	const Piece& target = *_getContent(pos);
	return target.isWhite() != isWhite;
}

/**
 * default implementation
 */
bool Chess::emptySquare(const Position& pos) const
{
	return (*_pieces).find(pos) == (*_pieces).cend();
}

/**
 * main
 */
int main()
{
	ASSERT_PRINT("starting");
	Chess* game = new Chess();
	game->play();
	delete game;
}