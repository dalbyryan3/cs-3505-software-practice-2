# Set compiler
CC=g++ -std=gnu++17

# Directory that contains source files (.cpp) and header files(.h)
SRC := src
# Directory to hold .o files during compilation
OBJ := obj
# Directory to hold ouputted binary files (like executable)
BIN := bin
  
# Use pkg-config for getting CFLAGS and LDLIBS for ffmpeg
FFMPEG_LIBS=    libavdevice                        \
                libavformat                        \
                libavfilter                        \
                libavcodec                         \
                libswresample                      \
                libswscale                         \
                libavutil                          \
# C flags
CFLAGS := -Wall -g           # some warnings about bad code and to output debugger info
CFLAGS := $(shell pkg-config --cflags $(FFMPEG_LIBS)) $(CFLAGS)
# Library flags
LDLIBS := $(shell pkg-config --libs $(FFMPEG_LIBS)) $(LDLIBS)


# Stuff should be set for using FFMPEG libs up to here so now build files being developed

# Indicate these are not real targets
.PHONY: all clean

# Default rule which will fire off compiling both the movie_builder and tests (and first creating bin and obj directories if necessary)
all: $(OBJ) $(BIN) $(BIN)/movie_builder $(BIN)/background_image_splicer_test $(BIN)/spliced_image_movie_generator_test

# Make the movie_builder target
$(BIN)/movie_builder: $(OBJ)/movie_builder.o $(OBJ)/spliced_image_movie_generator.o $(OBJ)/background_image_splicer.o 
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
# Make the background_image_splicer_test target
$(BIN)/background_image_splicer_test: $(OBJ)/background_image_splicer_test.o $(OBJ)/background_image_splicer.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
# Make the spliced_image_movie_generator_test target
$(BIN)/spliced_image_movie_generator_test: $(OBJ)/spliced_image_movie_generator_test.o $(OBJ)/spliced_image_movie_generator.o $(OBJ)/background_image_splicer.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

# Make object files
$(OBJ)/movie_builder.o: $(SRC)/movie_builder.cpp $(SRC)/background_image_splicer.h
	$(CC) -o $@ -c $< $(CFLAGS)
$(OBJ)/background_image_splicer.o: $(SRC)/background_image_splicer.cpp $(SRC)/background_image_splicer.h
	$(CC) -o $@ -c $< $(CFLAGS)
$(OBJ)/background_image_splicer_test.o: $(SRC)/background_image_splicer_test.cpp $(SRC)/background_image_splicer.h
	$(CC) -o $@ -c $< $(CFLAGS)
$(OBJ)/spliced_image_movie_generator.o: $(SRC)/spliced_image_movie_generator.cpp $(SRC)/spliced_image_movie_generator.h
	$(CC) -o $@ -c $< $(CFLAGS)
$(OBJ)/spliced_image_movie_generator_test.o: $(SRC)/spliced_image_movie_generator_test.cpp $(SRC)/spliced_image_movie_generator.h $(SRC)/background_image_splicer.h
	$(CC) -o $@ -c $< $(CFLAGS)

# Make necessary bin and obj directories if they do not exist
$(OBJ):
	mkdir $@
$(BIN):
	mkdir $@

# Clean rule
clean:
	@$(RM) -rv $(BIN)/* $(OBJ)/* # The @ disables the echoing of the command
