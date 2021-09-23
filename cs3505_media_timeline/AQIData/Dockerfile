FROM python:3-slim
RUN apt-get update && apt-get install build-essential -y

COPY . /aqi_data
WORKDIR /aqi_data
RUN mkdir /aqi_data/output

RUN pip install -r requirements.txt

CMD python GetAQI.py

