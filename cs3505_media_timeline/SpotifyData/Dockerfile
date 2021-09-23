FROM python:3-slim
RUN apt-get update && apt-get install build-essential -y

COPY . /spotify_data
WORKDIR /spotify_data


RUN pip install -r requirements.txt

CMD python get_new_releases.py 
