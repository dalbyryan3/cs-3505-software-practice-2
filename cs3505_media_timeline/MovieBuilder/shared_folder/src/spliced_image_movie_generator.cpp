#include "spliced_image_movie_generator.h"

movie_builder::spliced_image_movie_generator::spliced_image_movie_generator(const AVFrame *in)
{
    frame = in;
}

int movie_builder::spliced_image_movie_generator::make_movie(int frames)
{
    
    AVFrame *cropped;
    
    //determine how many pixels to move with each crop
    double to_move_dbl = ((double)(frame->width - frame->height))/((double)frames);
    int to_move = (int) to_move_dbl;
    int left = 0;
    int right = frame->width - (frame->height);
    
    /* std::cout << to_move << std::endl; */

    for(int i=0; i < frames; i++)
    {
        //std::cout << left << std::endl;   
        //std::cout << right << std::endl; 
        //cropped = crop_frame(frame, left, 0, right, (int) frame->height);
        //cropped = crop_frame(frame, left, 0, right, 0);
        cropped = crop_frame(frame, left, frame->width, frame->height);
        if (cropped == NULL)
        {
            std::cout << "stopping. " << std::endl;
            return -1;
        }
        
        char namebuffer[32];
        snprintf(namebuffer, sizeof(char) * 32, "./pics/to_movie%i.bmp", i);
        write_frame(cropped, namebuffer);
        
        av_frame_free(&cropped);
        left = left + to_move;
        //right = right - to_move;
        right = frame->width - (left + frame->height);
        if (right < 0)
        {
            std::cout << "reached end of image, " << i << " frames produced" << std::endl;
            system("cd ./pics && ffmpeg -y -i ./to_movie%d.bmp a_vid_out.avi");
            return 0;
        
        }
    }
    
    system("cd ./pics && ffmpeg -y -i ./to_movie%d.bmp a_vid_out.avi");
    
    //return 0;
}

AVFrame * movie_builder::spliced_image_movie_generator::crop_frame(const AVFrame *in, int left, int width, int height)			
//AVFrame * movie_builder::spliced_image_movie_generator::crop_frame(const AVFrame *in, int left, int top, int right, int bottom)
{
    // output frame
    AVFrame *output = av_frame_alloc();
    int error_code;
    
    output->format = in->format;
    //output->width = in->width;
    //output->height = in->height;
    output->width = height;
    output->height = height;
    output->channels = in->channels;
    output->channel_layout = in->channel_layout;
    output->nb_samples = in->nb_samples;
    av_frame_get_buffer(output, 32);
    //av_frame_copy(copyFrame, frame);
    //av_frame_copy_props(copyFrame, frame);
    
    
     for (int x = 0; x < height; x++)
        for (int y = 0; y < height; y++)
            for (int b=0; b < 3; b++)
                output->data[0][y*output->linesize[0]+x*3 + b] = in->data[0][y*in->linesize[0]+(x+left)*3 + b];
    
    return output;
    
    /*
    error_code = av_frame_copy(output, in);
    if (error_code < 0)
    {
        std::cout << "could not copy frame" << std::endl;
        return NULL;
    }
    
    output->crop_top = top;
    output->crop_bottom = bottom;
    output->crop_left = left;
    output->crop_right = right;
    
    
    error_code = av_frame_apply_cropping(output, 0);
    if (error_code < 0)
    {
        std::cout << "could not crop frame" << std::endl;
        return NULL;
    }
    
    if (output->width > output->height)
    {
        std::cout << "trying again" << std::endl;
        output->crop_left = output->width - output->height;
        av_frame_apply_cropping(output, 0);
    }
    
    std::cout << output->width << std::endl;   
    std::cout << output->height << std::endl;
    
    return output;*/
}
		    
int movie_builder::spliced_image_movie_generator::write_frame(AVFrame *frame, const char * name)
{
    /* std::cout << "Writing image..." << std::endl; */
    
    AVCodec * out_codec = avcodec_find_encoder(AV_CODEC_ID_BMP);
    if (out_codec == NULL)
    {
        
        std::cout << "Failed to write file" << std::endl;
        return -1;
        
    }
    
    
    AVCodecContext * out_ctx = avcodec_alloc_context3(out_codec);
    if (out_ctx == NULL)
    {
        
        std::cout << "Failed to write file" << std::endl;
        return -1;
        
    }
    
    out_ctx->pix_fmt = AV_PIX_FMT_BGR24;
    out_ctx->width = frame->width;
    out_ctx->height = frame->height;
    out_ctx->time_base.num = 1;
    out_ctx->time_base.den = 1;
    
    avcodec_open2(out_ctx, out_codec, NULL);
    
    AVPacket packet;
    av_init_packet(&packet);
    packet.data = NULL;
    packet.size = 0;
    
    
    int done;
    int size;
    size = avcodec_encode_video2(out_ctx, &packet, frame, &done);
    if (size < 0)
    {
        std::cout << "Error durning encoding" << std::endl;
        return -1;
        
    }
    
    /* std::cout << "encoded!" << std::endl; */
    
    /* std::cout << "writing file" << std::endl; */
    
    std::ofstream out_file(name);
    out_file.write((const char *) packet.data, packet.size);
    
    out_file.close();
    return 0;
    
}
