/*
 ============================================================================
 Name        : Piece.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : a general chess piece
 ============================================================================
 */
#ifndef _PIECE
#define _PIECE
#include <string>
#include "Position.h"
#include "asserts.h"

class Chess;

/**
 * abstract class that represents a chess piece
 */
class Piece
{
public:
	/**
	 * constructor
	 */
	Piece(Position pos, bool isWhite);

	/**
	 * copy constructor
	 */
	Piece(const Piece& src);

	/**
	 * destructor
	 */
	virtual ~Piece() = default;
	
	/**
 	 * checks if the piece can walk to the position
 	 * 
 	 */
	virtual bool canMove(const Position& to, const Chess& game) const;

	/**
	 * checks ig the piece threatens the position
	 */
	virtual bool threaten(const Position& to, const Chess& game) const  = 0;

	/**
	 * moves the piece, assumes it can move to the position
	 */
	virtual void move(const Position& to);

	/**
 	 * checks if the piece can castle
 	 * 
 	 */
	virtual bool canCastle() const;

	/**
	 * sets positions
	 */
	void setPosition(const Position& to);

	/**
	 * gets positions
	 */
	const Position& getPosition() const;

	/**
	 * tells if the piece is white
	 */
	bool isWhite() const;

	/**
	 * a unique stamp of the piece object that can be printed
	 * every piece type has a unique unicode stamp
	 * @return the unicode of the Piece
	 */
	virtual std::string unicode() const = 0;

	/**
	 * checks if in this game there is any legal move available for the piece
	 *@return true if there is
	 */
	virtual bool hasLegal(Chess& game) = 0;

private:

	// position of the piece
	Position _pos;

	//is the piece white
	bool _isWhite;
};

/**
 * default implementation
 */
inline void Piece::move(const Position& to)
{
	_pos = to;
}

/**
 * default implementation
 */
inline bool Piece::canCastle() const
{
	return false;
}

/**
 * default implementation
 */
inline void Piece::setPosition(const Position& pos)
{
	_pos = pos;
}

/**
 * default implementation
 */
inline const Position& Piece::getPosition() const
{
	return _pos;
}

/**
 * default implementation
 */
inline Piece::Piece(const Piece& src):Piece(src.getPosition(), src.isWhite())
{
}

/**
 * default implementation
 */
inline Piece::Piece(Position pos, bool isWhite):_pos(pos), _isWhite(isWhite) 
{
}

/**
 * default implementation
 */
inline bool Piece::isWhite() const
{
	return _isWhite;
}


#endif