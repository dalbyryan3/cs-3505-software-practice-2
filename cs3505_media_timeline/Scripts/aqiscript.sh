#!/bin/bash

docker run -d --mount type=bind,source="$(pwd)"/../MovieBuilder/shared_folder/collected_data,target="/aqi_data/output" --rm aqi_data 
