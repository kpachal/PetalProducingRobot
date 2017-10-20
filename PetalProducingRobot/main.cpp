#include "Gantry_Vancouver.h"
#include "MotionHandler.h"
#include "Autofocuser.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "opencv2/opencv.hpp"
using namespace cv;

int main()
{
	std::cout << "Beginning testing" << std::endl;

	Gantry_Vancouver myGantry;
	//MotionHandler myGantry;

	// Video
	VideoCapture cap;

	// Initialise
	myGantry.ActivateGantry();
	myGantry.ActivateAllAxes();
	myGantry.Home();

	// Send capture to autofocus
	Autofocuser focuser(&myGantry,&cap);

	//// Move somewhere on table
	myGantry.MoveTo(150.0, -150.0, -10.0);

	// Focus
	focuser.Focus();

	return 0;
}