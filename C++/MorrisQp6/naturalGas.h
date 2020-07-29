#ifndef NATURALGAS_H
#define NATURALGAS_H
#include "polluter.h"
using namespace std;

class naturalGas: public Polluter
{
private:
	int avg;

public:
	naturalGas();
	void setAvg(int a);
	int getAvg();
	void getCarbonFootprint();

};

#endif