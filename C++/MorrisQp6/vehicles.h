#ifndef VEHICLES_H
#define VEHICLES_H
#include "polluter.h"
using namespace std;


class Vehicles: public Polluter
{
private:
	int numMiles;
	int eff;

public:
	Vehicles();
	
	void setNumMiles(int m);
	int getNumMiles();

	void setEff(int e);
	int getEff();

	void getCarbonFootprint();


};

#endif