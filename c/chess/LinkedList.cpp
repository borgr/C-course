/*
 ============================================================================
 Name        : LinkedList.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : a list for Pieces implementation 
 ============================================================================
 */

#include "LinkedList.h"

/**
  * initilize all
  */
LinkedList::LinkedList(const Piece& str, LinkedList* next): _content(str), _next(next) 
{
}


LinkedList::~LinkedList() = default;

/**
 * nothing to add
 */
void deleteNext(LinkedList& list)
{
	LinkedList* deleted = list.getNext();
	if (deleted != nullptr)
	{
		list.setNext(*(deleted->getNext()));
		delete deleted;
	}
}