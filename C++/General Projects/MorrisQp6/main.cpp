#include "polluter.h"
#include "vehicles.h"
#include "airplanes.h"
#include "naturalGas.h"
#include <vector>
#include <iostream>

int main()
{
	
	int userInput;

	//create pointers to each polluter object
	Vehicles* v = new Vehicles;
	Airplanes* a = new Airplanes;
	naturalGas* n = new naturalGas;

	vector <Polluter*> polluters;
	
	cout << "Vehicle Miles Driven: ";
	cin >> userInput;
	v -> setNumMiles(userInput);

	cout << "Vehicle Fuel Efficiency(MPG): ";
	cin >> userInput;
	 v -> setEff(userInput);

	cout << "Airplane Miles Flown: ";
	cin >> userInput;
	a -> setMiles(userInput);

	cout << "Average Gas Bill: ";
	cin >> userInput;
	n -> setAvg(userInput);
	cout << endl;

	//populate the vectors with the polluter objects, with their respective information
	polluters.push_back(v);
	polluters.push_back(a);
	polluters.push_back(n);

	//iterate through each vector and call their unique getCarbonFootprint functions
	for(int i = 0; i < polluters.size(); i++)
	{
		polluters[i] -> getCarbonFootprint();
	}


}