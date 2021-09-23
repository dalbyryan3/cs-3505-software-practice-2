#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include "background_image_splicer.h"
#include <filesystem>

namespace movie_builder
{
	//Constructor for the image splicer object
	background_image_splicer::background_image_splicer(const int bg_height, const int bg_width, const std::string &background_image_filepath, std::vector<std::string> const &images_to_splice_filepaths) : background_image_path(background_image_filepath), images_to_splice_paths(images_to_splice_filepaths), background_height(bg_height), background_width(bg_width)
	{
	}

	// Returns a non NULL AVFrame pointer if successful
	AVFrame *background_image_splicer::splice_background_and_images(const std::string &output_image_path)
	{
		//initilize local vars
		int pic_count = 0;
		int num_pics = images_to_splice_paths.size();
		int const_pic_width = background_width / num_pics;
		
		for (const std::string &image_filepath : this->images_to_splice_paths)
		{
			AVFrame *image_AVFrame = this->open_file(image_filepath);
			if (image_AVFrame == NULL)
			{
				std::cout << "Failed to create AVFrame for " << image_filepath << std::endl;
			}
			//makes a string to put on the picture and removes the date from it
			std::string pic_name = std::filesystem::path(image_filepath).stem();
			pic_name = pic_name.substr(7,pic_name.length());
			//gets the details of the image to scale it properly
			int pic_width = image_AVFrame->width;
			int pic_height = image_AVFrame->height;
			double scale_factor = (double)const_pic_width / (double)pic_width;
			if (pic_height * scale_factor > background_height)
			{
				scale_factor = (double)background_height / (double)pic_height;
			}
			else
			{
				scale_factor = (double)const_pic_width / (double)pic_width;
			}
			int pic_buffer = (const_pic_width - (pic_width * scale_factor)) / 2;
			int x_loc;
			int y_loc = (background_height - (pic_height * scale_factor)) / 2;

			//This puts the first image on the background
			if (pic_count == 0)
			{
				x_loc = 0 + pic_buffer;
				this->splice_two_images(pic_name, scale_factor, x_loc, y_loc, this->background_image_path, image_filepath, output_image_path);
			}
			//This puts every other picture of the background and moves the file around so it won't overwrite any pictures.
			else
			{
				x_loc = (pic_count * const_pic_width) + pic_buffer;
				std::stringstream rename_command;
				rename_command << "mv " << output_image_path << " ./temp.jpg";
				system(rename_command.str().c_str());
				this->splice_two_images(pic_name, scale_factor, x_loc, y_loc, "./temp.jpg", image_filepath, output_image_path);
				std::stringstream remove_command;
				remove_command << "rm"
							   << " ./temp.jpg";
				system(remove_command.str().c_str());
			}
			pic_count = pic_count + 1;
		}
		//returns the frame
		return this->open_file(output_image_path);
	}
	/**
	 * This method puts the name we want in the top left of the image, and puts the image onto the background in the right place according
	 * to what picture number it is. 
	 */
	void background_image_splicer::splice_two_images(std::string text, const double scale_factor, const int x_loc, const int y_loc, const std::string &background_path, const std::string &image_path, const std::string &output_image_path)
	{
		std::stringstream ss;
		ss << "ffmpeg -nostats -loglevel 0 -y -i '" << image_path << "' -vf \"drawtext=fontfile=/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf:fontsize=24:text='" << text << "': fontcolor=black:box=1:boxcolor=white@0.7: x=0: y=0\" -y ./mod_pic.jpg";
		std::string command = ss.str();
		system(command.c_str());
		std::stringstream ss2;
		ss2 << "ffmpeg -nostats -loglevel 0 -y -i " << background_path << " -i ./mod_pic.jpg -filter_complex \"[1]scale=iw*" << scale_factor << ":-1[b];[0:v][b] overlay=x=" << x_loc << ":y=" << y_loc << "\" " << output_image_path;
		command = ss2.str();
		system(command.c_str());
		std::stringstream remove_command;
		remove_command << "rm"
					   << " ./mod_pic.jpg";
		system(remove_command.str().c_str());
	}

	/// Will return NULL if AVFrame could not be created
	AVFrame *background_image_splicer::open_file(std::string filename)
	{
		int error_code;

		AVFormatContext *format_ctx = NULL;
		error_code = avformat_open_input(&format_ctx, filename.c_str(), NULL, NULL);
		if (error_code != 0)
		{
			std::cout << "Could not open file: " << filename << std::endl;
			return NULL;
		}

		error_code = avformat_find_stream_info(format_ctx, NULL);
		if (error_code != 0)
		{
			std::cout << "Could not find the stream info for file: " << filename << std::endl;
			return NULL;
		}

		AVCodec *codec = NULL;
		codec = avcodec_find_decoder(format_ctx->streams[0]->codec->codec_id);
		if (codec == NULL)
		{
			std::cout << "Could not find the codec for file: " << filename << std::endl;
			return NULL;
		}

		AVCodecContext *codec_ctx = format_ctx->streams[0]->codec;
		error_code = avcodec_open2(codec_ctx, codec, NULL);
		if (error_code != 0)
		{
			std::cout << "Could not find open codec for file: " << filename << std::endl;
			return NULL;
		}

		AVFrame *frame;
		AVPacket packet;
		frame = av_frame_alloc();
		av_read_frame(format_ctx, &packet);
		int done;
		avcodec_decode_video2(codec_ctx, frame, &done, &packet);

		// Convert color format of the frame
		AVFrame *rgbFrame = av_frame_alloc();
		rgbFrame->width = frame->width;
		rgbFrame->height = frame->height;
		rgbFrame->format = AV_PIX_FMT_RGB24;

		int numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, codec_ctx->width, codec_ctx->height);
		uint8_t *buffer = (uint8_t*)av_malloc(numBytes);
		avpicture_fill((AVPicture*)rgbFrame, buffer, AV_PIX_FMT_RGB24, codec_ctx->width, codec_ctx->height);

		struct SwsContext *sws_ctx;
		sws_ctx = sws_getContext(frame->width, frame->height, (AVPixelFormat)frame->format, frame->width, frame->height, AV_PIX_FMT_RGB24, SWS_BILINEAR, NULL, NULL, NULL);

		sws_scale(sws_ctx, frame->data, frame->linesize, 0, codec_ctx->height, rgbFrame->data, rgbFrame->linesize);

		return rgbFrame;
	}

} // namespace movie_builder