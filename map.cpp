#include "map.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QResizeEvent>
#include <QCursor>

map::map(QWidget *parent) : QWidget(parent), currentPos(-1, -1), targetPos(-1, -1), resizing(false) {
    // 加载地图图像
    mapPixmap = QPixmap("E:/qtdocument/bjutmap.jpg");  // 请替换为实际的地图路径
    setMouseTracking(true);  // 开启鼠标追踪
}

// 捕捉鼠标点击事件
void map::mousePressEvent(QMouseEvent *event) {
    // 处理右键点击，清除所有标记和路
    if (event->button() == Qt::RightButton) {
        currentPos = QPoint(-1, -1);  // 重置起始点
        targetPos = QPoint(-1, -1);   // 重置目标点
        update();  // 重新绘制，清除所有标记和路径
        return;
    }

    // 如果鼠标点击在边缘，开始调整窗口大小
    if (event->pos().x() <= BORDER_WIDTH || event->pos().x() >= width() - BORDER_WIDTH ||
        event->pos().y() <= BORDER_WIDTH || event->pos().y() >= height() - BORDER_WIDTH) {
        resizing = true;
        lastMousePos = event->globalPos();
        return;
    }

    // 左键点击处理：如果不在边缘，正常处理地图点击
    if (event->button() == Qt::LeftButton) {
        if (currentPos == QPoint(-1, -1)) {
            currentPos = event->pos();  // 第一次点击设置为当前位置（红点）
        } else {
            targetPos = event->pos();   // 第二次点击设置为目标位置（绿点）
        }
        update();  // 每次点击后重新绘制
    }
}

// 鼠标移动事件，用于调整窗口大小
void map::mouseMoveEvent(QMouseEvent *event) {
    if (resizing) {
        // 计算鼠标移动的距离
        int dx = event->globalX() - lastMousePos.x();
        int dy = event->globalY() - lastMousePos.y();

        // 调整窗口的大小
        QSize newSize = size() + QSize(dx, dy);
        resize(newSize);

        // 更新最后鼠标的位置
        lastMousePos = event->globalPos();
        return;
    }

    // 更新鼠标光标样式以指示可调整窗口的边缘
    if (event->pos().x() <= BORDER_WIDTH || event->pos().x() >= width() - BORDER_WIDTH ||
        event->pos().y() <= BORDER_WIDTH || event->pos().y() >= height() - BORDER_WIDTH) {
        setCursor(Qt::SizeFDiagCursor);  // 设置拖动调整大小的光标
    } else {
        setCursor(Qt::ArrowCursor);  // 恢复普通光标
    }
}

// 鼠标释放事件
void map::mouseReleaseEvent(QMouseEvent *event) {
    if (resizing) {
        resizing = false;
        setCursor(Qt::ArrowCursor);  // 调整完大小后恢复光标
    }
}

// 处理窗口大小变化事件
void map::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    update();  // 触发窗口大小变化时的重绘
}

// 绘制地图和路径
void map::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // 将地图缩放到窗口大小
    QPixmap scaledMap = mapPixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaledMap);

    // 如果已设置当前位置，绘制当前位置的标记
    if (currentPos != QPoint(-1, -1)) {
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        painter.drawEllipse(currentPos, 10, 10);  // 绘制红色圆点表示当前位置
    }

    // 如果已设置目标位置，绘制目标位置的标记和路径
    if (targetPos != QPoint(-1, -1)) {
        painter.setPen(Qt::green);
        painter.setBrush(Qt::green);
        painter.drawEllipse(targetPos, 10, 10);  // 绘制绿色圆点表示目标位置

        // 绘制从当前位置到目标位置的路径
        painter.setPen(QPen(Qt::blue, 3));
        painter.drawLine(currentPos, targetPos);
    }
}
