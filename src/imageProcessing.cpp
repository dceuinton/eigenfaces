
#include "imageProcessing.h"

// MUST at least be a BGR image. 
// TRY to input a greyscale image.
void filterIntensity(Mat &src) {
	if (src.type() != CV_8UC1) {
		cvtColor(src, src, COLOR_BGR2GRAY);
	}
	equalizeHist(src, src);                 // This is a the OpenCV function that actually does the work.
}