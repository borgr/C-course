/*
 ============================================================================
 Name        : Castle.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : rook implementation
 ============================================================================
 */
#include <cassert>
#include "Position.h"
#include "Piece.h"
#include "Castle.h"
#include "Chess.h"
#include "Range.h"
#include "Castle.h"

#define UNICODE "\u265C"

string Castle::unicode() const
{
	return UNICODE;
}

void Castle::move(const Position& to)
{
	_moved = true;
	this->Piece::move(to);
}

bool Castle::threaten(const Position& to, const Chess& game) const
{
	return orthogonalThreat(getPosition(), to, game);
}

