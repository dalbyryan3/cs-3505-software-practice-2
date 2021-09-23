FROM python:3-slim
RUN apt-get update && apt-get install build-essential -y

COPY . /stock_data
WORKDIR /stock_data

RUN pip install -r requirements.txt

CMD python stock_data_gathering.py 

