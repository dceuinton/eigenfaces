
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

	vector<Mat> images;
	readImagesFromFile(testImagesFileName, images);

	printf("images has %i in it\n", (int)images.size());

	int count = 0;

	for (Mat im: images) {
		Mat clone = im.clone();
		filterIntensity(clone);
		printf("Image %i is [%i, %i]\n", ++count, im.rows, im.cols);
		imshow("Original", im);
		imshow("Filtered", clone);
		waitKey(0);
	}

	return 1;
}