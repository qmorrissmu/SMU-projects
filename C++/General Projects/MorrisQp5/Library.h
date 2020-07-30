#ifndef LIBRARY_H
#define LIBRARY_H
#include <fstream>
#include "LinkedList.h"
using namespace std;

class Library
{
	public: 
		Library();
		void readFile();
		void writeOutput();

	private:
		LinkedList bookShelf;
		LinkedList loanList;
		string booksAtLib;
		string booksLoaned;

};

#endif