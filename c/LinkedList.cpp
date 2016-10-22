/*
 ============================================================================
 Name        : LinkedList.cpp
 Author      : borgr
 Version     :
 Copyright   :
 Description : a list for strings implementation 
 ============================================================================
 */

//delete includes
#include <iostream>
#include <string>
using namespace std;

#include "LinkedList.h"

/**
  * initilize all
  */
LinkedList::LinkedList(const string& str, LinkedList* next): _content(str), _next(next) 
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

//////////////////////////TODO delete
/**
 * main
 */
int main()
{
	LinkedList* l = new LinkedList(string("works"), new LinkedList(string("?")));
	cout << l->getContent() << l->getNext()->getContent() << endl;
	delete l->getNext();
	delete l;
}