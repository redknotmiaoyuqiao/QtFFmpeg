#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(QRect(0,0,640,360));

    m_cameraClient = new CameraClient();
    m_cameraClient->setupUpdateGUICallBack(updateVideo2GUI,(unsigned long)this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateVideo2GUI(rgbDataDefine * rgbData,unsigned long userData)
{
    MainWindow * window = (MainWindow *)userData;
    if(window != NULL){
        window->onRecvFrame((unsigned char *)rgbData->dataBuffer,rgbData->width,rgbData->height);
    }
}

void MainWindow::onRecvFrame(unsigned char * data,int width,int height)
{

}

void MainWindow::PaintImage(QPainter &painter)
{

}

void MainWindow::paintEvent(QPaintEvent *)
{

}
