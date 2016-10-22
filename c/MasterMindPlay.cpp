/*
 ============================================================================
 Name        : MasterMindPlay.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : a game of master mind, try to guess
 ============================================================================
 */
 // TODO implement finish
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cassert>

using namespace std;

#include "Game.h"
#include "erand.h"
#include "asserts.h"

#define FIRST 'a'

// turn outputs
#define GUESS_OUT "Please enter a guess of 4 letters between 'a' and '"
#define CHECK_OUT(bulls, cows) "You got " << bulls << " and " << cows << " cows."
#define FINISH(guesses) "It took you " << guesses << " guesses.\n"

// error outputs
#define WRONG_LENGTH_OUT "string of wrong length"
#define ILLEGAL_CHAR_OUT "illegal chars in string"

// parse macros
#define PROPER_INT "the legal length is a positive integer"
#define INTS_OUT "to many lengths were given"
#define CHARS_OUT "to many last chars were given"

// flag that indicates an error has occured and the program is shutting down. 
extern bool gError;

//note: exceptions might have been better, but off scope for now...

/**
 * default dtor
 */
Game::~Game() = default;

/**
 * finishes the game
 */
 void Game::finish()
 {
 	cout << FINISH(getTurns());
 }

/**
 * makes sure a char is legal
 * @return true iff legal
 */
bool legalChar(const char& c, const Game& game)
{
	return c >= FIRST && c<= game.getLast();
}

/**
 * check guess validity
 * @return true iff valid
 */
bool checkGuessValidity(const string& userGuess, const Game& game)
{
	if (userGuess.length() != game.getLength())
	{
		cout << WRONG_LENGTH_OUT << endl;
		return false;;
	}
	unsigned int i;
	for (i = 0; i < game.getLength(); i++)
	{
		if(!legalChar(userGuess[i], game))
		{
			cout << ILLEGAL_CHAR_OUT << endl;
			return false;
		}
	}
	return true;
}

/**
 * asks user for a guess
 */
string Game::guess()
{
	string userGuess;
	cout << GUESS_OUT << getLast() << "'" << endl;
	cin >> userGuess;
	gError = !checkGuessValidity(userGuess, *this);
	return userGuess;
}

/**
 *generates an answer for the game
 */
string generateAnswer(const Game& game)
{
	string result = "";
	unsigned int i;
	for (i = 0; i < game.getLength(); i++)
	{
		result += randomChar(game.getLast());
	}
	return result;
}

/**
 * checks the guess
 * @returns true iff the guess is correct
 */
bool Game::check(string guess) const
{
	if (gError)
	{
		return true;
	}
	static const string answer = generateAnswer(*this);
	ASSERT_PRINT("generated answer: " + answer);
	unsigned int cows;
	unsigned int bulls;
	compareGuesses(bulls, cows, guess, answer);
	cout << CHECK_OUT(bulls, cows) << endl;
	return bulls == _length;
}
