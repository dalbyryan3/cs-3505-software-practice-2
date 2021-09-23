FROM ubuntu

SHELL ["/bin/bash", "-c"]

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ="America/Salt Lake City"

#install needed libraries
RUN apt-get -y update && apt-get -y install \
  apt-utils \
  emacs-nox \
  git-core \
  g++ \
  python3 \
  python3-pip

RUN pip3 install tweepy
RUN pip3 install datetime
RUN pip3 install requests && pip3 install Pillow

RUN mkdir /output



# Copy in the python folder and the font for image processing

COPY . /twitter_data
WORKDIR /twitter_data
#ADD twitter.py

#RUN mkdir ./files ;

#ADD ./twitter.py ./files/

#RUN cd ./files;

CMD python3 twitter.py 
