
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "eigenfaceClassifierBuilder.h"
#include "util.h"
#include "imageProcessing.h"

using namespace cv;
using namespace std;

string trainingImagesFile = "trainingImageList.txt";
string testImagesFile = "testImageList.txt";

void trainClassifier(string saveFilename, string trainingDataFilename) {
	printf("Training Eigenface classifier with the data from %s\n", trainingDataFilename.c_str());

	buildEigenfaceClassifier(trainingDataFilename, saveFilename);

	printf("Saving Eigenface classifier as %s\n", saveFilename.c_str());
}

void testClassifier(string classifierFilename, string testDataFilename) {
	printf("Testing the %s classifier with data from %s\n", classifierFilename.c_str(), testDataFilename.c_str());

	testOnData(classifierFilename, testDataFilename);
}

void theFullMonty(string classifierFilename, string trainingDataFilename, string testDataFilename, string outputFilename) {
	trainAndTest(classifierFilename, trainingDataFilename, testDataFilename, outputFilename);
}

int main(int argc, char const *argv[]) {

	printf("OpenCV version: %i.%i\n", CV_MAJOR_VERSION, CV_MINOR_VERSION);

	if (argc == 4) {
		if (strcmp(argv[1], "test") == 0) {
			testClassifier(string(argv[2]), string(argv[3]));
		}
		if (strcmp(argv[1], "train") == 0) {
			trainClassifier(string(argv[2]), string(argv[3]));
		}
	} else if (argc == 6) {
		if (strcmp(argv[1], "full") == 0) {
			theFullMonty(string(argv[2]), string(argv[3]), string(argv[4]), string(argv[5]));
		}
	}else {
		printf("Usage: ./efaces <cmd: train/test> <classifiername.xml> <datafilename>\n");
	}

	return 1;
}