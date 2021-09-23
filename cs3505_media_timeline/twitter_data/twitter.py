import io
import tweepy
from PIL import Image, ImageDraw, ImageFont
from datetime import datetime

consumer_key= 'rd7DyFNOKd5PqPUbmXQ0j081P'
consumer_secret= 'p2NUCKlAMt1jXwZu2yre2b22Z6NKskJmzmvbr9IxyaV7RawoIG'
access_token= '1328130945250074624-BnqodBrJOaUik38T76pIBTliPTnSBX'
access_token_secret= '6jJHV5ZBEq85D3PzqtRKRBUTXzpDEZ4ynWDATZi2jpHSL'

auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_token_secret)
api = tweepy.API(auth, wait_on_rate_limit=True)

x = api.trends_place(2487610)
y = x.pop(0)
z = y['trends']
tweet = z.pop(0)
name = tweet['name']


img = Image.new('RGB', (150, 150), color = (0, 0, 0))
d = ImageDraw.Draw(img)



for x in range(1,4):
    
    tweet = z.pop(0)
    name = tweet['name']
    d.text((35, 30 + (20*x)), name, align='center', fill=(255,255,255))

now = datetime.now()

img.save("../output/" + now.strftime("%m%d%y_%H") + '_twitter' + '.bmp')


#f = open("testText.txt", "a")
#f.write(name)
#f.close()
