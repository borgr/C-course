/*
 ============================================================================
 Name        : Queen.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : queen
 ============================================================================
 */
#ifndef _QUEEN
#define _QUEEN
#include <string>
#include "Position.h"
#include "Piece.h"

/**
 * a queen
 */
class Queen : public Piece
{
public:
	Queen(Position pos, bool isWhite);
	
	Queen(const Queen& src);

	virtual ~Queen() = default;

	/**
	 * a queen threatens in all directions for as many steps as frre
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

/**
 * default implementation
 */
inline Queen::Queen(Position pos, bool isWhite): Piece(pos, isWhite)
{
}

#endif