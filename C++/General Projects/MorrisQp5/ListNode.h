#ifndef LISTNODE_H
#define LISTNODE_H
#include "Book.h"
using namespace std;

class ListNode
{
	

private:
	
	Book b;
	ListNode* next;

public:
	
	ListNode(Book& x, ListNode* n)
	{
		b = x;
		n = nullptr;
		next = n;
	}

	void setNext(ListNode* n)
	{
		next = n;
	}

	ListNode* getNext()
	{
		return next;
	}

	void setBook(Book x)
	{
		b = x;
	}

	Book& getBook()
	{
		return b;
	}


};

#endif