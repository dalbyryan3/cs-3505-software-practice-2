This docker image is based on the ubunutu image. Pull ubunutu before you build the docker image.

From within ```NewsData/newsdata``` build the containter with ```docker build --tag newsdata .``` and it's good to use. 
(Only need to build once)

The files are saved within the docker image so you have to mount it to external storage when running, i.e.

```docker run --mount type=bind,source={EXTERNAL STORAGE LOCATION},target="/output" newsdata python3 gnews.py```
