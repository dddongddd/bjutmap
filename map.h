#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QPoint>

class map : public QWidget {
    Q_OBJECT

public:
    explicit map(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;  // 捕捉鼠标点击事件
    void mouseMoveEvent(QMouseEvent *event) override;   // 处理鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event) override; // 鼠标释放事件
    void paintEvent(QPaintEvent *event) override;       // 用于绘制地图和路径
    void resizeEvent(QResizeEvent *event) override;     // 处理窗口大小变化

private:
    QPoint currentPos;  // 当前的位置
    QPoint targetPos;   // 目标位置
    QPixmap mapPixmap;  // 存储地图图像

    bool resizing;       // 是否正在调整窗口大小
    QPoint lastMousePos; // 记录最后鼠标的位置
    int BORDER_WIDTH = 10; // 拖动边缘的宽度
};

#endif // MAP_H
