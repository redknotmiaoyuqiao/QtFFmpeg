#ifndef H264DECODER_H
#define H264DECODER_H

typedef struct rgbDataDefine
{
    int width;
    int height;
    int bufferSize;
    unsigned char * dataBuffer;
} RGBDataDefine;

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class H264Decoder
{
public:
    H264Decoder();
    ~H264Decoder();

    int DecodeH264Frames(unsigned char * inputBuffer,int aLength,RGBDataDefine * outputBuffer);

private:
    int pictureWidth;

    int setRecoderREsolveState;

    AVCodec * pCodec;
    AVCodecContext * pCodecCtx;
    AVFrame * pVideoFrame;
    AVPacket pAvPacket;

    AVPicture outPicture;

    struct SwsContext * imgConverCtx;

    void copyDecodedFrame(unsigned char * src);
};

#endif // H264DECODER_H
