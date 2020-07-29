#include <fstream>
#include <iostream>
#include "LinkedList.h"
#include "Library.h"
using namespace std;


Library::Library()
{
	bookShelf = LinkedList();
	loanList = LinkedList();
	booksAtLib = "bookshelf.txt";
	booksLoaned = "booksOnLoan.txt";

}

void Library::readFile()
{
	char status;
	ifstream infile;

	infile.open("booklist.txt");

	if(!infile.is_open())
	{
		cout << "error opening file" << endl;
	}

	while(infile.good())
	{
		infile >> status;
		if(status == 'A')
		{
			int length;
			int width;
			int pages;
			string authorLast;
			string authorFirst;
			string title;

			infile >> length;
			infile >> width;
			infile >> pages;
			infile >> authorLast;
			infile >> authorFirst;

			getline(infile, title);

			//send to book constructor
			Book b(length, width, pages, authorLast, authorFirst, title);
			bookShelf.insertInOrder(b);

		}
		else if(status == 'L')
		{
			string renterLast;
			string renterFirst;
			int month;
			int day;
			int year;
			string title;

			infile >> renterLast;
			infile >> renterFirst;
			infile >> month;
			infile >> day;
			infile >> year;

			getline(infile, title);
			if(!bookShelf.titleAvailable(title))
			{
				if(loanList.titleAvailable(title))
			   	{
					cout << title << "ALREADY LOANED OUT" << endl;

				}
				else if(loanList.titleAvailable(title))
				{
					cout << title << "NOT FOUND IN LIBRARY" << endl;

				}
			}
			else
			{
				//FIX ME
				Book c = bookShelf.lend(title);
				c.renterInfo(renterLast, renterFirst, month, day, year);
				loanList.insertInOrder(c);
			}

		}
		else if(status == 'R')
		{
			string title;
			getline(infile, title);
			if(!loanList.titleAvailable(title))
			{
				if(bookShelf.titleAvailable(title))
				{
					cout << "Book has been returned." << endl;
				}
				else
				{
					cout << "Error" << endl;
				}
			}
			else
			{
				//FIX ME
				Book c = loanList.lend(title);
			}

			//search for book and in loan list and put back on bookshelf
		}




	}


}

void Library::writeOutput()
{
	ofstream output;
	output.open(booksAtLib);
	output << bookShelf.ListSize();
	bookShelf.printBookshelf(output);

	ofstream otherOutput;
	otherOutput.open(booksLoaned);
	otherOutput << loanList.ListSize() << endl;
	loanList.printOnLoan(otherOutput);
}

