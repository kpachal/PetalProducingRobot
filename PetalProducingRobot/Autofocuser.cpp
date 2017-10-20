#include "Autofocuser.h"



Autofocuser::Autofocuser(MotionHandler * gantry, VideoCapture * cap) :
	msg(INFO)
{
	m_gantry = gantry;
	m_cap = cap;

	// MOVE THESE VALUES TO A CONFIG FILE
	m_dTable = -120.0; // mm relative to home at which gantry table is in focus
	m_stepLarge = 2.0; //mm to move in large scale search for focus

	// Default values for focusing algorithms
	m_focusAlg = LAPV;
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

//	msg.Info("WTF DO WE HAVE", img.depth(), img.channels(), img.type());

	// Step 1: convert to greyscale
	img = EnsureGrayscale(img);

	// Step 2: blur image
	img = Blur(img);

	// Step 3: compute measure of focus.
	double focusMeasure;
	switch (m_focusAlg) {
		case LAPV:	focusMeasure = varLaplacian(img);
					break;
		case LAPM:	focusMeasure = modLaplacian(img);
					break;
	}

	std::cout << "Got focus measure " << focusMeasure << std::endl;

	return focusMeasure;

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
	GaussianBlur(img,img,Size(3,3),0,0,BORDER_DEFAULT);

	return img;
}

double Autofocuser::modLaplacian(Mat img) {

	int ddepth = img.depth();

	Mat M = (Mat_<double>(3, 1) << -1, 2, -1);
	Mat G = cv::getGaussianKernel(3, -1, ddepth);

	Mat Lx;
	sepFilter2D(img, Lx, ddepth, M, G);

	Mat Ly;
	sepFilter2D(img, Ly, ddepth, G, M);

	Mat FM = abs(Lx) + abs(Ly);

	double focusMeasure = mean(FM).val[0];
	return focusMeasure;
}

double Autofocuser::varLaplacian(Mat img) {

	Mat temp;
	Scalar  median, sigma;

	// Apply Laplacian operator
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = img.depth();
	cv::Laplacian(img, temp, ddepth, kernel_size);// , scale, delta, cv::BORDER_DEFAULT);
	cv::meanStdDev(temp, median, sigma); //mean,output_value);

	//return variance of the laplacian
	double focusMeasure = sigma.val[0]*sigma.val[0];
	return focusMeasure;
}
