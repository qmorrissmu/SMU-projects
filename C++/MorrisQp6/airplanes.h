#ifndef AIRPLANES_H
#define AIRPLANES_H
#include "polluter.h"
using namespace std;

class Airplanes: public Polluter
{
private:
	int miles;

public:
	Airplanes();
	void setMiles(int aM);
	int getMiles();
	void getCarbonFootprint();

};

#endif