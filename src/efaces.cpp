
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "eigenfaceClassifierBuilder.h"
#include "util.h"
#include "imageProcessing.h"

using namespace cv;
using namespace std;

string testImagesFileName = "testImagesList.txt";

int main(int argc, char const *argv[]) {

	printf("OpenCV version: %i.%i\n", CV_MAJOR_VERSION, CV_MINOR_VERSION);

	Mat jocko = imread("testImages/bw1.ppm", 0);
	Mat jockoFiltered = jocko.clone();
	filterIntensity(jockoFiltered);

	vector<Mat> images;

	readImagesFromFile(testImagesFileName, images);

	imshow("Jocko", jocko);
	imshow("Jocko Filtered", jockoFiltered);

	waitKey(0);

	return 1;
}