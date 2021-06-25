#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->menubar->setNativeMenuBar(false);
    //
    connect(ui->actionnew,&QAction::trigger,[=](){
        // 对话框 分类
        // 模态对话框（不可以对其他窗口进行操作） 非模态对话框（可以对其他窗口进行操作）
        // 模态创建
        QDialog dlg(this);
        dlg.exec();
        qDebug() << "模态对话框弹出";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

