
#ifndef IMAGE_PROCESSING_DALE
#define IMAGE_PROCESSING_DALE

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_transforms.h>
#include <dlib/opencv.h>

#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

void filterIntensity(Mat &src);
void detectFaces(const char *filename);

#endif 