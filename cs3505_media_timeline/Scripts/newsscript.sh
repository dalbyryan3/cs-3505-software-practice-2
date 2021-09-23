#!/bin/sh

docker run -d --mount type=bind,source="$(pwd)"/../MovieBuilder/shared_folder/collected_data,target="/output" --rm newsdata python3 gnews.py
