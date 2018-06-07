#include "util.h"

bool endsWith(string &fullString, string &ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	} else {
		return false;
	}
}

// Reads a list of image names from a file into a vector as Mats and greyscale
void readImagesFromFile(string &filename, vector<Mat> &images) {
	fstream file(filename.c_str());

	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
	}

	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			images.push_back(imread(line, 0));	
		}		
	}
}