
#ifndef __EIGENFACE_CLASSIFIER_BUILDER__
#define __EIGENFACE_CLASSIFIER_BUILDER__

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgproc.hpp>
// #include <opencv2/contrib/contrib.hpp>
#include "imageProcessing.h"

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "util.h"

using namespace cv;
using namespace cv::face;
using namespace std;

void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';');
void buildEigenfaceClassifier(string &dataFilename, string &saveFilename);
Ptr<EigenFaceRecognizer> loadClassifier(const string &loadFilename);
void testOnData(string classifierFilename, string testDataFilename);
void trainAndTest(string classifierFilename, string trainDataFilename, string testDataFilename, string outputFolder);

#endif

/*
 * With the general method that Stan and I both use:
 * For 10 eigenfaces we get 19.2% 
 * For 80 eigenfaces we get 29.2% 
*/

/*
 * 59.6% when used with the frontal faces only
*/