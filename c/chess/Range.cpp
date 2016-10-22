/*
 ============================================================================
 Name        : Range.cpp
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
#include "Range.h"

bool orthogonalThreat(const Position& pos, const Position& to, const Chess& game)
{
	if (to.getRow() == pos.getRow() && to.getCol() != pos.getCol())
	{
		int i;
		int end;
		// check all the squares between vurrent and last (not including)
		for(i = range(to.getCol(), pos.getCol(), end) + 1; i < end; i++)
		{
			if(!game.emptySquare(Position(to.getRow(), i)))
			{
				return false;
			}
		}
		return true;
	}
	else if (to.getCol() == pos.getCol() && to.getRow() != pos.getRow())
	{
		int i;
		int end;
		for(i = range(to.getRow(), pos.getRow(), end) + 1; i < end; i++)
		{
			if(!game.emptySquare(Position(i, to.getCol())))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}