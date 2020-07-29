#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "ListNode.h"
#include "Book.h"
using namespace std;

class LinkedList
{

private: 

	ListNode* head;

public:

	LinkedList();
	void insertInOrder(Book);
	int ListSize();
	ListNode* getHead();
	Book lend(string, Book);
	void removeFromList(string);
	void pushFront(Book);
	void printBookshelf(ostream&);
	void printOnLoan(ostream&);
	bool titleAvailable(string);


};

#endif