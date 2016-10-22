/*
 ============================================================================
 Name        : Knight.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : Knight implementation
 ============================================================================
 */
#include <cassert>
#include "asserts.h"
#include "Position.h"
#include "Piece.h"
#include "Knight.h"
#include "Chess.h"
#include "Diagonals.h"

using namespace std;

#define UNICODE "\u265E"
#define FAR_SIDE 2
#define CLOSE_SIDE 1

string Knight::unicode() const
{
	return UNICODE;
}

bool Knight::_legal(const Position& pos, Chess& game) const
{
	return game.onBoard(pos) &&
		   canMove(pos, game) &&
		   game.safeMove(getPosition(), pos);
}


bool Knight::_fourDirections(const int& row, const int& col, Chess& game) const
{
	return _legal(Position(getPosition().getRow() + row, getPosition().getCol() + col), game) ||
		   _legal(Position(getPosition().getRow() + row, getPosition().getCol() - col), game) ||
		   _legal(Position(getPosition().getRow() - row, getPosition().getCol() + col), game) ||
		   _legal(Position(getPosition().getRow() - row, getPosition().getCol() - col), game);

}

bool Knight::hasLegal(Chess& game)
{
	return _fourDirections(FAR_SIDE, CLOSE_SIDE, game) || 
		   _fourDirections(FAR_SIDE, CLOSE_SIDE, game);
}

/**
 * compares the two paires and checks if they have knight jumping differences
 *@param a1
 *@param a2
 *@param b1
 *@param b2
 *@return true if they represent a step forward and a step diagonal
 **/
static bool jump(const int& a1, const int& a2, const int& b1, const int& b2)
{
	return abs(a1 - b1) == FAR_SIDE && abs(a2 - b2) == CLOSE_SIDE;
}

bool Knight::threaten(const Position& to, const Chess&) const
{
	return jump(getPosition().getCol(), getPosition().getRow(), to.getCol(), to.getRow()) ||
		   jump(getPosition().getRow(), getPosition().getCol(), to.getRow(), to.getCol());
}
