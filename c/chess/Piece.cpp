/*
 ============================================================================
 Name        : Piece.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : a general chess piece implementation
 ============================================================================
 */
#include "Piece.h"
#include "Chess.h"

/**
 * default implementation : if there is no friend in the spot, you can move there
 */
inline bool Piece::canMove(const Position& to, const Chess& game) const
{
	return !game.isEnemy(!isWhite(), to) && threaten(to, game);
}