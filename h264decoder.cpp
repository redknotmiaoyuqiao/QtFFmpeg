#include "h264decoder.h"

H264Decoder::H264Decoder()
{
    pCodec = NULL;
    pCodecCtx = NULL;
    pVideoFrame = NULL;

    imgConverCtx = NULL;

    pictureWidth = 0;
    setRecoderREsolveState = 0;

    av_register_all();
    avcodec_register_all();

    pCodec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if(pCodec == NULL){
        printf("avcodec_find_decoder() Fail");
        return;
    }


}

H264Decoder::~H264Decoder()
{

}
