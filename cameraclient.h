#ifndef CAMERACLIENT_H
#define CAMERACLIENT_H

#include "cctcpdatadefine.h"
#include "h264decoder.h"

typedef void (*UpdateVideo2GUI_CallBack)(rgbDataDefine * rgbData,unsigned long userData);

class CameraClient
{
public:
    CameraClient();
    ~CameraClient();

    bool startTCPSocketConnection(CC_NetConnectInfo * connectionInfo);

    void stopTCPSocketlient();

    void setupUpdateGUICallBack(UpdateVideo2GUI_CallBack callback,unsigned long userData);

private:
    void initTCPCSocketConnection(CC_NetConnectInfo * connectionInfo);

private:
    char                        m_IPAdress[64];                 //camIP
    int                         m_port;                       //端口
    char                        m_userName[13];                  //用户名
    char                        m_password[13];                  //密码

    int                         m_cSockfd;                      //命令套接字.
    int                         m_dSockfd;                      //数据通道套接字.

    int                         m_videoID;      //视频ID

    struct   sockaddr_in        m_cSockaddr_in;
    struct   sockaddr_in        m_dSockaddr_in;

    bool                        m_recvDataToggle;
    bool                        m_recvCommandToggle;

    pthread_mutex_t             mutex_cRecv;
    pthread_mutex_t             mutex_cSend;
    pthread_mutex_t             mutex_dRecv;
    pthread_mutex_t             mutex_dSend;

    UpdateVideo2GUI_CallBack m_updateVideo2GUI_CallBack;
    unsigned long m_userData;

};

#endif // CAMERACLIENT_H
