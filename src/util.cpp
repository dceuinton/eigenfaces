#include "util.h"

bool endsWith(string &fullString, string &ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	} else {
		return false;
	}
}

void readImagesFromFile(string &filename, vector<Mat> &images) {
	fstream file(filename.c_str());

	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
	}

	string line;
	while (getline(file, line)) {
		images.push_back(imread(line.c_str(), 0));
	}
}