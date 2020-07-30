#include <iostream>
#include "Book.h"
#include "LinkedList.h"
#include "Library.h"
using namespace std;

int main()
{

	Library libraryManager = Library();
	libraryManager.readFile();
	cout << endl;
	libraryManager.writeOutput();
	cout << endl;
	

	return 0;
}