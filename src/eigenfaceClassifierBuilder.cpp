
#include "eigenfaceClassifierBuilder.h"

// https://thecodinglove.com/when-i-accidentally-show-the-wrong-feature-during

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
        	Mat image = imread(path, 0);
        	filterIntensity(image);
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

void buildEigenfaceClassifier(string &dataFilename, string &saveFilename) {
	
	// Check that the saveFile ends with .xml
	string XMLTag = ".xml";
	if (!endsWith(saveFilename, XMLTag)) {
		printf("ERROR: Please use an .xml file to save the classifier.\n");
		return;
	}

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
	int numberOfEigenfacesToKeep = 80;
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

void testOnData(string classifierFilename, string testDataFilename) {
	string XMLTag = ".xml";
	if (!endsWith(classifierFilename, XMLTag)) {
		printf("ERROR: Correct classifier should end in '.xml'.\n");
		return;
	}

	Ptr<EigenFaceRecognizer> model = loadClassifier(classifierFilename);

	vector<Mat> images;
	vector<int> labels;

	try {
		read_csv(testDataFilename, images, labels);
	} catch (Exception &e) {
		cerr << "ERROR: Couldn't open file \"" << testDataFilename << "\". Reason: " << e.msg << endl;
		exit(1);
	}

	int correctCount = 0;
	int totalCount = 0;

	for (int i = 0; i < images.size(); i++) {
		int result = model->predict(images[i]);

		if (result == labels[i]) {
			correctCount++;
		}
		totalCount++;
	}

	printf("Tested a total of %d images.\n", totalCount);
	printf("Got a total of %d correct.\n", correctCount);

	float percentage = ((float)correctCount)/((float)totalCount) * 100.0f;

	printf("%f\n", percentage);
}

static Mat norm_0_255(InputArray _src) {
    Mat src = _src.getMat();
    // Create and return normalized image:
    Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

int getIndex(vector<int> &labels, int label) {
    vector<int>::iterator it;

    it = find(labels.begin(), labels.end(), label);

    int index = it - labels.begin();

    if (index == labels.size()) {
        index = -1;
    }

    return index;
}


void trainAndTest(string classifierFilename, string trainDataFilename, string testDataFilename, string outputFolder) {
	
	string output_folder = outputFolder;

    string CSVFile = trainDataFilename;
    string testCSVFile = testDataFilename;

    vector<Mat> images;
    vector<int> labels;

    try {
        read_csv(CSVFile, images, labels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << CSVFile << "\". Reason: " << e.msg << endl;
        exit(1);
    }

    if(images.size() <= 1) {
        string error_message = "Please add more images to your data set!";
        CV_Error(CV_StsError, error_message);
    }

    int height = images[0].rows;

    int numEigenFacesKeep = 80;
    float threshold = 100.0f;

    // Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
    Ptr<BasicFaceRecognizer> model = EigenFaceRecognizer::create(numEigenFacesKeep);
    // Ptr<FaceRecognizer> model = createEigenFaceRecognizer(numEigenFacesKeep, threshold);

    cout << "Training Now!!" << endl;
    model->train(images, labels);
    cout << "Training Done!!" << endl;

    Mat eigenfaces = model->getEigenVectors();
    Mat mean = model->getMean();    

    vector<Mat> testImages;
    vector<int> testLabels; 

    vector<bool> results;

    try {
        read_csv(testCSVFile, testImages, testLabels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << testCSVFile << "\". Reason: " << e.msg << endl;
        exit(1);
    }

    for (int i = 0; i < testImages.size(); i++) {
        int result = model->predict(testImages[i]);

        bool correct = false;

        if (result == testLabels[i]) {
            correct = true;
        }

        results.push_back(correct);

        string result_message = format("Predicted class = %d / Actual class = %d.", result, testLabels[i]);
        cout << result_message << endl;

        if (i < 10) {
        	imshow(format("Test %i Predicted Label %i", i+1, result), images[getIndex(labels, result)]);
	        imshow(format("Test %i Actual Label %i", i+1, testLabels[i]), testImages[i]);
        }        
    }

    int counter = 0;
    for (vector<bool>::iterator it = results.begin(); it != results.end(); it++) {
        if (*it == true) {
            counter++;
        }
    }

    for (int i = 0; i < min(10, eigenfaces.cols); i++) {
        // string msg = format("Eigenvalue #%d = %.5f", i, eigenvalues.at<double>(i));
        // cout << msg << endl;
        // get eigenvector #i
        Mat ev = eigenfaces.col(i).clone();
        // Reshape to original size & normalize to [0...255] for imshow.
        Mat grayscale = norm_0_255(ev.reshape(1, height));
        // Show the image & apply a Jet colormap for better sensing.
        Mat cgrayscale;
        applyColorMap(grayscale, cgrayscale, COLORMAP_JET);
        // Display or save:
        imwrite(format("%s/eigenface_%d.png", output_folder.c_str(), i), norm_0_255(cgrayscale));
        // imwrite(format("%s/eigenface_%d.png", output_folder.c_str(), i), norm_0_255(grayscale));
    }

    for(int num_components = min(eigenfaces.cols, 10); num_components < min(eigenfaces.cols, 300); num_components+=15) {
        // slice the eigenvectors from the model
        Mat evs = Mat(eigenfaces, Range::all(), Range(0, num_components));
        Mat projection = LDA::subspaceProject(evs, mean, images[0].reshape(1,1));
        Mat reconstruction = LDA::subspaceReconstruct(evs, mean, projection);
        // Normalize the result:
        reconstruction = norm_0_255(reconstruction.reshape(1, images[0].rows));
        imwrite(format("%s/eigenface_reconstruction_%d.png", output_folder.c_str(), num_components), reconstruction);
    }

    cout << "Predicted " << counter << "/" << results.size() << endl;
    cout << (float) counter/results.size() << "%" << endl;

    waitKey(0);
}