/*
 ============================================================================
 Name        : Pawn.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : pawn implementation
 ============================================================================
 */
#include <cassert>
#include "asserts.h"
#include "Position.h"
#include "Piece.h"
#include "Pawn.h"
#include "Chess.h"

#define UNICODE "\u265F"
#define UP 1
#define DOWN -1
#define WHITE_START 2
#define BLACK_START 7

string Pawn::unicode() const
{
	return UNICODE;
}

/**
 * returns the direction the pawn should walk in
 *@param isWhite
 *@return UP or DOWN accordingly
 */
inline int direction(bool isWhite)
{
	return isWhite ? UP : DOWN;
}

bool Pawn::threaten(const Position& to, const Chess&) const
{
	if (std::abs(to.getCol() - getPosition().getCol()) == 1)
	{
		assert(0 < to.getCol());
		assert(to.getCol() <= LINES);
		if(to.getRow() == getPosition().getRow() + direction(isWhite()))
		{
			return true;
		}
	}
	return false;
}

bool Pawn::hasLegal(Chess& game)
{
	const Position pos = getPosition();
	const Position stepForward = Position(pos.getRow() + direction(isWhite()), pos.getCol());
	const Position takeLeft = Position(pos.getRow() + direction(isWhite()), pos.getCol() + 1);
	const Position takeRight = Position(pos.getRow() + direction(isWhite()), pos.getCol() - 1);
	assert(game.onBoard(stepForward));
	return (canMove(stepForward, game) && game.safeMove(pos, stepForward)) ||
		   (game.onBoard(takeRight) &&
		   canMove(takeRight, game) &&
		   game.safeMove(pos, takeRight)) ||
		   (game.onBoard(takeLeft) &&
		   canMove(takeLeft, game) &&
		   game.safeMove(pos, takeLeft));
}

/**
 * a pawn moves forward one or eats to the sides
 * a pawn can move two steps on first turn
 */
bool Pawn::canMove(const Position& to, const Chess& game) const
{
	const int startRow = isWhite() ? WHITE_START : BLACK_START;

	//stay in the same col
	if(to.getCol() == getPosition().getCol())
	{
		//move one or two steps forward
		if(to.getRow() == getPosition().getRow() + direction(isWhite()) ||
		  (to.getRow() == getPosition().getRow() + 2 * direction(isWhite()) &&
		  getPosition().getRow() == startRow))
		{
			// may move if position is empty
			return game.emptySquare(to);
		}
	}

	// eat a col to the right or to the left
	else if (threaten(to, game) && game.isEnemy(isWhite(), to))
	{
		return true;
	}
	return false;
}