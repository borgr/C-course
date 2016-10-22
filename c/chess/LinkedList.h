/*
 ============================================================================
 Name        : LinkedList.h
 Author      : borgr
 Version     :
 Copyright   :
 Description : a list for Pieces
 ============================================================================
 */

/**
 * you know... Piece slinked list
 */

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
	inline const Piece& getContent() const;

	/**
	 * content setter
	 */
	inline void setNext(LinkedList& next);

private:
	///the content
	Piece _content;
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
inline const Piece& LinkedList::getContent() const
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