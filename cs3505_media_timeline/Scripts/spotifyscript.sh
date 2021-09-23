#!/bin/sh

docker run -d --mount type=bind,source="$(pwd)"/../MovieBuilder/shared_folder/collected_data,target=/spotify_data/output --rm spotify_data
