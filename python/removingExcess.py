#!/usr/bin/env python

import sys
import os.path
import bz2

if __name__ == "__main__":
    
    if len(sys.argv) != 2:
    	print "Usage: bunzipper <basepath>"
    	sys.exit(1)

    BASE_PATH=sys.argv[1];

    for dirname, dirnames, filenames in os.walk(BASE_PATH):
        for subdirname in dirnames:
            subject_path = os.path.join(dirname, subdirname)
            # print subject_path

            for filename in os.listdir(subject_path):
                # print filename
                filepath = os.path.join(subject_path, filename)
                # print filepath

                if (filepath.endswith("fa_a.ppm") or filepath.endswith("fa.ppm")):
                    print filepath
                else:
                    print "Removing: " + filepath
                    os.remove(filepath)