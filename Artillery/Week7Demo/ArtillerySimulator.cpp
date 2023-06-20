#include "position.h"
#include "physics.h"
#include "simulator.h"

#include <iostream>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

int main()
{
	Simulator simulator1;
	simulator1.run(7.0);
	Simulator simulator2;
	simulator2.run(0.0);
	Simulator simulator3;
	simulator3.run(75.0);
	Simulator simulator4;
	simulator4.run(30.0);
	Simulator simulator5;
	simulator5.run(-45.0);

}