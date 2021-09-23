FROM python:3-slim
RUN apt-get update && apt-get install build-essential -y

COPY . /twitch_data
WORKDIR /twitch_data

RUN pip install -r requirements.txt


CMD python datagather.py