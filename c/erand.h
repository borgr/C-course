#ifndef ERAND_H
#define ERAND_H
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <stdlib.h>
#include <time.h>

int gen()
{
	srand( (unsigned int) time(NULL));
	return 1;
}

/**
 * @brief randomChar returns a random character, in the range 'a' to a givven character
 * @param C the maximal character to be returned
 * @return a random character
 */
inline char randomChar(char C = 'd')
{
	static int stamMashehu = gen();
	int mod = C-'a';
	char character;
	
	character = (rand() % mod) + 'a';
	return character;
}

#endif // ERAND_H
