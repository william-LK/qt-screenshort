#include "mainwindow.h"
#include "capturescreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 点击截图按钮开始截图;
    capturescreen* captureHelper = new capturescreen();
    captureHelper->show();
    return a.exec();
}
