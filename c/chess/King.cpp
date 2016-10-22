/*
 ============================================================================
 Name        : Pawn.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : pawn implementation
 ============================================================================
 */
#include <cassert>
#include "Position.h"
#include "Piece.h"
#include "King.h"
#include "Chess.h"
#include "Range.h"
#include "Diagonals.h"

#define UNICODE "\u265A"

string King::unicode() const
{
	return UNICODE;
}

#define LONG 'B'
#define SHORT 'G'

bool King::castlePosition(const Position& to) const
{
	ASSERT_PRINT(char('A' - 1 + to.getCol()) << to.getRow());
	ASSERT_PRINT(char('A' - 1 + Position(getPosition().getRow(), LONG).getCol())
				 << Position(getPosition().getRow(), LONG).getRow());
	return to == Position(getPosition().getRow(), LONG) ||
		   to == Position(getPosition().getRow(), SHORT);
}

void King::move(const Position& to)
{
	_moved = true;
	this->Piece::move(to);
}

bool King::threaten(const Position& to, const Chess&) const
{
	return std::abs(getPosition().getRow() - to.getRow()) <= 1 &&
		   std::abs(getPosition().getCol() - to.getCol()) <= 1 &&
		   getPosition() != to;
}

/**
 * The king moves one step to his sides
 * plus bonuses...
 */
bool King::canMove(const Position& to, const Chess& game) const
{
	if(game.isThreatened(isWhite(), to))
	{
		ASSERT_PRINT("king can not go to a threatened square");
		return false;
	}
	// can not move more than one step and can not stay
	if (threaten(to, game))
	{
		ASSERT_PRINT("one step from the king");
		if(game.isEnemy(isWhite(), to) || game.emptySquare(to))
		{
			return true;
		}
		return false;
	}
	if (canCastle() && castlePosition(to))
	{
		ASSERT_PRINT("king castle position");
		// trying to castle, is the way clear and safe?
		int i;
		int end;
		// check in the range non inclusive
		for (i = range(getPosition().getCol(), to.getCol(), end) + 1; i < end; i++)
		{
			const Position current = Position(getPosition().getRow(), i);
			ASSERT_PRINT("checking now" << char('A' - 1 + current.getCol()) << current.getRow());
			if(game.isThreatened(isWhite(), current) ||
			   !game.emptySquare(current))
			{
				ASSERT_PRINT("square empy?" << game.emptySquare(current));
				ASSERT_PRINT("square threatened?" << game.isThreatened(isWhite(), current));
				ASSERT_PRINT(char('A' - 1 + current.getCol()) << current.getRow());
				return false;
			}
		}
		//check target
		return !game.isThreatened(isWhite(), to) && game.emptySquare(to);
	}
	ASSERT_PRINT("wierd move...");
	return false;
}

bool King::hasLegal(Chess& game)
{
	return diagLegal(game, *this) || orthLegal(game, *this);
}