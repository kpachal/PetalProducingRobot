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

	// Get location: where am I?
	std::vector<double> location = myGantry.WhereAmI();
	std::cout << "I am at location x=" << location.at(0) << ", y=" << location.at(1) << ", z=" << location.at(2) << ", u=" << location.at(3) << std::endl;
	return 0;
}

void displayVideo(VideoCapture cap) {
	
	for (;;) {
		Mat frame;
		cap >> frame;
		if (frame.empty()) break;
		imshow("here is a table!", frame);
		if (waitKey(10) == 27) break; // stop with ESC

	}

}