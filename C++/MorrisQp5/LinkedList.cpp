#include "LinkedList.h"
#include "Book.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList()
{
	head = nullptr;
}

void LinkedList::insertInOrder(Book b)
{
	if(head == nullptr)
	{
		this -> pushFront(b);
	}
	else if(!head -> getBook().compare(b))
	{
		this -> pushFront(b);
	}
	else
	{
		ListNode* curr = head;
		ListNode* prev = nullptr;
		while(curr != nullptr && curr -> getBook().compare(b))
		{
			prev = curr;
			curr = curr -> getNext();
		}

		ListNode* addToShelf = new ListNode(b);
		addToShelf -> setNext(curr);
		prev -> setNext(addToShelf);
	}

}

/*
void LinkedList::insertInOrderBookshelf(Book curr)
{

	//FIND THE SLOT TO INSERT THE NODE:
	//if the current data(first slot) is greater than data in new node
	//newNode gets inserted at the front
	ListNode* front = head;
	while(front -> next != nullptr)
	{
		if(curr.getArea() > front -> next -> getBook().getArea())
		{
			break;
		}
		else if(curr.getArea() == front -> next -> getBook().getArea())
		{
			if(curr.getNumberPages() > front -> next -> getBook().getNumberPages())
			{
				break;
			}

		}

		front = front -> next;
	}

	//INSERT THE NODE:
	ListNode* newNode = new ListNode(curr);
	ListNode* tempNode = front -> next;
	front -> next = newNode;
	newNode -> next = tempNode;
}

void LinkedList::insertInOrderOnLoan(Book curr)
{
	ListNode* front = head;
	while(front -> next != nullptr)
	{
		if(curr.getYear() < front -> next -> getBook().getYear())
		{
			break;
		}
		else if(curr.getYear() == front -> next -> getBook().getYear())
		{
			if(curr.getMonth() < front -> next -> getBook().getMonth())
			{
				break;
			}
			else if(curr.getMonth() == front -> next -> getBook().getMonth())
			{
				if(curr.getDay() < front -> next -> getBook().getDay())
				{
					break;
				}
			}
		}

		front = front -> next;
	}

	ListNode* newNode = new ListNode(curr);
	ListNode* tempNode = front -> next;
	front -> next = newNode;
	newNode -> next = tempNode;

	

}

*/
/*
void LinkedList::printOnLoan(ostream& output)
{
	int i = 1;
	ListNode* curr = head;
	while(curr != nullptr)
	{
		output << i << ". " << curr -> getBook().onLoan() << endl;
		curr = curr -> getNext();
		i++;
		cout << endl;
	}
}
*/

void LinkedList::removeFromList(string title)
{

	if(head -> getBook().getTitle() == title)
	{
		head = head -> getNext();
	}
	else
	{
		ListNode* curr = head;
		ListNode* prev = nullptr;
		while(curr != nullptr)
		{
			if(curr -> getBook().getTitle == title)
			{
				prev -> setNext(curr -> getNext());
				delete curr;
				break;
			}
			prev = curr;
			curr = curr -> getNext();
		}
	}
}

Book LinkedList::loanedBook(string title)
{
	ListNode* curr = head;
	ListNode* prev = nullptr;
	while(curr != nullptr)
	{
		prev = curr;
		curr = curr -> getNext();
	}

	return Book();

}

bool LinkedList::titleAvailable(string title)
{
	if(head == nullptr)
	{
		return false;
	}
	else if(head -> getBook().getTitle() == title)
	{
		return true;
	}
	else
	{
		ListNode* curr = head;
		ListNode* prev = nullptr;
		while(curr != nullptr)
		{
			if(curr -> getBook().getTitle() == title)
			{
				prev -> setNext(curr -> getNext());
				delete curr;
				break;
			}
			prev = curr;
			curr = curr -> getNext();

		}

		return false;
	}
}

int LinkedList::ListSize()
{
	int counter = 0;
	ListNode* curr = head;
	while(curr != nullptr)
	{
		++counter;
		curr = curr -> getNext();
	}

	return counter;
}

ListNode* LinkedList::getHead()
{
	return head;
}

void LinkedList::pushFront(Book b)
{
	ListNode* temp = new ListNode(b);
	temp -> setNext(head);
	head = temp;
}

/*
void LinkedList::addToList(LinkedList* curr)
{
	if(curr -> getStatus() == 'A' || curr -> getStatus() == 'R')
	{
		Bookshelf.insertInOrder(curr);
	}
	else
	{
		OnLoan.insertInOrder(curr);
	}
}

*/

Book LinkedList::lend(string title, Book curr)
{
	ListNode* front = head;
	ListNode* prev = nullptr;
	while(front -> getNext() != nullptr)
	{
		prev = curr;
		curr = curr.getNext();
	}

	return curr;


}

//make an fstream output
void LinkedList::printBookshelf(ostream& output)
{
	ListNode* curr = head;
	int i = 0;
	while(curr -> getNext() != nullptr)
	{
		output << i++ << ". " << curr -> getBook().getTitle() << " " << curr -> getBook().getAFirst()
			   << "( " << curr -> getBook().getLength() << "x" << curr -> getBook().getWidth()
			   << ", " << curr -> getBook().getNumberPages() << " p)" << endl;

			   curr = curr -> getNext();
	}
}

void LinkedList::printOnLoan(ostream& output)
{
	ListNode* curr = head;
	int i = 0;
	while(curr -> getNext() != nullptr)
	{
		output << curr -> getBook().getMonth() << "/" 
			   << curr -> getBook().getDay() << "/"
			   << curr -> getBook().getYear() << endl;

		output << curr -> getBook().getTitle() << " borrowed by " 
			   << curr -> getBook().getRFirst() << curr -> getBook().getRLast() << endl;	   
	}
}