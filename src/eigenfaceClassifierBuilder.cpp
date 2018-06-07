
#include "eigenfaceClassifierBuilder.h"

// Used from Philipp Wagner <bytefish[at]gmx[dot]de> under the BSD license
// Takes a file with image format as 
// <imagepath><separator><lable> i.e. jocko.jpg;0
// Reads the images in as greyscale and puts it in images vector, and puts label in label vector
void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator) {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
        	// Where we should do all the image processing
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

void buildEigenfaceClassifier(string &dataFilename, string &saveFilename) {
	
	// ************************************************************
	// Check that the saveFile ends with .xml
	// ************************************************************

	vector<Mat> images;
	vector<int> labels;

	// Read in the images
	try {
		read_csv(dataFilename, images, labels);
	} catch (Exception &e) {
		cerr << "ERROR: Couldn't open file \"" << dataFilename << "\". Reason: " << e.msg << endl;
		exit(1);
	}

	// Check to make sure that there are enough images
	if (images.size() <= 1) {
		string errorMessage = "Not enough images in data set. Check you have enough images or are using the right file";
		CV_Error(CV_StsError, errorMessage);
	}

	// ************************************************************
	// Important to get the height somewhere here for later reconstruction
	// ************************************************************

	// Set how many eigen faces to use and the threshold
	int numberOfEigenfacesToKeep = 10;
	float threshold = 0.0f;

	Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create(numberOfEigenfacesToKeep);
	
	// Train
	printf("Training classifier now (could take while depending on data set)...\n");
	model->train(images, labels);
	printf("Training complete!\n");

	// Save it 
	model->save(saveFilename);
}

Ptr<EigenFaceRecognizer> loadClassifier(const string &loadFilename) {
	Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();
	model->read(loadFilename);

	if (model->empty()) {
		printf("ERROR: Couldn't read from %s\n", loadFilename.c_str());
	} else {
		printf("The classifier %s has been loaded.\n", loadFilename.c_str());
	}
	return model;
}