
#include "imageProcessing.h"

// MUST at least be a BGR image. 
// TRY to input a greyscale image.
void filterIntensity(Mat &src) {
	if (src.type() != CV_8UC1) {
		cvtColor(src, src, COLOR_BGR2GRAY);
	}
	equalizeHist(src, src);                 // This is a the OpenCV function that actually does the work.
}

// Must input a Mat of type CV_UC1
void detectFaces(const char *filename) {

	try {

		dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
		dlib::image_window win;
		dlib::array2d<unsigned char> image;
		// dlib::assign_image(image, dlib::cv_image<unsigned char>(src));
		load_image(image, filename);

		dlib::pyramid_up(image);

		// std::vector<rectangle> dets = detector(image, 1);	
		std::vector<dlib::rectangle> dets = detector(image);
		cout << "Number of faces detected: " << dets.size() << endl;

		win.clear_overlay();
		win.set_image(image);
		win.add_overlay(dets, dlib::rgb_pixel(255,0,0));

	} catch (exception &e) {
		printf("Exception thrown\n%s\n", e.what());
	}

	
}