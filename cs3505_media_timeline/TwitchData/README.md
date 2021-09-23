## Container Info:
- This container returns the thumbnail image of the 6th most popular game being streamed on Twitch when the program is executed.
- The 6th most popular game was chosen as the top 5 games on Twitch have historically been the same games, and would lead to repetitive data.

## How to Run:
- Inside the folder, run:
- `docker build --tag twitch_data .`
- After it is finished building, run:
- `docker run -d --mount type=bind,source="$(pwd)"/Output,target=/twitch_data/Output twitch_data`
- This will add an image to the Output folder everytime it is ran.

## Image Info:
- Each image is given a name corresponding to its timestamp when it was retrieved.
- Each image has a size of 1280x720.
- Each image is a JPG.
