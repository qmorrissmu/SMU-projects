#include "airplanes.h"
#include <iostream>
using namespace std;

Airplanes::Airplanes()
{
	int miles;
}

void Airplanes::setMiles(int aM)
{
	miles = aM;
}

int Airplanes::getMiles()
{
	return miles;
}

void Airplanes::getCarbonFootprint()
{
	int avgEm = 223;
	double wTP = 1.2;
	double ff = 1.9;
	float conversion = .0022;

	float footprintA = miles*avgEm*wTP*ff*conversion;

	cout << "The airplane's carbon footprint is " << footprintA << " lbs." << endl;



}