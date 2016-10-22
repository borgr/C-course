/*
 ============================================================================
 Name        : Knight.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : knight header
 ============================================================================
 */
#ifndef _KNIGHT
#define _KNIGHT
#include <string>
#include "Position.h"
#include "Piece.h"

/**
 * a knight
 */
class Knight : public Piece
{
public:
	Knight(Position pos, bool isWhite);
	
	Knight(const Knight& src);

	virtual ~Knight() = default;
	/**
	 * a knight thratens a step orthogonally and a step diagonaly
	 */
	bool threaten(const Position& to, const Chess& game) const override;

	using Piece::canCastle;

	using Piece::canMove;

	std::string unicode() const override;

	/**
	 * check surrounding diagonals
	 */
	bool hasLegal(Chess& game) override;
private:
	/**
	 * checks the four directions for legality
	 *@param row to add or deduce
	 *@para col to add or deduve
	 *@param game
	 *@return true if one of the direction is legal
	 */
	bool _fourDirections(const int& row, const int& col, Chess& game) const;

	bool _legal(const Position& pos, Chess& Game) const;
};

inline Knight::Knight(Position pos, bool isWhite): Piece(pos, isWhite)
{
}
#endif