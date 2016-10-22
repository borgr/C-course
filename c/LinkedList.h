/*
 ============================================================================
 Name        : LinkedList.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : a list for strings
 ============================================================================
 */

/**
 * you know... string linked list
 */
#include <iostream>
#include <string>
using namespace std;

class LinkedList
{
public:
	/**
	 * ctor
	 */
	LinkedList(const string& str, LinkedList* next = nullptr);

	/**
	 *dtor
	 */
	~LinkedList();

	/**
	 * next getter
	 */
	inline LinkedList* getNext() const;

	/**
	 * content getter
	 */
	inline const string& getContent() const;

	/**
	 * content setter
	 */
	inline void setNext(LinkedList& next);

private:
	///the string
	string _content;
	///next node
	LinkedList* _next;
};

/**
 * default
 */
inline LinkedList* LinkedList::getNext() const
{
	return _next;
}

/**
 * default
 */
inline const string& LinkedList::getContent() const
{
	return _content;
}

/**
 * default
 */
inline void LinkedList::setNext(LinkedList& next)
{
	_next = &next;
}

/**
 * deletes the next node
 * does nothing if this is last
 */
 void deleteNext(LinkedList& list);