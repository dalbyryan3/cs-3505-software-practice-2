# CS3505 Final Project- Team Rocket
# Media Timeline Using Docker and FFMPEG

## Building Data Collection Containers
Build each container by running the following commands while in the respective folders of the project. 
1. In StockData ->`docker build --tag stock_data .`
2. In twitter_data ->`docker build --tag twitter_data .`
3. In TwitchData -> `docker build --tag twitch_data .`
4. In NewsData -> `docker build --tag newsdata .`
5. In SpotifyData ->`docker build --tag spotify_data .`
6. In AQIData ->`docker build --tag aqi_data .`
7. To set up the cron job, execute `crontab -e`
  7a. This will bring up a text file, which is where the crontext.txt file from the scripts folder should be pasted. 
  7b. For running locally, Paths may need to be adjusted. 

## Movie Builder Usage
1. Collect data in MovieBuilder/shared_folder/collected_data using scheduled firing of data collecting containers as per each containers README.md.
2. `cd MovieBuilder`
3. `docker build --tag movie_builder .` *Only have to run this build command once*
4. `docker run -d --mount type=bind,source="$(pwd)/output",target="/shared_folder/output" --mount type=bind,source="$(pwd)/shared_folder/collected_data",target="/shared_folder/collected_data" movie_builder <MMDDYY>`
*This run command binds the collected_data folder to pass collected data into the docker container and binds the output folder to get the output of the movie_builder out of the docker container*
5. `cd output` *This will contain a movie if the program was successful and program output in movie_builder_output_information.txt*

