#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cameraclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onRecvFrame(unsigned char * data,int width,int height);

private:

    QMutex m_mutex;

    QImage m_image;

    Ui::MainWindow *ui;

    CameraClient * m_cameraClient;

private:

    void paintEvent(QPaintEvent *);

    void PaintImage(QPainter &painter);

    void static updateVideo2GUI(rgbDataDefine * rgbData,unsigned long userData);
};

#endif // MAINWINDOW_H
