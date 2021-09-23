#ifndef SPLICED_IMAGE_MOVIE_GENERATOR
#define SPLICED_IMAGE_MOVIE_GENERATOR

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

extern "C"
{
    #include <libavformat/avformat.h>
    #include <libavfilter/avfilter.h>
    #include <libavutil/imgutils.h>
    #include <libavcodec/avcodec.h>
    #include <libswscale/swscale.h>
}

namespace movie_builder
{
	class spliced_image_movie_generator
	{
		public:
			spliced_image_movie_generator(const AVFrame *in);
			int make_movie(int frames);
			
		private:
		
		    const AVFrame * frame;
		    //AVFrame * crop_frame(const AVFrame *in, int left, int top, int right, int bottom);
		    AVFrame * crop_frame(const AVFrame *in, int left, int width, int height);
		    int write_frame(AVFrame *frame, const char * name);

	};
}

#endif