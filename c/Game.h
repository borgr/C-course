/*
 ============================================================================
 Name        : MasterMindGame.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : defines a master mind game
 ============================================================================
 */
#ifndef MYGAME
#define MYGAME
#include <iostream>
#include <string>

// the classic game values 
#define DEF_LENGTH 4
#define DEF_LAST 'd'
#define USAGE "USAGE: MasterMindPlay [length] [letter]"

/**
 * a general class of a mastermind single game
 */
class Game
{
	public:

		/**
		 * constructs a new game
		 * @see _length 
		 * @see _lastChar
		 */
		Game(unsigned int length, const char& lastChar);

		/**
		 * dtor
		 */
		~Game();

		/**
		 * no copy, there is no reason to allow it
		 */
		Game(const Game&) = delete;

		/**
		 * no =, no reason to allow it
		 */
		Game& operator = (const Game&) = delete;

		/**
		 * getter
		 *
		 * @return number of turns already played, including current one.
		 */
		const unsigned int& getTurns() const;

		/**
		 * getter
		 *
		 * @return lentgh
		 */
		const unsigned int& getLength() const;

		/**
		 * getter
		 *
		 * @return last char
		 */
		const char& getLast() const;

		/**
		 * plays a game
		 */
		inline void play();

	private:
		///number of turns
		unsigned int _turns;
		/// number of pebbels to guess
		const unsigned int _length; 
		/// the last allowed character from lowercase a to ...
		const char _lastChar;

		/**
		 * claculates the number of bulls and cows
		 */
		void compareGuesses(unsigned int &bulls, unsigned int& cows,
							const string& guess, const string& answer) const;

		/**
		 * makes another turn returns true if game ended
		 */
		bool turn();

		/**
		 * takes a new guess
		 */
		string guess();

		/**
		 * checks the guess given
		 * @return true iff the guess is the solution
		 */
		bool check(string guess) const;

		/**
		 * ends the game
		 */
		void finish();


		/**
		 * starts a new turn
		 */
		void turnPassed();

};

// allowes compiler to make inline if default implementations are used
 /**
  * default implementation
  */
inline Game::Game(unsigned int length, const char& lastChar):
_turns(0), _length(length), _lastChar(lastChar)
{
}

 /**
  * default implementation
  */
inline void Game::turnPassed()
{
	_turns++;
}
 
/**
 * no sepcial additions
 */
inline bool Game::turn()
{
	turnPassed();
	return check(guess());
}

 /**
  * default implementation
  */
inline const unsigned int& Game::getTurns() const
{
	return _turns;
}

 /**
  * default implementation
  */
inline const unsigned int& Game::getLength() const
{
	return _length;
}

 /**
  * default implementation
  */
inline const char& Game::getLast() const
{
	return _lastChar;
}

 /**
  * only one way to play a game, turn by turn
  */
inline void Game::play()
{
	while (!turn());
	finish();
}

 /**
  * checks that a string is a legal int
  * @str string to match
  * @return true iff matches
  */
 bool isInt(string str);

/**
 * creates a game from input
 */
Game* parseArgs(unsigned int argc, char *argv[]);
#endif