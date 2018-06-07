
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "eigenfaceClassifierBuilder.h"

using namespace cv;
using namespace std;

int main(int argc, char const *argv[]) {

	printf("Hello World!\n");

	Mat jocko = imread("../a3/jocko.jpg", 0);
	imshow("Jocko", jocko);
	waitKey(0);

	// buildEigenfaceClassifier();

	printf("Major.Minor %i.%i\n", CV_MAJOR_VERSION, CV_MINOR_VERSION);

	return 1;
}