
#include "imageProcessing.h"

// Best to input a greyscale image
void filterIntensity(Mat &src) {
	if (src.type() != CV_8UC1) {
		cvtColor(src, src, COLOR_BGR2GRAY);
	}
	equalizeHist(src, src);
}