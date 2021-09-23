# This class collects the top 2 new releases per day

1. running get_new_releases.py will put 2 images named MMDDYY_SongName_By:ArtistName.jpg into the OutputData folder
1.a MMDDYY will be the day in that format
2. Running the docker container will install the requirements.txt and run get_new_releases.py. 
3. To run this type the command Docker build --tag spotify_data . whle in this folder.
by Jack Machara
