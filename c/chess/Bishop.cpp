/*
 ============================================================================
 Name        : Bishop.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : Bishop implementation
 ============================================================================
 */
#include <cassert>
#include "asserts.h"
#include "Position.h"
#include "Piece.h"
#include "Bishop.h"
#include "Chess.h"
#include "Diagonals.h"

#define UNICODE "\u265D"

string Bishop::unicode() const
{
	return UNICODE;
}

bool Bishop::hasLegal(Chess& game)
{
	return diagLegal(game, *this);
}

bool Bishop::threaten(const Position& to, const Chess& game) const
{
	return diagonalThreat(getPosition(), to, game);
}
