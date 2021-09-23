# This image will be based on the ubuntu image.  Build it using the
# command in the comment below.  You may omit the ubuntu pull if you already
# did it.  Before running the build, change into the directory containing
# this Dockerfile.
#
# docker pull ubuntu
# docker build --tag myubuntu  .
# 
# (Don't forget the trailing . to specify that this directory is the context.)

FROM ubuntu

# Set a default shell.

SHELL ["/bin/bash", "-c"]

# The timezone library stops the docker build and waits for user input to
# select a timezone. This breaks the build. To get around this, 
# set up timezone information prior to installing that library. This
# Docker code does that. Composited from two sources:
# https://rtfm.co.ua/en/docker-configure-tzdata-and-timezone-during-build/
# https://serverfault.com/questions/949991/how-to-install-tzdata-on-a-ubuntu-docker-image

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ="America/Salt Lake City"

# Install a handful of useful libraries.  Note that this is generally against
# best practices -- containers should be lean, and not include 'things you
# might use'.  In our case, we're using the containers for development, so
# this may be reasonable here.

RUN apt-get -y update -qq && apt-get -y install \
   apt-utils \
   g++ \
   autoconf \
   automake \
   build-essential \
   cmake \
   git-core \
   libass-dev \
   libfreetype6-dev \
   libgnutls28-dev \
   libtool \
   libvorbis-dev \
   pkg-config \
   texinfo \
   wget \
   yasm \
   zlib1g-dev

RUN mkdir -p /ffmpeg_installation

RUN cd /ffmpeg_installation && git clone git://source.ffmpeg.org/ffmpeg.git ffmpeg && cd ffmpeg && git reset --hard f7fd205f11d5299d6a16b0ff0ae85fddb32772f2 

# Build ffmpeg
RUN cd /ffmpeg_installation/ffmpeg && ./configure --prefix=/ --enable-libfreetype && make ffmpeg && make install


# Copy MovieBuilder code that uses ffmpeg to build movie
COPY ./shared_folder /shared_folder
WORKDIR /shared_folder
RUN cd /shared_folder && make

# Make the MovieBuilder code, create execute statement that is ready for taking in outputs of other docker containers as inputs
ENTRYPOINT ["/shared_folder/execute_movie_builder.sh"] 
