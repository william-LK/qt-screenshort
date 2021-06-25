#ifndef CAPTURESCREEN_H
#define CAPTURESCREEN_H

// 基础类
#include <QWidget>
// 画笔
#include <QPainter>


class capturescreen : public QWidget
{
    Q_OBJECT
// 公开成员
public:
    explicit capturescreen(QWidget *parent = nullptr);

// 信号
signals:
    void signalCompleteCature(QPixmap catureImage);

// 私有函数成员
private:
    // 初始化窗口
    void initWindow();
    // 读取背景和像素图
    void loadBackgroundPixmap();
    // 鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
    // 鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    // 鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event);
    // 绘图事件
    void paintEvent(QPaintEvent *event);
    // 监听点击事件
    void keyPressEvent(QKeyEvent *event);
    // 计算区域
    QRect getRect(const QPoint &beginPoint,const QPoint &endPoint);
// 私有状态成员
private:
    // 像素属性
    QPixmap m_loadPixmap, m_capturePixmap;
    // 屏幕宽高
    int m_screenwidth;
    int m_screenheight;
    // 按下状态
    bool m_isMousePress;
    // 开始坐标与结束坐标
    QPoint m_beginPoint, m_endPoint;
    // 绘图实例
    QPainter m_painter;
};





#endif // CAPTURESCREEN_H
