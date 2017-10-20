#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "MotionHandler.h"

using namespace cv;

class Autofocuser
{
public:
	Autofocuser(MotionHandler * gantry, VideoCapture * cap);
	~Autofocuser();

	void Focus();

	double ComputeFocus(Mat img);

protected :

	Mat EnsureGrayscale(Mat img);

	Mat Blur(Mat img);

	double Laplacian(Mat img);

	double varLaplacian(Mat img);

	MotionHandler * m_gantry;

	VideoCapture * m_cap;

	// For delivering messages.
	MessageHandler msg;

	// MOVE THESE VALUES TO A CONFIG FILE
	double m_dTable;
	double m_stepLarge;
};

