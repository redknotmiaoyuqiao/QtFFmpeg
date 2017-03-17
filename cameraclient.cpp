#include "cameraclient.h"

CameraClient::CameraClient()
{
    m_videoID = 0;
    m_recvCommandToggle = false;
    m_recvDataToggle = false;

    pthread_mutex_init(&mutex_cRecv,NULL);
    pthread_mutex_init(&mutex_cSend,NULL);
    pthread_mutex_init(&mutex_dRecv,NULL);
    pthread_mutex_init(&mutex_dSend,NULL);
}

CameraClient::~CameraClient()
{

}

bool CameraClient::startTCPSocketConnection(CC_NetConnectInfo * connectionInfo)
{
    printf("IP:%s\n" ,connectionInfo->server_ip);
    printf("PORT:%s\n" ,connectionInfo->port);
    printf("USER:%s\n" ,connectionInfo->user_name);
    printf("PASS:%s\n" ,connectionInfo->pass_word);

    memcpy(m_IPAdress,connectionInfo->server_ip,sizeof(m_IPAdress));
    memcpy(m_userName,connectionInfo->user_name,sizeof(m_userName));
    memcpy(m_password,connectionInfo->pass_word,sizeof(m_password));

    m_port = connectionInfo->port;

    int ret = this->initTCPCSocketConnection(connectionInfo);

    if(ret == 0){
        //新建线程
    }
}

void CameraClient::initTCPCSocketConnection(CC_NetConnectInfo * connectionInfo)
{
    printf("控制命令socket初始化:...........\n");

    memset(&m_cSockaddr_in, 0, sizeof(struct sockaddr_in));

    m_cSockfd=socket(AF_INET,SOCK_STREAM,0);

    printf("controll socket init %d\n",m_cSockfd);

    if(m_cSockfd<0){
        printf("socket error!\n");
        return -1;
    }

    m_cSockaddr_in.sin_family=AF_INET;
    m_cSockaddr_in.sin_port=htons(connectionInfo->port);
    m_cSockaddr_in.sin_addr.s_addr=htons(INADDR_ANY);


    if(inet_pton(AF_INET,m_IPAdress,&m_cSockaddr_in.sin_addr.s_addr)<=0)
    {
        printf("inet_pton error!!!\n");
        return -1;
    }
    //非阻塞的connect模式.
    int flags=fcntl(m_cSockfd, F_GETFL,0);
    fcntl(m_cSockfd, F_SETFL,flags|O_NONBLOCK);

    int connetRet=connect(m_cSockfd,(struct sockaddr*)&m_cSockaddr_in,sizeof(struct sockaddr));
    printf("socket connection result: %d\n",connetRet);

    //设置回阻塞模式.
    int flags1=fcntl(m_cSockfd, F_GETFL,0);
    fcntl(m_cSockfd, F_SETFL,flags1 &(~O_NONBLOCK));


    struct timeval timeout={2,0};

    int nRet1=setsockopt(m_cSockfd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(struct timeval));

    if(nRet1<0){
        printf("setsockopt1 error!!!\n");
        return -1;
    }

    int nRet2=setsockopt(m_cSockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(struct timeval));

    if(nRet2<0){
        printf("setsockopt2 error!!!\n");
        return -1;
    }

    return 0;
}

void CameraClient::stopTCPSocketlient()
{
    puts("Client:---------------------STOP------------------");
    m_recvCommandToggle = false;
    m_recvDataToggle = false;

    if(m_dSockfd > 0){
        close(m_dSockfd);
        m_dSockfd = -1;
    }

    if(m_cSockfd > 0){
        close(m_cSockfd);
        m_cSockfd = -1;
    }
}

void CameraClient::setupUpdateGUICallBack(UpdateVideo2GUI_CallBack callback,unsigned long userData)
{
    m_updateVideo2GUI_CallBack = callback;
    m_userData = userData;
}
