#include "Book.h"
#include <string>
#include <iostream>
using namespace std;


Book::Book()
{
	length = 0;
	width = 0;
	numberPages = 0;
	area = 0;
}


//constructor for a book object
//whether rented or not, it has all these properties(width, height, author, ect)
Book::Book(int l,int w,int p,string last,string first,string t)
{
	length = l;
	width = w;
	area = l * w;
	numberPages = p;
	authorLast = last;
	authorFirst = first;
	title = t;
	rented = false;

}


//extra info tied to a book that has been rented
void Book::renterInfo(string rLast, string rFirst,int m,int d,int y)
{
	returnYear = y;
	returnMonth = m;
	returnDay = d;
	renterLast = rLast;
	renterFirst = rFirst;
	rented = true;

}



/*
Book::Book(string last,string first,int m,int d,int y,string t)
{
	lastName = last;
	firstName = first;
	returnMonth = m;
	returnDay = d;
	returnYear = y;
	title = t;
}
*/



int Book::getLength()
{
	return length;
}

int Book::getWidth()
{
	return width;
}

/*
char Book::getStatus()
{
	return status;
}

*/

int Book::getArea()
{
	return area;
}

int Book::getMonth()
{
	return returnMonth;
}
int Book::getDay()
{
	return returnDay;
}
int Book::getYear()
{
	return returnYear;
}

string Book::getTitle()
{
	return title;
}

int Book::getNumberPages()
{
	return numberPages;
}

string Book::getRLast()
{
	return renterLast;
}

string Book::getRFirst()
{
	return renterFirst;
}

string Book::getAFirst()
{
	return authorFirst;
}

string Book::getALast()
{
	return authorLast;
}

void Book::returnBook()
{
	rented = false;
}

bool Book::isRented()
{
	return rented;
}

bool Book::compare(Book& nextBook)
{

	if(this -> isRented())
	{
		if(returnYear < nextBook.returnYear)
		{
			return true;
		}
		else if(returnMonth < nextBook.returnYear && returnYear == nextBook.returnYear)
		{
			return true;
		}
		else if(returnDay < nextBook.returnDay && returnMonth == nextBook.returnMonth && returnYear == nextBook.returnYear)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(this -> getArea() < nextBook.getArea())
		{
			return false;
		}
		else if(this -> getArea() == nextBook.getArea() && this -> getNumberPages() < nextBook.getNumberPages())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

}

string Book::onLoan()
{
	if(this -> isRented())
	{
		cout << title << " loaned to " << renterFirst << " " << renterLast << endl;
	}
	else 
	{
		cout << title << " by " << authorFirst << " " << authorLast << "(" << length << "x" << width << ", " << numberPages << " p)" << endl;
	}

	return title;
}












