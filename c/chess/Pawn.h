/*
 ============================================================================
 Name        : Pawn.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : pawns, some say they are the most important pieces in the game
 ============================================================================
 */
#ifndef _PAWN
#define _PAWN
#include <string>
#include "Position.h"
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(Position pos, bool isWhite);
	
	Pawn(const Pawn& src);

	virtual ~Pawn() = default;

	/**
	 * a pawn can move a step forward or two in his first move
	 * or eat step forward and a step to the side
	 */
	bool canMove(const Position& to, const Chess& game) const override;

	/**
	 *pawn threatens astep forward and a step to the side
	 */
	bool threaten(const Position& to, const Chess& game) const override;

	using Piece::canCastle;

	std::string unicode() const override;
	
	/**
	 * check if can eat or move forward
	 */
	bool hasLegal(Chess& game) override;
};

/**
 * default implementation
 */
inline Pawn::Pawn(Position pos, bool isWhite): Piece(pos, isWhite)
{
}
#endif