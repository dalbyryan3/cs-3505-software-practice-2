## To use this container:
- From within StockData run (This only needs to be done once):
- `docker build --tag stock_data .`
- Then can run container. -d fires the container then stops it when done:
- `docker run -d --mount type=bind,source="$(pwd)"/output,target="/stock_data/output" stock_data`
- **This command will fire the container and get an output image in /stock_data/output which is bound to $(pwd)/output**
- This output image will be in a MMDDYY_<Text which describes the output image>
- Note: Could copy file from "$(pwd)/output to a universal folder after the container is executed
- Also note: the source filepath is if container is run inside the StockData folder.
