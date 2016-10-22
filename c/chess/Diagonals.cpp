/*
 ============================================================================
 Name        : Diagonals.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : a diagonal moving helpers implementation
 ============================================================================
 */
#include <stdlib.h>
#include "Chess.h"
#include "Position.h"
#include "Piece.h"
using namespace std;

bool isDiag(const Position& from, const Position& to)
{
	return abs(from.getRow() - to.getRow()) == 
		   abs(from.getCol() - to.getCol());
}

static int moveOne(const int& from, const int& to)
{
	return from + (from > to ? - 1 : 1);
}

Position next(const Position& from, const Position& to)
{
	return Position(moveOne(from.getRow(), to.getRow()),
		   moveOne(from.getCol(), to.getCol()));
}

bool diagonalThreat(const Position& from, const Position& to, const Chess& game)
{
	Position pos = from;
	if(isDiag(pos, to))
	{
		while (to != (pos = next(pos, to)))
		{
			if(!game.emptySquare(pos))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

/**
 *@param game
 *@param piece
 *@param pos
 *@return true iff the piece can walk to that position
 */
inline bool movable(Chess& game, const Piece& piece, const Position& pos)
{
	return game.onBoard(pos) &&
		   piece.canMove(pos, game) &&
		   game.safeMove(piece.getPosition(), pos);		
}

bool diagLegal(Chess& game, const Piece& piece)
{
	const Position pos = piece.getPosition();
	const Position rightUp = Position(pos.getRow() + 1, pos.getCol() + 1);
	const Position leftUp = Position(pos.getRow() - 1, pos.getCol() + 1);
	const Position rightDown = Position(pos.getRow() + 1, pos.getCol() - 1);
	const Position leftDown = Position(pos.getRow() - 1, pos.getCol() - 1);
	return movable(game, piece, rightUp) ||
		   movable(game, piece, leftUp) ||
		   movable(game, piece, rightDown) ||
		   movable(game, piece, leftDown);
}