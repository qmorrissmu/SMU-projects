#include "vehicles.h"
#include <iostream>
using namespace std;


//constructor
Vehicles::Vehicles()
{
	int numMiles;
	int eff;
}


void Vehicles::setNumMiles(int m)
{
	numMiles = m;
}

int Vehicles::getNumMiles()
{
	return numMiles;
}

void Vehicles::setEff(int e)
{
	eff = e;
}

int Vehicles::getEff()
{
	return eff;
}


void Vehicles::getCarbonFootprint()
{
	double lbsCO = 19.4;	
	double other = 100/95;

	double footprintV = (numMiles*52)/eff*lbsCO*other;

	cout << "Your vehicle's carbon footprint is " << footprintV << " lbs." << endl;
}