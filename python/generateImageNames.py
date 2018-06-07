#!/usr/bin/env python

# Assumes there are no subdirectories

import sys
import os.path

if __name__ == "__main__":

    if len(sys.argv) != 2:
        print "usage: generateImageNames.py <base_path>"
        sys.exit(1);

    BASE_PATH=sys.argv[1];

    for dirname, dirnames, filenames in os.walk(BASE_PATH):
        for filename in filenames:
            path = os.path.join(dirname, filename);
            print path;