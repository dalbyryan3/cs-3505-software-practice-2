#!/bin/sh

docker run -d --mount type=bind,source="$(pwd)"/../MovieBuilder/shared_folder/collected_data,target=/stock_data/output --rm stock_data
