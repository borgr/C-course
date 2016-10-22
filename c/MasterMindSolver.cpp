/*
 ============================================================================
 Name        : MasterMindPlay.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : a game of master mind, how good will I be?
 ============================================================================
 */
#include <iostream>
#include <algorithm> 
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cassert>

using namespace std;

#include "Game.h"
#include "erand.h"
#include "asserts.h"
#include "LinkedList.h"

//general macros
#define EOS '\0' //end of string
#define FIRST 'a'
#define CHEAT "you are a cheater, I do not play with you!"
#define MY_GUESS_OUT "My guess is: "
#define FINISH(guesses) "I did it in " + guesses + " guesses!"

//guess macros
#define BULLS 0
#define COWS 1
#define BULLS_AND_COWS 2

// flag that indicates an error has occured and the program is shutting down. 
bool gError = false; 


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
 * gets the checking from the user
 * @param bulls int reference to put bulls in 
 * @param cows int reference to put cows ib
 * @return true iff legal input was given
 */
parseCheck(int& bulls, int& cows)
{
	string bullsStr;
	cin >> bullsStr;
	string cowsStr;
	getline(cin, cowStr);
	if(isInt(bullsStr) && isInt(cowsStr))
	{
		bulls = atoi(bullsStr);
		cows = atoi(cowsStr);
		return true;
	}
	ASSERT_PRINT("the ilegal input was" + bullsStr + cowsStr);
	return false;
}

/**
 * thinks hard and tries to guess
 * @return a guess, may change gError
 */
string Game::guess()
{
	//static LinkedList guesses = initializeGuesses(); //TODO implement returns * & or LINKED?
	// keeps the number of letters from each type that we know in certainty
	static int* lettersNum = new int[getLength()];
	static int sumLettersKnown = 0;
	// will keep string guessed
	static string* guessed = new string[getLast() - FIRST];
	// will keep checks from user [guessNum][cow or not] bull = 0 cow = 1
	static int* checks = new int[getLast() - FIRST][BULLS_AND_COWS];
	const unsigned int guessNum = getTurns() - 1;
	const unsigned int lastGuess = guessNum - 1;
	if(guessNum == 0)
	{
		return guessed[guessNum] = string(FIRST, getLength);
	}
	else if(guessNum < getLast() - FIRST)
	{
		//gets the inputs and makes sure it is valid
		if(!parseCheck(checks[lastGuess][BULLS],
		   checks[lastGuess][COWS]) ||
		   (checks[lastGuess][BULLS] +
		   checks[lastGuess][COWS] > getLength()))
		{
			cout << INPUT_OUT << endl;
			gError = true;
			//TODO delete everything!!!!!!!!!!!!
			return "";
		}
		//conclude number of letters of the last guess
		lettersNum[lastGuess] = checks[lastGuess][BULLS] +
								checks[lastGuess][COWS] - sumLettersKnown;
		//check if all letters known
		sumLettersKnown += lettersNum[lastGuess];
		if (sumLettersKnown < getLength())
		{
			guessed[guessNum] = guessed[lastGuess];
			// change redundent letters from last guess to the next letter
			int changed = getLength() - sumLettersKnown;
			int i = 0;
			const char nextLetter = FIRST + guessNum;
			const char lastLetter = FIRST + lastGuess;
			assert(nextLetter.islower());
			while(changed > 0)
			{
				if(guessed[guessNum][i] == (lastLetter))
				{
					guessed[guessNum][i] = nextLetter;
					changed--;
				}
				assert(i < getLength());
			}
			// find a permutation that is consistent with recent guesses
			//TODO super check that!!!
			sort(guessed[guessNum].begin(), guessed[guessNum].end());
			while(!consistent(guessed[guessNum]))
			{
				if (!next_permutation(guessed[guessNum].begin(), guessed[guessNum].end())
				{
					cout << CHEAT<< endl;
					gError = true;
					return "";
				}
			}
			return guessed[guessNum];
		}
		else
		{
			//TODO start bruting
		}
		return guessed[guessNum];
	}
	
//delete statics
}

/**
 *generates an answer for the game
 */
string generateGuess(const Game& game, LinkedList* guesses)
{
	if(guesses == nullptr)
	{
		cout << CHEAT; 
		gError = true;
		return "";
	}
	/*
	 note: for best guess in brute force it is requiered to make three loops over all the guesses
	 and count
	 if this guess 
	 would eliminate the other guess
	 if the third guess is the correct answer
	 choose the guess that eliminates the most guesses given the worst answer
	 it will take n^3 on the guesses (which does not change o since it is exponential any way...)
	 but, for 4 on 4 it will finish in 6 at most and mean of 4.__ 
	 so, only first time will be long...
	 and there arn't many times.
	 */
	return guesses->getContent();
}

/**
 * checks the guess
 * @returns true iff the guess is correct
 */
bool Game::check(string guess) const
{
	if (gError || guess == "")
	{
		return true;
	}
	cout << MY_GUESS_OUT << guess << endl;
	/* The input will be asked from the guesser as it is only needed
	   there for assesing next guess.
	*/
	return false;
}
