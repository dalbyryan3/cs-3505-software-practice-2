# Based on ubuntu, pull ubuntu before running


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
   
#get some more python libraries with pip
RUN pip3 install requests && pip3 install Pillow

#make output directory
# mount this to the the desired external storage location
RUN mkdir output



# Copy in the python folder and the font for image processing

COPY . /