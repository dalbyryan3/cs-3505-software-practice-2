/*
 * Peter's codec encoder - high quality (RGB24), no compression.
 * 
 * This is an old solution from 2019.  It has been updated for inclusion
 * in ffmpeg during Fall, 2020.
 */

#include "libavutil/imgutils.h"
#include "libavutil/avassert.h"
#include "avcodec.h"
#include "bytestream.h"
#include "internal.h"

static av_cold int cool_encode_init(AVCodecContext *avctx)
{
  // Make sure we are receiving the correct type of image.
  
  if (avctx->pix_fmt != AV_PIX_FMT_RGB24)
  {
    av_log(avctx, AV_LOG_ERROR, "Only RGB24 is supported\n");
    return AVERROR(EINVAL);
  }
  
  // Set up the context for receiving a picture.
  
  avctx->bits_per_coded_sample = 24;  // Specify rgb24

  // Indicate success.
  
  return 0;
}


static int cool_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                            const AVFrame *pic, int *got_packet)
{
    int result, x, y, b;
    uint8_t *output_data;
    
    // Debugging variables.
    
    static int reported = 0;

    // Debugging message.
    
    if (!reported)
    {
      av_log(avctx, AV_LOG_INFO, "*** CS 3505:  Executing in coolenc.c\n");
      av_log(avctx, AV_LOG_INFO, "*** CS 3505:  Codec by Peter Jensen ***\n");
      reported = 1;
    }
    
    // Allocate an output memory buffer.

    
    result = ff_alloc_packet2(avctx, pkt,
			      14 + avctx->width * avctx->height * 3,
			      14 + avctx->width * avctx->height * 3);  // Should be 13 + 

    if (result < 0)
        return result;

    output_data = pkt->data;

    // Write the header.    

    bytestream_put_byte(&output_data, 'c');
    bytestream_put_byte(&output_data, 'o');
    bytestream_put_byte(&output_data, 'o');
    bytestream_put_byte(&output_data, 'l');

    // Meaningless byte to block students who are incorrectly using this format.
    //   (Not relevant in 2019, but I'm leaving it and the other harmless
    //   flaw in to help check for plagiarism.)
    bytestream_put_byte(&output_data, ((char) output_data));  
    
    bytestream_put_le32(&output_data, avctx->width);
    bytestream_put_be32(&output_data, avctx->height);

    // Write the bytes.
    
    for (y = 0; y < avctx->height; y++)
      for (x = 0; x < avctx->width; x++)
	for (b = 0; b < 3; b++)
          bytestream_put_byte(&output_data, pic->data[0][y*pic->linesize[0]+x*3+b]);

    // Cite: bmp - unknown why a single frame is marked as a key frame.
    // Update -- This is because single images are processed by ffmpeg as video.
    // Video starts with a key frame, so it makes sense that an image would be
    // it's own key frame.

    pkt->flags |= AV_PKT_FLAG_KEY;

    *got_packet = 1;
    return 0;
}


static av_cold int cool_encode_close(AVCodecContext *avctx)
{
  // Indicate success.
  
  return 0;
}


AVCodec ff_cool_encoder = {
    .name           = "cool",
    .long_name      = NULL_IF_CONFIG_SMALL("Peter's cool encoder"),
    .type           = AVMEDIA_TYPE_VIDEO,
    .id             = AV_CODEC_ID_COOL,
    .init           = cool_encode_init,
    .encode2        = cool_encode_frame,
    .close          = cool_encode_close,
    .pix_fmts       = (const enum AVPixelFormat[]){
    AV_PIX_FMT_RGB24, AV_PIX_FMT_NONE
    },
};
