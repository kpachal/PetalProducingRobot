#include "Gantry_Vancouver.h"
#include "MotionHandler.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

int main()
{
	std::cout << "Beginning testing" << std::endl;
	Gantry_Vancouver myGantry;
	//MotionHandler myGantry;

	// Initialise
	myGantry.ActivateGantry();
	myGantry.ActivateAllAxes();

	myGantry.Home();

	//// Move somewhere on table
	myGantry.MoveTo(300.0, -250.0, -50.0);

	// Move incrementally backwards
	//myGantry.MoveBy(-10.0, -10.0, 10.0);

	// Free run in x, then stop, run back, stop
	myGantry.RunX();
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	myGantry.EndRunX();
	myGantry.RunXNeg();
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	myGantry.EndRunX();

	// Free run in y, then stop, run back, stop
	myGantry.RunY();
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	myGantry.EndRunY();
	myGantry.RunYNeg();
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	myGantry.EndRunY();

	// Free run down and back up
	myGantry.RunZ();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	myGantry.EndRunZ();
	myGantry.RunZNeg();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	myGantry.EndRunZ();

    // Spin around
	myGantry.RunU();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	myGantry.EndRunU();

	// Get location: where am I?
	std::vector<double> location = myGantry.WhereAmI();
	std::cout << "I am at location x=" << location.at(0) << ", y=" << location.at(1) << ", z=" << location.at(2) << ", u=" << location.at(3) << std::endl;
	return 0;
}