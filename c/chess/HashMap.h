/*
 ============================================================================
 Name        : HashMap.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : hash specialization for Position
 ============================================================================
 */
#ifndef _HASH_SPECIALIZE
#define _HASH_SPECIALIZE
/**
* speciliazing a hash function for our map's keys.
*/
namespace std
{
	/**
	* specializer of the std hash to work for Position
	*/
	template <>
	struct hash<Position>
	{
		/**
		* the hash function for pairs
		*/
		std::size_t operator()(const Position& k) const
		{
			using std::size_t;
			using std::hash;
			return (hash<int>()(k.getCol()) ^ (hash<int>()(k.getRow()) << 1));
		}
	};
}
#endif