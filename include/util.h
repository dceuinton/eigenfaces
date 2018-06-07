
#ifndef UTILS_DALE_MINI_PROJECT
#define UTILS_DALE_MINI_PROJECT

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream> 
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;
using namespace cv;

bool endsWith(string &fullString, string &ending);

void readImagesFromFile(string &filename, vector<Mat> &images);

#endif