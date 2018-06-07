#!/usr/bin/env python

# This is a script to bunzip all the .bz2 files in out feret_Facial_Image_DB01 
# Face database
# If you only want the images (don't want to keep the .bz2 file) uncomment the last line

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
    		for filename in os.listdir(subject_path):
    			filepath = os.path.join(subject_path, filename)
    			# print filepath
    			# print filename
    			# decompress(filename)
    			if (filepath.endswith(".bz2")):
    			    zipfile = bz2.BZ2File(filepath)
    			    data = zipfile.read()
    			    newfilepath = filepath[:-4]
    			    open(newfilepath, 'wb').write(data)
    			    os.remove(filepath)						# This line deletes the bz2 file