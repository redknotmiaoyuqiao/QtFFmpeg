#ifndef CAMERACLIENT_H
#define CAMERACLIENT_H

#include "h264decoder.h"

typedef void (*UpdateVideo2GUI_CallBack)(rgbDataDefine * rgbData,unsigned long userData);

class CameraClient
{
public:
    CameraClient();
    ~CameraClient();
private:
    void UpdateVideo2GUI_CallBack(rgbDataDefine * rgbData,unsigned long userData);

    UpdateVideo2GUI_CallBack m_updateVideo2GUI_CallBack;
    unsigned long m_userData;
};

#endif // CAMERACLIENT_H
