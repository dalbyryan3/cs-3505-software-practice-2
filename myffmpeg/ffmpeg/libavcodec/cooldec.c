/*
 * Peter's codec decoder.
 * 
 * This is an old solution from 2019.  It has been updated for inclusion
 * in ffmpeg during Fall, 2020.
 */

#include "avcodec.h"
#include "bytestream.h"
#include "internal.h"
#include "msrledec.h"

static int cool_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    // Input variables.

    const uint8_t *input_data;
    int            input_data_size;

    // Output variables.
    
    AVFrame *pic;
    int result;

    // Loop variables.

    int x, y, b;

    // Debugging variables.
    
    static int reported = 0;

    // Debugging message.
    
    if (!reported)
    {
      av_log(avctx, AV_LOG_INFO, "*** CS 3505:  Executing in cooldec.c\n");
      av_log(avctx, AV_LOG_INFO, "*** CS 3505:  Codec by Peter Jensen ***\n");
      reported = 1;
    }

    // Check input data for validity, extract image dimensions.
    
    input_data = avpkt->data;
    input_data_size = avpkt->size;

    if (input_data_size < 12)
    {
      av_log(avctx, AV_LOG_ERROR, "File is too short\n");
      return AVERROR_INVALIDDATA;	
    }          
    
    if (bytestream_get_byte(&input_data) != 'c' ||
	bytestream_get_byte(&input_data) != 'o' ||
	bytestream_get_byte(&input_data) != 'o' ||
	bytestream_get_byte(&input_data) != 'l')
    {
      av_log(avctx, AV_LOG_ERROR, "Corrupt COOL file\n");
      return AVERROR_INVALIDDATA;
	
    }
    
    bytestream_get_byte(&input_data);  // Ignore meaningless byte

    avctx->width   = bytestream_get_le32(&input_data);
    avctx->height  =  bytestream_get_be32(&input_data);
    avctx->pix_fmt = AV_PIX_FMT_RGB24;
    
    if (input_data_size < 12 + avctx->width * avctx->height * 3  )
    {
      av_log(avctx, AV_LOG_ERROR, "File is too short\n");
      return AVERROR_INVALIDDATA;	
    } 
    
    // Create output picure buffer of size specified in the context

    pic = data;
    result = ff_get_buffer(avctx, pic, 0);
    
    if (result < 0)
        return result;


    /* Cite: bmp  Again, I'm unsure of these settings, but it appears to
       indicate that it's an image and a key frame.  */
    
    pic->pict_type = AV_PICTURE_TYPE_I; 
    pic->key_frame = 1;

    /* End */
    
    // Set pixel data

    for (y = 0; y < avctx->height; y++)
      for (x = 0; x < avctx->width; x++)
	for (b = 0; b < 3; b++)
          pic->data[0][y*pic->linesize[0]+x*3 + b] = bytestream_get_byte(&input_data);
    
    // Indicate that we decoded a frame and return how many bytes we consumed.
    
    *got_frame = 1;

    return input_data_size;
}

AVCodec ff_cool_decoder = {
    .name           = "cool",
    .long_name      = NULL_IF_CONFIG_SMALL("Peter's cool decoder"),
    .type           = AVMEDIA_TYPE_VIDEO,
    .id             = AV_CODEC_ID_COOL,
    .decode         = cool_decode_frame,
    .capabilities   = AV_CODEC_CAP_DR1,
};
