/*
 ============================================================================
 Name        : Range.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : module to help orthogonal moving pieces
 ============================================================================
 */

#ifndef _RANGE
#define _RANGE
#include "Position.h"
#include "Chess.h"

/**
 * checks if piece in pos threatens position to
 *@param pos position of the piece
 *@param to position that might be threatened
 *@param game 
 *@return true iff to is threatened
 */
bool orthogonalThreat(const Position& pos, const Position& to, const Chess& game);

/**
 * finds the range between two ints
 *@oaram a a number
 *@param b another number
 *@param end a reference to which the end of the rang will be allocated
 *@return the beginning of the range
 */
inline int range(const int& a, const int& b, int& end)
{
	//probably returning a general iterator would have been nicer
	// but off scope for this ex
	if(a > b)
	{
		end = a;
		return b;
	}
	end = b;
	return a;
}

/**
 *@param game
 *@param piece
 *@param pos
 *@return true iff the piece can walk to that position
 */
static inline bool movable(Chess& game, const Piece& piece, const Position& pos)
{
	return game.onBoard(pos) &&
		   piece.canMove(pos, game) &&
		   game.safeMove(piece.getPosition(), pos);	
}

/**
 * checks if there is any legal move for the piece
 *@param piece
 *@param game
 */
inline bool orthLegal(Chess& game, const Piece& piece)
{
	const Position pos = piece.getPosition();
	const Position up = Position(pos.getRow() + 1, pos.getCol());
	const Position left = Position(pos.getRow(), pos.getCol() - 1);
	const Position right = Position(pos.getRow(), pos.getCol() + 1);
	const Position down = Position(pos.getRow() - 1, pos.getCol());
	return movable(game, piece, up) ||
		   movable(game, piece, left) ||
		   movable(game, piece, right) ||
		   movable(game, piece, down);
}

#endif