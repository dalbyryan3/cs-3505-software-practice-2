#ifndef BACKGROUND_IMAGE_SPLICER_H
#define BACKGROUND_IMAGE_SPLICER_H

#include <string>
#include <vector>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

namespace movie_builder
{
	class background_image_splicer
	{
		const std::string background_image_path;
		const std::vector<std::string> images_to_splice_paths;
		const int background_height;
		const int background_width;

		public:
			background_image_splicer(int bg_height, int bg_width, const std::string &background_image_filepath, std::vector<std::string> const &images_to_splice_filepaths);
			AVFrame* splice_background_and_images(const std::string &output_image_path);
		private:
			void splice_two_images(std::string text, const double scale_factor, const int x_loc, const int y_loc, const std::string &background_path, const std::string &image_path, const std::string &output_image_path);
			AVFrame* open_file(std::string filename);
			
	};
}

#endif
