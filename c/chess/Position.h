/*
 ============================================================================
 Name        : Position.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : a position on a rectangle board 
 ============================================================================
 */
#ifndef _POSITION
#define _POSITION
#define FIRST 'A'

/**
 * a class that represents a position on a board
 */
class Position
{
public:
	/**
	 * constructs a position on a rectangle board
	 * parameters in the computer sciences writing convention row col
	 *@param number of sqaure
	 *@param letter of square 
	 */
	explicit Position(int number = 0, char letter = 0);

	/**
	 * constructs a position on a rectangle board
	 * parameters in the computer sciences writing convention
	 *@param row 
	 *@param col 
	 */
	Position(int row, int col);

	/**
	 * constructs a position on a rectangle board
	 *@param row 
	 *@param col 
	 */
	Position(unsigned int row, unsigned int col);

	/**
	 * constructs a position on a rectangle board
	 *@param row 
	 *@param col 
	 */
	Position(const Position& pos);

	/**
	 * returns positions row
	 */
	int getRow() const;

	/**
	 * return positions col
	 */
	int getCol() const;

	/**
	 * returns true iff white position
	 **/
	 bool isWhite() const;

	 /**
	 * defines the right way of comparing
	 */
	 bool operator==(const Position& pos) const;

	 /**
	 * defines the right way of comparing
	 */
	 bool operator!=(const Position& pos) const;

private:
	int _row;
	int _col;
};

/**
 * default operator==
 */
inline bool Position::operator==(const Position& pos) const
{
	return getCol() == pos.getCol() && getRow() == pos.getRow();
}

inline bool Position::operator!=(const Position& pos) const
{
	return !(*this == pos);
}

/**
 * default implementation
 */
inline int Position::getRow() const
{
	return _row;
}

/**
 * default implementation
 */
inline int Position::getCol() const
{
	return _col;
}

/**
 * default implementation
 */
inline Position::Position(int number, char letter):_row(number), _col(letter - FIRST + 1) 
{
}

/**
 * default implementation
 */
inline Position::Position(int row, int col):_row(row), _col(col) 
{
}

/**
 * default implementation
 */
inline Position::Position(unsigned int row, unsigned int col):_row(row), _col(col) 
{
}

/**
 * default copy constructor
 */
inline Position::Position(const Position& pos):_row(pos.getRow()), _col(pos.getCol())
{
}
/**
 * default implementation
 */
inline bool Position::isWhite() const
{
	return (getCol() + getRow()) % 2;
}
#endif