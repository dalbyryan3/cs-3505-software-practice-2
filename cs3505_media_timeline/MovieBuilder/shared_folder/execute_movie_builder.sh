#!/bin/bash

# This script executes movie builder and outputs files to an output directory
echo "Executing Movie Builder"
mkdir -p /shared_folder/output
rm -rf /shared_folder/output/*
rm -rf /shared_folder/pics/*
/shared_folder/bin/movie_builder /shared_folder/collected_data /shared_folder/output "$1"
if [ -e /shared_folder/pics/a_vid_out.avi  ]
	 then cp /shared_folder/pics/a_vid_out.avi /shared_folder/output
fi
echo "Finished Executing Movie Builder"
