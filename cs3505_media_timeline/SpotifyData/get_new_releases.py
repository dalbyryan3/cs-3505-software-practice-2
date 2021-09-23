

#imports
import spotipy
import secrets
from PIL import Image
import datetime
import requests
from io import BytesIO
from spotipy.oauth2 import SpotifyClientCredentials
from pathlib2 import Path
#gets the date and time, and makes a file with an empty txt file for the path 
current_date = datetime.datetime.now()


#get secrets for spotify api
cid = secrets.cid
secret = secrets.secret
#gets info from spotify with spotipy
client_credentials_manager = SpotifyClientCredentials(client_id=cid, client_secret=secret)
spotify = spotipy.Spotify(client_credentials_manager=client_credentials_manager)
results = spotify.new_releases('US',2)
releases = results['albums']
#Save the images in the output folder in the MMDDYY_SongName_By:ArtistName.jpg
count = 0
for release_item in releases['items']:
    file_name = current_date.strftime("%m%d%y")+'_'+release_item['name']+'_By_'+release_item['artists'][0]['name']
    file_name = file_name.replace(chr(32),'')
    file_name = file_name.replace('\'','')
    file_name = file_name.replace(chr(40), '')
    file_name = file_name.replace(chr(41),'')
    file_name = file_name.replace('.','')
    file_path = './output/' + file_name + '.jpg'
    output_filepath = Path(file_path)
    output_filepath.parent.mkdir(parents=True,exist_ok=True)
    #filer out invalid chars
    url = release_item['images'][0]['url']
    response = requests.get(url)
    img = Image.open(BytesIO(response.content))
    img.save(file_path)
    count=count+1
