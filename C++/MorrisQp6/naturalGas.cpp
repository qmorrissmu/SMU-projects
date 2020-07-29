#include "naturalGas.h"
#include <iostream>

naturalGas::naturalGas()
{
	int avg;

}

void naturalGas::setAvg(int a)
{
	avg = a;
}

int naturalGas::getAvg()
{
	return avg;
}

void naturalGas::getCarbonFootprint()
{
	double ppT = 14.14;
	double eFactor = 120.61;

	double footprintN = (avg/ppT)*eFactor*12;

	cout << "The natural gas carbon footprint is " << footprintN << " lbs." << endl;

}