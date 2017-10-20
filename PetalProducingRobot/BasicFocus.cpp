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
	if (!cap.open(0)) return 0;

	// Initialise
	myGantry.ActivateGantry();
	myGantry.ActivateAllAxes();
	//myGantry.Home();

	// Start in vageuly plausible spot
	myGantry.MoveZTo(-120.0);

	// Use this for display so I don't kill everything
	//namedWindow("currentFrame", WINDOW_NORMAL);
	//resizeWindow("currentFrame", 600, 600);
	
	// Send capture to autofocus
	Autofocuser focuser(&myGantry, &cap);

	for (int i = 0; i < 10; i++) {

		std::cout << "Beginning!" << std::endl;
		// Get image where we are now
		Mat frame;
		bool success = cap.read(frame);
		if (!(success)) continue;

		// Get degree of focus: is this reasonable? plausible?
		double focusVar = focuser.ComputeFocus(frame);
		std::cout << "Degree of focus: " << focusVar << std::endl;

		// Display frame
		//imshow("currentFrame", frame);

		// Move in incremental steps before checking again
		myGantry.MoveZBy(1.0);
		// Wait for camera to refocus
		std::this_thread::sleep_for(std::chrono::microseconds(3000));


	}

	return 0;
}