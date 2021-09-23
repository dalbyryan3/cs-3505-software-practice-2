#plot stuff
import matplotlib.pyplot as plt; plt.rcdefaults()
import numpy as np
import os.path

#file stuff
from datetime import date, timedelta, datetime
from pathlib import Path

#aqi stuff
import asyncio
from pyairvisual import CloudAPI

#main method
async def main() -> None:
    #gets the key from a txt file
    keyStream = open("AQI_APIKey.txt", "r")
    key = keyStream.read()    
    cloud_api = CloudAPI(key)

    #get strings from data
    dataSaltLake = await cloud_api.air_quality.city(city = "Salt Lake City", state = "Utah", country = "USA")
    dataOgden = await cloud_api.air_quality.city(city = "Ogden", state = "Utah", country = "USA")
    dataProvo = await cloud_api.air_quality.city(city = "Provo", state = "Utah", country = "USA")
    dataLogan = await cloud_api.air_quality.city(city = "Logan", state = "Utah", country = "USA")
    
    #get arrays from data
    dataSplitSLC = cleanUpString(str(dataSaltLake))
    dataSplitO = cleanUpString(str(dataOgden))
    dataSplitP = cleanUpString(str(dataProvo))
    dataSplitL = cleanUpString(str(dataLogan))

    #get AQI numbers per city
    aqiSLC = getAqiUS(dataSplitSLC)
    aqiO = getAqiUS(dataSplitO)
    aqiP = getAqiUS(dataSplitP)
    aqiL = getAqiUS(dataSplitL)

    #build the chart
    objects = ('Salt Lake City', 'Ogden', 'Provo', 'Logan')
    y_pos = np.arange(len(objects))
    performance = [aqiSLC, aqiO, aqiP, aqiL]

    plt.bar(y_pos, performance, align='center', alpha=0.5)
    plt.xticks(y_pos, objects)
    plt.ylabel('EPA standard AQI')
    plt.title('AQI in Utah')

    #build the file
    
    dtime = datetime.now().date().strftime("%m%d%y")

    title = "AQIdataUtah"
    
    plt.savefig('./output/{0}_{1}.png'.format(dtime, title))		
    
    
    
def cleanUpString(data):
    str1 = data.replace('\'', '')
    str2 = str1.replace(':', '')
    str3 = str2.replace(',', '')
    str4 = str3.replace('{', '')
    str5 = str4.replace('}', '')

    dataSplit = str5.split(" ")
    return dataSplit

def getAqiUS(dataSplit):
    i = 0
    while(i < len(dataSplit)):
        if(dataSplit[i] == "aqius"):
            return int(dataSplit[i+1])
        i += 1

def getMainUS(dataSplit):
    i = 0
    while(i < len(dataSplit)):
        if(dataSplit[i] == "mainus"):
            return dataSplit[i+1]
        i += 1

asyncio.run(main())

    
