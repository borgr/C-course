/*
 ============================================================================
 Name        : Bishop.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : bishop header
 ============================================================================
 */
#ifndef _BISHOP
#define _BISHOP
#include <string>
#include "Position.h"
#include "Piece.h"

/**
 * class for bishop
 */
class Bishop : public Piece
{
public:
	Bishop(Position pos, bool isWhite);
	
	Bishop(const Bishop& src);

	virtual ~Bishop() = default;

	/**
	 * bishop threatens in diagonals
	 */
	bool threaten(const Position& to, const Chess& game) const override;

	using Piece::canCastle;

	using Piece::canMove;

	std::string unicode() const override;

	/**
	 * check surrounding diagonals
	 */
	bool hasLegal(Chess& game) override;
}; 

inline Bishop::Bishop(Position pos, bool isWhite): Piece(pos, isWhite)
{
}

#endif