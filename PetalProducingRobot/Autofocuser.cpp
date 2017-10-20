#include "Autofocuser.h"



Autofocuser::Autofocuser(MotionHandler * gantry, VideoCapture * cap) :
	msg(INFO)
{
	m_gantry = gantry;
	m_cap = cap;

	// MOVE THESE VALUES TO A CONFIG FILE
	m_dTable = -120.0; // mm relative to home at which gantry table is in focus
	m_stepLarge = 2.0; //mm to move in large scale search for focus
}


Autofocuser::~Autofocuser()
{
}

void Autofocuser::Focus() {

	// Move gantry to sensible start location.
	m_gantry->MoveZTo(m_dTable,10);

	// Depending on degree of focus found, move higher or lower by appropriate amount
	double focused = false;
	do {
		
		Mat frame;
		*m_cap >> frame;

		double focusDegree = ComputeFocus(frame);
		double someStandard = 1.0;

		if (focusDegree < someStandard) { // Everything is a grey blurry blob. Move around a lot

			m_gantry->MoveZBy(fabs(m_stepLarge));

		} else { // go to small focus & fitting routine

			// When satisfied that we know where the maximum is, go there and finish
			
			// FIXME
			double bestFit = m_dTable;
			m_gantry->MoveZTo(m_dTable);
			focused = true;
		}

	} while (!focused);

	return;

}

double Autofocuser::ComputeFocus(Mat img) {

	msg.Info("WTF DO WE HAVE", img.depth(), img.channels(), img.type());

	// Step 1: convert to greyscale
	img = EnsureGrayscale(img);

	// Step 2: blur image
	img = Blur(img);

	// Step 3: compute measure of focus.

	return 1.0;

}

Mat Autofocuser::EnsureGrayscale(Mat img) {

	Mat dest;
	Mat bgr[3];
	Mat img_grey;
	split(img, bgr);
	absdiff(bgr[0],bgr[1], dest);

	if (countNonZero(dest)) {
		msg.Info("This image is not grayscale! Converting.");
		cvtColor(img, img_grey, CV_BGR2GRAY);
	}
	else {
		msg.Info("This image is already grayscale!");
		img_grey = img;
	}

	return img_grey;
}

Mat Autofocuser::Blur(Mat img) {

	msg.Info("Applying Gaussian blur");
	GaussianBlur(img,img,Size(1,1),0,0,BORDER_DEFAULT);

	return img;
}

double Autofocuser::Laplacian(Mat img) {

	return 1.0;
}

double Autofocuser::varLaplacian(Mat img) {

	return 1.0;

}
