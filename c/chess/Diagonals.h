/*
 ============================================================================
 Name        : Diagonals.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : diag move helpers module
 ============================================================================
 */
#ifndef _DIAG
#define _DIAG
class Position;
class Piece;
class Chess;
/**
 * checks if to road from one position to the other is diag
 *@param from
 *@param to
 *@return true if it is diag
 */
bool isDiag(const Position& from, const Position& to);

/**
 * assumes rod is diag
 *@to square destination
 *@from will become the next position in diag to to
 *@return next
 */
Position next(const Position& from, const Position& to);

/**
 *@param game
 *@param piece
 *@return if the piece can walk in a diagonal way
 */
bool diagLegal(Chess& game, const Piece& piece);

/**
 * checks if piece in pos threatens position to
 *@param pos position of the piece
 *@param to position that might be threatened
 *@param game 
 *@return true iff to is threatened
 */
bool diagonalThreat(const Position& pos, const Position& to, const Chess& game);
#endif