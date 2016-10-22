/*
 ============================================================================
 Name        : Queen.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : queen implementation
 ============================================================================
 */
#include <cassert>
#include "asserts.h"
#include "Position.h"
#include "Piece.h"
#include "Queen.h"
#include "Chess.h"
#include "Diagonals.h"
#include "Range.h"

#define UNICODE "\u265B"

string Queen::unicode() const
{
	return UNICODE;
}

bool Queen::hasLegal(Chess& game)
{
	return diagLegal(game, *this) || orthLegal(game, *this);
}

bool Queen::threaten(const Position& to, const Chess& game) const
{
	return diagonalThreat(getPosition(), to, game) ||
		   orthogonalThreat(getPosition(), to, game);
}
