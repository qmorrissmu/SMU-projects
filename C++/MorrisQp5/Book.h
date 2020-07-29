#ifndef BOOK_H
#define BOOK_H
#include <string>
using namespace std;


class Book
{	

private:

	int returnMonth;
	int returnDay;
	int returnYear;
	int length;
	int width;
	int area;
	int numberPages;
	bool rented;
	string authorFirst;
	string authorLast;
	string title;
	string renterFirst;
	string renterLast;

public:

	Book(int l, int w, int p, string aLast, string aFirst, string t);
	Book();
	void renterInfo(string rLast, string rFirst, int m, int d, int y);

	int getArea();
	int getLength();
	int getWidth();

	int getMonth();
	int getDay();
	int getYear();

	int getNumberPages();
	void returnBook();

	bool compare(Book& next);
	bool isRented();
	
	string getRLast();
	string getRFirst();

	string getAFirst();
	string getALast();
	
	string getTitle();

	string onLoan();


};

#endif