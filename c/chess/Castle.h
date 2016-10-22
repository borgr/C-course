/*
 ============================================================================
 Name        : Castle.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : rook implementation 
 ============================================================================
 */
#ifndef _CASTLE
#define _CASTLE
#include <string>
#include "Piece.h"
#include "Range.h"
class Position;

/**
 * a rook
 */
class Castle : public Piece
{
public:
	Castle(Position pos, bool isWhite);
	
	Castle(const Castle& src);

	virtual ~Castle() = default;

	/**
	 * rook walk in all orthogonal directions
	 */
	bool threaten(const Position& to, const Chess& game) const override;

	using Piece::canMove;

	std::string unicode() const override;

	void move(const Position& to) override;

	/**
	 * a rook can castle if it did not move
	 */
	bool canCastle() const override;

	/**
	 * check in surrounding four directions
	 */
	bool hasLegal(Chess& game) override;
private:

	/// remembers if the king has moved
	bool _moved;
	
};

/**
 * default implementation
 */
inline bool Castle::hasLegal(Chess& game)
{
	return orthLegal(game, *this);
}

/**
 * default implementation
 */
inline Castle::Castle(Position pos, bool isWhite): Piece(pos, isWhite), _moved(false)
{
}

/**
 * default implementation
 */
inline bool Castle::canCastle() const
{
	return !_moved;
}

#endif