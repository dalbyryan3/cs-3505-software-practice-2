#Requests a list of top news articles, gets the image for each, writes the headline on the images, 
# and then saves each as a unique image with their timestamp as a file name

#libraries needed for image processing
import io
from PIL import Image, ImageDraw, ImageFont
#library for API regquests
import requests
#used  to make the article timestamp
import datetime

#get the headlines from the gnews top headlines endpoint
r = requests.get('https://gnews.io/api/v4/top-headlines?token=63f89f9930231abe03fcafe9b6e4c700&lang=en')


# iterate vover each headline until we get one with a good, usable image
for a in r.json()["articles"]:
    try:
        #use the image url from each article to retreive the image
        image_url = a["image"]
        
        #print(a["title"])

        url_response = requests.get(image_url)
        
        #get the image bytes to create an image object
        image_data = io.BytesIO(url_response.content)
    
        im = Image.open(image_data)
        
        #make all images the same size so the headline text is a readable size
        im = im.resize((500,500))

        draw = ImageDraw.Draw(im)
        
        #draw a background rectangle at the top of the image so the text is visible
        draw.rectangle((0, 0, 500, 40), fill=(230, 0, 0), outline=(255, 255, 255))

        font = ImageFont.truetype("ArialCEBold.ttf",size=18)

        #draw the headline text at the top of the image
        draw.text((10,10), a["title"], fill="rgb(255,255,255)", font=font)
        
        
        #draw a background rectangle at the bottom of the image so the text is visible
        draw.rectangle((0, 500, 500, 480), fill=(230, 0, 0), outline=(255, 255, 255))

        font = ImageFont.truetype("ArialCEBold.ttf",size=9)

        #draw the time published text at the top of the image
        draw.text((10,485), a["publishedAt"], fill="rgb(255,255,255)", font=font)
        
        #get timestamp, frist words, and sorce name to create a unique filename
        timestamp =  datetime.datetime.now().strftime("%m%d%y")
        
        first = a["title"].split()[0]
        
        second = a["title"].split()[1]
        
        source = a["source"]["name"]
        
        file_path = "/output/"+ timestamp + "_" + first + "_" + second + "_" +source
        
        file_path = file_path.replace(chr(32),'_')
        
        file_path = file_path.replace('\'','')
        
        file_path = file_path.replace('(','')
        
        file_path = file_path.replace(')','')
        
        file_path = file_path.replace('.','')
        
        
        #save the image with the time it was published at the file name
        im.save(file_path + ".png","PNG")
        
        #leave as soon as we get one article that works
        break
            
        
    #some articles come with bad image data, print message to console if an article image can't be processed
    except:
        print("Unable to process image data for article " + a["title"])
