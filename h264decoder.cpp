#include "h264decoder.h"

H264Decoder::H264Decoder()
{
    //初始化
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
        printf("avcodec_find_decoder() Fail!\n");
        return;
    }

    pCodecCtx = avcodec_alloc_context3(pCodec);
    if(pCodecCtx == NULL){
        printf("avcodec_alloc_context3() Fail!\n");
        return;
    }

    avcodec_open2(pCodecCtx,pCodec,NULL);

    pVideoFrame = avcodec_alloc_frame();

    avpicture_alloc(&outPicture,PIX_FMT_RGB24,640,360);
}

H264Decoder::~H264Decoder()
{
    //释放资源
    if(pCodecCtx != NULL){
        avcodec_close(pCodecCtx);
        pCodecCtx = NULL;
    }

    if(pVideoFrame != NULL){
        avcodec_free_frame(&pVideoFrame);
        pVideoFrame = NULL;
    }

    if(&outPicture == NULL){
        avpicture_free(&outPicture);
    }

    if(imgConverCtx != NULL){
        sws_freeContext(imgConverCtx);
        imgConverCtx = NULL;
    }
}

int H264Decoder::DecodeH264Frames(unsigned char * inputBuffer,int aLength,RGBDataDefine * outputBuffer)
{
    int getPicPtr = 0;
    int result = 0;

    av_init_packet(&pAvPacket);
    pAvPacket.data = (unsigned char *)inputBuffer;
    pAvPacket.size = aLength;

    result = avcodec_decode_video2(pCodecCtx,pVideoFrame,&getPicPtr,&pAvPacket);

    if(getPicPtr){
        if(imgConverCtx == NULL){
            imgConverCtx = sws_getContext(pCodecCtx->width,pCodecCtx->height,pCodecCtx->pix_fmt,640,360,PIX_FMT_RGB24,SWS_FAST_BILINEAR,NULL,NULL,NULL);
        }
        //转 RGB
        //用 GPU 更好
        sws_scale(imgConverCtx,(const uint8_t**)pVideoFrame->data,pVideoFrame->linesize,0,pVideoFrame->height,outPicture.data,outPicture.linesize);

        outputBuffer->width = pCodecCtx->width;
        outputBuffer->height = pCodecCtx->height;
        outputBuffer->bufferSize = outPicture.linesize[0];
        outputBuffer->dataBuffer = outPicture.data[0];
    }

    av_free_packet(&pAvPacket);

    return 0;
}
