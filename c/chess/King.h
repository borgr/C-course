/*
 ============================================================================
 Name        : King.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : king the king in the game of kings
 ============================================================================
 */
#ifndef _KING
#define _KING
#include <string>
#include "Position.h"
#include "Piece.h"

/**
 * king class
 */
class King : public Piece
{
public:
	King(Position pos, bool isWhite);

	King(const King& src);

	virtual ~King() = default;
	/**
	 * a king can go to all directions
	 * one step
	 * and only if the sqaure is unthreatened
	 */
	bool canMove(const Position& to, const Chess& game) const override;

	bool canCastle() const override;

	std::string unicode() const override;
	/**
	 * a king can go to all directions
	 * one step
	 */
	bool threaten(const Position& to, const Chess& game) const override;
	
	/**
	 * checks if a position is one of the castle positions for this king
	 *@param to a place to which moving the king will be considered a castle
	 *@return true iff the position will be considered castle
	 */
	bool castlePosition(const Position& to) const;

	void move(const Position& to) override;

	/**
	 * cheack each surrounding square
	 */
	bool hasLegal(Chess& game) override;
private:

	/// remembers if the king has moved
	bool _moved;
	
};

/**
 * default implementation
 */
inline King::King(Position pos, bool isWhite): Piece(pos, isWhite), _moved(false)
{
}

/**
 * default implementation
 */
inline bool King::canCastle() const
{
	return !_moved;
}

#endif