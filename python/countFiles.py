#!/usr/bin/env python

import sys
import os.path

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print "usage: create_csv <base_path>"
        sys.exit(1)

    BASE_PATH=sys.argv[1]
    SEPARATOR=";"
    
    foldersWithEnough = 0;
    label = 0;
    total = 0;
    stride = 4;
    container = [];
    testImages = [];
    trainingImages = [];
    testFile = open("testImageList.txt", "w+");
    trainingFile = open("trainingImageList.txt", "w+");
    for dirname, dirnames, filenames in os.walk(BASE_PATH):
        for subdirname in dirnames:
            subject_path = os.path.join(dirname, subdirname)
            fileCount = 0;
            container = [];
            for filename in os.listdir(subject_path):
            	fileCount += 1;
            	fullPathName = os.path.join(subject_path, filename);
            	container.append(fullPathName);

            if fileCount > 7:
            	foldersWithEnough += 1;
            	strideCounter = 0;
            	for filename in container:
            		line = "%s%s%d" % (filename, SEPARATOR, label);
            		# print line;
            		if strideCounter % stride == 0:
            			testImages.append(line);
            			testFile.write("%s\n" % line);
            		else:
            			trainingImages.append(line);
            			trainingFile.write("%s\n" % line);

            		strideCounter += 1;
            		total += 1;
            	label += 1;

    print "There are %d folders with more than 7 images in them" % foldersWithEnough
    print "There are %d images" % total
    # print "Test Images"
    # for image in testImages:
    	# print image;
    # print "Training Images"
    # for image in trainingImages:
    	# print image;