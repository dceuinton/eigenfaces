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
    testFile = open("eTestImageList.txt", "w+");
    trainingFile = open("eTrainingImageList.txt", "w+");
    for dirname, dirnames, filenames in os.walk(BASE_PATH):
        for subdirname in dirnames:
            subject_path = os.path.join(dirname, subdirname)
            fileCount = 0;
            container = [];
            for filename in os.listdir(subject_path):
            	if "fa" in filename:
                    filename = os.path.join(subject_path, filename);
                    line = "%s%s%d" % (filename, SEPARATOR, label);
                    trainingFile.write("%s\n" % line);
                if "fb" in filename:
                    filename = os.path.join(subject_path, filename);
                    line = "%s%s%d" % (filename, SEPARATOR, label);
                    testFile.write("%s\n" % line);
            label += 1;