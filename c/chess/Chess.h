/*
 ============================================================================
 Name        : Chess.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : chess class definition
 ============================================================================
 */
 /*TODO list:
 valgrind
 */
#ifndef _CHESS_MAIN
#define _CHESS_MAIN
#include <iostream>
#include <unordered_map> 
#include "Position.h"
#include "HashMap.h"
#include "King.h"
#define LINES 8
class Piece;

using namespace std;


// macros for turn end
#define WHITE_RES 1
#define BLACK_RES 2
#define DRAW -3

/**
 * a class that represents chess
 */
class Chess
{
public:

	/**
	 * returns the player of the chosen color's name
	 *@param
	 */
	string getName(bool isWhite) const;
	
	/**
	 * ctor for game
	 **/
	Chess();
	/**
	 * play a game.
	 * playing a game twice will result in undefined behaviour
	 **/
	inline void play();
	/**
	 * dtor for game
	 **/
	~Chess();

	/**
	 * no copy, there is no reason to allow it
	 */
	Chess(const Chess&) = delete;

	/**
	 * no =, no reason to allow it
	 */
	Chess& operator=(const Chess&) = delete;

	/**
	 * helper function, checks if an enemy piece is in a square
	 *@param isWhite indicates the color of the player
	 *@param pos relevant position
	 *@return true iff there pos has an enemy piece
	 */
	bool isEnemy(const bool& isWhite, const Position& pos) const;

	/**
	 * checks if a square is empty
	 */
	bool emptySquare(const Position& pos) const;

	/**
	 * checks if an enemy piece threatens the sqaure
	 *@param isWhite indicates the color of the player
	 *@param pos relevant position
	 *@return true idd the aquare is threatened
	 */
	bool isThreatened(const bool& isWhite, const Position& pos) const;
	/**
	 * checks a row or col if they are on board
	 *@param place
	 *@return true if a legal square on board
	 */
	 inline bool onBoard(const int& place) const;
	/**
	 * checks the position represents pos on board
	 *@param Position
	 *@return true if a legal square on board
	 */
	inline bool onBoard(const Position& pos) const;

	/**
	 * makes sure moving the piece will not create a check
	 * in oher words the piece is not bound or tied to its square
	 * assumes piece can move from to
	 *@param from
	 *@param to
	 *@return true iff move will not be resolved to a check
	 **/
	bool safeMove(const Position& from, const Position& to);

private:
	/**
	 * updates the players name
	 */
	void _askForNames();
	
	/**
	 * makes a turn 
	 * if an error will occur the same player will be asked to play again and the board will not change
	 * @returns WHITE_RES if it is white's turn BLACK_RES if black's -WHITE_RES if WHITE_RES won
	 * -BLACK_RES if BLACK_RES won DRAW otherwise
	 * finishing macros are guarenteed to be negative and only them.
	 **/
	int _turn();

	/**
	 * returns the Piece in Position
	 */
	Piece* _getContent(const Position& pos) const;

	/**
	 * decides the next move
	 * returns bool if the next move is illegal
	 **/
	bool _nextMove(Position& from, Position& to);

	/// remembers who is next to play
	bool _whitePlays;

	/**
	 * finishes a turn 
	 * returns if next player is white
	 */
	bool _turnPlayed();

	/**
	 * @return true iff it is white's turn to play
	 */
	inline bool _whiteNext();

	/**
	 * adds the piece to ceratin position
	 * assumes position is empty
	 * @param piece
	 * @param pos
	 **/
	void _setContent(Position pos, Piece* piece);

	/**
	 * makes a pawn a queen if is on the last row
	 *@param pos
	 */
	void _createQueen(const Position& pos);

	/**
	 * tries to finish the game,
	 * @return true iff game finishedabs cpp
	 */
	bool _finish(int state) const;

	/**
	 * prints the board
	 */
	void _printBoard() const;

	/**
	 * checks if there is a check on the given player
	 *@param isWhite true if the player is white
	 */
	bool _check(bool isWhite) const;

	/**
	 * checks if a move ends without a check
	 *@param from
	 *@param to
	 *@return true iff move will not be resolved to a check
	 **/
	bool _endsCheck(const Position& king, const Position& to);

	/**
	 * updates king's position to a new place,
	 * if from is not a king does nothing
	 *@param king place in which a king might be 
	 *@param to a new position the king was moved to
	 */
	void _updateKing(const Position& king, const Position& to);

	/**
	 * moves the piece in a position to another position, assumes legal
	 */
	void _move(const Position& from, const Position& to);

	/**
	 * removes the piece in a position from the board
	 *@param pos
	 */
	void _remove(const Position& pos);

	/**
	 * prints warning for illegal move
	 */
	void _warn() const;

	/**
	 *@param isWhite 
	 *@return true iff the player has no legal move
	 */
	bool _noLegal(bool isWhite);

	/**
	 * returns the position of the king from that color
	 *@param isWhite
	 */
	inline const Position& _kingPos(bool isWhite) const;

	//a king should be dealt with separatly 
	///white king piece
	Position _whiteKing;

	///black king piece
	Position _blackKing;

	unordered_map<Position, Piece*>* _pieces;

	string _whitePlayer;

	string _blackPlayer;
};

/**
 * default implementation
 */
inline bool Chess::onBoard(const int& place) const
{
	return place > 0 && place <= LINES;
}

/**
 * default implementation
 */
inline bool Chess::onBoard(const Position& pos) const
{
	return onBoard(pos.getRow()) && onBoard(pos.getCol());
}

/**
 * default implementation
 */
inline bool Chess::_turnPlayed()
{
	return (_whitePlays = !_whitePlays);
}
/**
 * default implementation
 */
inline string Chess::getName(bool isWhite) const
{
		return isWhite ? _whitePlayer : _blackPlayer;
}

/**
 * default implementation
 */
inline const Position& Chess::_kingPos(bool isWhite) const
{
	return isWhite ? _whiteKing : _blackKing;
}

/**
 * default implementation
 */
inline void Chess::play()
{
	while (!_finish(_turn()));
}

/**
 * default implementation
 */
inline bool Chess::_whiteNext()
{
	return _whitePlays;
}
#endif