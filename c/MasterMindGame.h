/*
 ============================================================================
 Name        : MasterMindGame.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : defines a master mind game
 ============================================================================
 */

#include <iostream>
#include <string>
using namespace std;

/**
 * a general class of a mastermind single game
 */
class Game
{
	public:
		/// number of pebbels to guess
		const unsigned int _length; 
		/// the last allowed character from lowercase a to ...
		const char _lastChar;

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
		 * no copy, there is not reason to allow it
		 */
		Game(const Game&) = delete;

		/**
		 * no =, no reason to allow it
		 */
		Game& operator = (const Game&) = delete;

		/**
		 * makes another turn returns true if game ended
		 */
		bool turn();

		/**
		 * ends the game
		 */
		void finish();

		/**
		 * getter
		 *
		 * @return number of turns already played, including current one.
		 */
		const unsigned int& getTurns() const;

	private:
		unsigned int _turns;

		/**
		 * takes a new guess
		 */
		string& guess();

		/**
		 * checks the guess given
		 * @return true iff the guess is the solution
		 */
		bool& check(string guess) const;

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
_length(length), _lastChar(lastChar), _turns(0)
{
	cout << "new game created " << _lastChar << _length << endl;
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
	void turnPassed();
	return check(guess);
}

 /**
  * default implementation
  */
inline const unsigned int& Game::getTurns() const
{
	return _turns;
}