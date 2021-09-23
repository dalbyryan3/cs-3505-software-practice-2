import requests
import urllib.request
import datetime


def GatherData():

        ##URL Link
        URL= "https://api.twitch.tv/helix/games/top"

        ##Header parameters and secrets.
        PARA={'Authorization':"Bearer " + "2c4k40p9ifvus29iordfbod08afbgj", "Client-ID": "s3u0u6w0eb6n5xi2i9hvw1gjz41ri6"}

        r=requests.get(url=URL,headers=PARA)

        data=r.json()

        ##Retrieve the image url
        thumbnail_url=data['data'][5]['box_art_url']
        name=data['data'][5]['name']
        name=str.replace(name," ","")
        name=str.replace(name,":","")

        ##Set the image dimensions
        thumbnail_url=str.format(thumbnail_url,width=1280,height=720)

        ##Format timestamp for file name
        timestr=datetime.datetime.now().strftime("%m%d%y")

        ##Retrieve and save image to output folder
        urllib.request.urlretrieve(thumbnail_url,"./Output/"+timestr+"_"+name+".jpg")


if __name__ == "__main__":
    GatherData()
