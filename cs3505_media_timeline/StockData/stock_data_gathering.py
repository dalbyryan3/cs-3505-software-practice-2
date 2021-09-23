import pandas as pd
from alpha_vantage.timeseries import TimeSeries
import matplotlib.pyplot as plt
from datetime import date, timedelta, datetime
import random
from pathlib import Path


# Use AlphaVantage api to get stock data, randomly select stock to get out of choices
api_key_stream = open("AlphaVantageAPIKey.txt", "r")
api_key = api_key_stream.read()
index_list = ['AAPL', 'GOOGL', 'MSFT', 'TWTR' , 'FB']
index_name = random.choice(index_list) 
ts = TimeSeries(key=api_key, output_format='pandas')
data, meta_data = ts.get_intraday(symbol=index_name, interval='1min', outputsize='full')

# Create output file
date_string = data.index[0].strftime(r"%m%d%y")
day_to_select = (data.index[0]).strftime(r'%Y-%m-%d')
data_to_plot = data.loc[day_to_select]
data_to_plot = data_to_plot['4. close']
plt.figure();
plt.title('{0} {1} Time Series Stock Data'.format(index_name, day_to_select))
data_to_plot.plot()

# Output file information
image_diplay_name = '{0}TimeSeriesStockData'.format(index_name)
output_filepath = Path('./output/{0}_{1}.png'.format(date_string, image_diplay_name))
output_filepath.parent.mkdir(parents=True,exist_ok=True) # Make necessary directories if they do not exists
output_filepath.unlink(missing_ok=True) # Remove old file if it exists
plt.savefig(output_filepath.__str__())
plt.close()
