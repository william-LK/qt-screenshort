#include "capturescreen.h"
#include "QApplication"
#include "QGuiApplication"
#include "QScreen"
#include "QWindow"
#include "QMouseEvent"
#include "QPoint"
#include "QColor"
#include "QPaintEvent"
#include "QRect"
#include <QDesktopWidget>
// 构造函数
capturescreen::capturescreen(QWidget *parent) : QWidget(parent)
{
    initWindow();
    loadBackgroundPixmap();
}


// 初始化窗口
void capturescreen::initWindow(){
    // 开启窗口部件跟踪鼠标
    this->setMouseTracking(true);
    // 设置无边框化
    this->setWindowFlags(Qt::FramelessWindowHint);
    // 窗口 变为活动的窗口 | 窗口 填充整个屏幕，无边框
    setWindowState(Qt::WindowActive | Qt::WindowFullScreen);
}

// 读取背景和像素图
void capturescreen::loadBackgroundPixmap(){
     //抓取当前屏幕的图片;
    m_loadPixmap=QPixmap::grabWindow(QApplication::desktop()->winId());
    // 拿到宽高
    m_screenwidth = m_loadPixmap.width();
    m_screenheight = m_loadPixmap.height();
}

// 鼠标按下
void capturescreen::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        // 把状态设置为按下
        m_isMousePress = true;
        // 记录开始的坐标
        m_beginPoint = event->pos();
    }
    // 让鼠标事件继续执行
    return QWidget::mousePressEvent(event);
}

// 鼠标移动
void capturescreen::mouseMoveEvent(QMouseEvent *event){
    if(m_isMousePress){
        // 记录结束的坐标
        m_endPoint = event->pos();
        // 更新界面
        update();
    }
    return QWidget::mouseMoveEvent(event);
}

// 鼠标释放事件
void capturescreen::mouseReleaseEvent(QMouseEvent *event){
    // 记录结束位置
    m_endPoint = event->pos();
    // 修改按下状态
    m_isMousePress = false;
    return QWidget::mouseReleaseEvent(event);
}

// 绘图事件  update执行会触发这个事件   过程是先重绘 然后贴背景图  然后在上层加一层阴影
void capturescreen::paintEvent(QPaintEvent *event){
    m_painter.begin(this);  //进行重绘;
    QColor shadowColor = QColor(0, 0, 0, 100);                      //阴影颜色设置；
    m_painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));    //设置画笔;
    m_painter.drawPixmap(0, 0, m_loadPixmap);                       //将背景图片画到窗体上;
    m_painter.fillRect(m_loadPixmap.rect(), shadowColor);           //画影罩效果;

    // 如果是按下状态
    if(m_isMousePress){
        // 获取选择的区域大小
        QRect selectedRect = getRect(m_beginPoint, m_endPoint);
        // 从背景图中拿到截取区域
        QRect iRect = QRect(selectedRect.x() * 2, selectedRect.y() * 2, selectedRect.width() * 2, selectedRect.height() * 2);
        m_capturePixmap = m_loadPixmap.copy(iRect);
        m_capturePixmap.scaled(selectedRect.x(),selectedRect.y());
        // 定位左上角 并写入截取的图片
        m_painter.drawPixmap(selectedRect.topLeft(),m_capturePixmap);
        // 绘制矩形
        m_painter.drawRect(selectedRect);
    }

    m_painter.end();  //重绘结束;
}

// 计算截图区域
//QRect capturescreen::getRect(const QPoint &beginPoint, const QPoint &endPoint)
//{
//    // 定义坐标宽高先
//    int x,y,width,height;
//    // qAbs 返回计算结果的绝对值
//    width = qAbs(beginPoint.x() - endPoint.x());
//    height = qAbs(beginPoint.y() - endPoint.y());
//    // 正向截图和反向截图判断
//    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
//    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();
//    // 获取区域结果
//    QRect selectedRect = QRect(x, y, width, height);

//    // 避免宽或高为零时拷贝截图有误;
//    // 可以看QQ截图，当选取截图宽或高为零时默认为2;
//    if (selectedRect.width() == 0)
//    {
//        selectedRect.setWidth(1);
//    }
//    if (selectedRect.height() == 0)
//    {
//        selectedRect.setHeight(1);
//    }
//    return selectedRect;
//}
QRect capturescreen::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x, y, width, height;
    width = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    QRect selectedRect = QRect(x, y, width, height);
    // 避免宽或高为零时拷贝截图有误;
    // 可以看QQ截图，当选取截图宽或高为零时默认为2;
    if (selectedRect.width() == 0)
    {
        selectedRect.setWidth(1);
    }
    if (selectedRect.height() == 0)
    {
        selectedRect.setHeight(1);
    }

    return selectedRect;
}

// 重写键盘事件
void capturescreen::keyPressEvent(QKeyEvent *event)
{
    // Esc 键退出截图;
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }
    // Eeter键完成截图;
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        signalCompleteCature(m_capturePixmap);
        close();
    }
}











