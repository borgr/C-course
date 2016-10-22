/*
 ============================================================================
 Name        : MasterMindGame.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : implements general mastermind game functions
 ============================================================================
 */
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

#include "Game.h"
#include "asserts.h"

//general macros
#define EOS '\0' //end of string

// correctArgNum macros
#define ARGS_NUM 3
#define ARGS_NUM_OUT " arguments expected or less."

// flag that indicates an error has occured and the program is shutting down. 
bool gError = false;

 /**
 * nothing to add
 */
 void Game::compareGuesses(unsigned int &bulls, unsigned int& cows,
 						   const string& guess, const string& answer) const
 {
 	cows = 0;
 	bulls = 0;
 	bool* answerUsed = new bool[_length];
	bool* guessUsed = new bool[_length];
	unsigned int i;
	for (i = 0; i < _length; i++)
	{
		answerUsed[i] = false;
		guessUsed[i] = false;
	}
 	for (i = 0; i < _length; i++)
 	{
 		if (guess[i] == answer[i])
 		{
 			bulls++;
 			answerUsed[i] = true;
 			guessUsed[i] = true;
 		}
 	}
 	for (i = 0; i < _length; i++)
 	{
 		if (guessUsed[i] == false)
 			{
 			unsigned int j;
 			for(j = 0; j < _length; j++)
 			{
 				if (answerUsed[j] == false && guess[i] == answer[j])
 				{
 					guessUsed[i] = true; // not used corrently but good practice 
 					answerUsed[j] = true;
 					cows++;
 				}
 			}
 		}
 	}
 	delete[] answerUsed;
 	delete[] guessUsed;
 }

/**
 * validates input
 * if there is a problem, prints an informative message
 * @return true iff args correct
 */
bool correctArgNum(unsigned int argc)
{
	if (argc > ARGS_NUM)
	{
		cout << ARGS_NUM << ARGS_NUM_OUT << endl;
		cout << USAGE << endl;
		return false;
	}
	return true;
}

 /**
  * checks if a string contains exactly one lowerCase letter
  * @param str a string to check
  * @return true iff matches
  */
 bool isChar(char* str)
 {
 	return str[0] != EOS && islower(str[0]) && str[1] == EOS;
  //note: order counts. Need to verify first that the string is not empty
 }

 /**
  * checks that a string is a legal int
  * @str string to match
  * @return true iff matches
  */
 bool isInt(string str)
 {
 	unsigned int i;
 	for (i = 0; i < str.length(); i++)
 	{
 		if (!isdigit(str[i]))
 		{
 			return false;
 		}
 	}
 	return true;
 }

/**
 * assigns the arguments to default game values if needed
 * @param &last
 * @param &length
 * @return the number of items assigned to default
 */
unsigned int assignDefaults(int &length, char &last)
{
	unsigned int assigned = 0;
	if (length == 0)
	{
		assigned++;
		length = DEF_LENGTH;
	}
	if (last == EOS)
	{
		assigned++;
		last = DEF_LAST;
	}
	return assigned;
}

  /**
  * creates a game with the given args
  * @return nullptr if an error occured
  */
Game* parseArgs(unsigned int argc, char *argv[])
{
	if (!correctArgNum(argc))
	{
		return nullptr;
	}
	int length = 0;
	char last = EOS;
	unsigned int i;
	for (i = 1; i < argc; i++)
	{
		// check argument to be int
		// Note: c++ atoi by itself will return undefined behaviour
		if(isInt(string(argv[i])))
		{
			if (length == 0)
			{
				length = atoi(argv[i]);
			}
		}
		// check argument to be char
		else if(isChar(argv[i]))
		{
			if (last == EOS)
			{
			  last = argv[i][0];
			}
		}
	}

	/* check assigned num is right
	 * if not, than it means there were wrong values or double values
	 */
	if (assignDefaults(length, last) != (ARGS_NUM - argc))
	{
		cout << USAGE << endl;
		return nullptr;
	}

	ASSERT_PRINT("starting game...");
	return new Game(length, last);
}

int main(int argc, char *argv[])
{
	assert(argc > 0);
	Game* game = parseArgs(argc, argv);
	if (game == nullptr)
	{
		ASSERT_PRINT("unable to start game");
		return EXIT_FAILURE;
	}
	game->play();
	delete game;
	if (gError)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}