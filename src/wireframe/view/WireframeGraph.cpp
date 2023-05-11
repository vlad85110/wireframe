//
// Created by Влад Кирилов on 04.05.2023.
//

#include "WireframeGraph.h"

#include <QPainter>
#include <QMouseEvent>
#include "wireframe/WireframeRedactor.h"

WireframeGraph::WireframeGraph(WireframeRedactor &redactor) : QWidget(&redactor), redactor(redactor) {}

void WireframeGraph::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.fillRect(rect(), Qt::black);

    auto &wireframe = redactor.wireframe;

    if (wireframe != nullptr) {
        wireframe->handlePoints(redactor.fiX + redactor.prevFiX, redactor.fiY + redactor.prevFiY,
                                redactor.fiZ + redactor.prevFiZ, redactor.zn);
        auto &lines = wireframe->getLines();

        QPen pen;
        pen.setColor(QColor(245, 71, 195));
        painter.setPen(pen);

        auto centerX = width() / 2;
        auto centerY = height() / 2;

        auto scale = (double)std::min(QWidget::width(), QWidget::height()) * redactor.wireframe->getDimension();

        if (!lines.empty()) {
            for (auto &line: lines) {
                auto x1 = line.first.x() * scale + centerX;
                auto x2 = line.second.x() * scale + centerX;

                auto y1 = centerY - line.first.y() * scale;
                auto y2 = centerY - line.second.y() * scale;

                painter.drawLine((int) x1, (int) y1, (int) x2, (int) y2);
            }
        }
    }

    painter.end();
}

void WireframeGraph::mousePressEvent(QMouseEvent *event) {
    redactor.lastMouseLocation = event->pos();
}

void WireframeGraph::mouseReleaseEvent(QMouseEvent *event) {
    redactor.prevFiY += redactor.fiY;
    redactor.prevFiZ += redactor.fiZ;
    redactor.prevFiX += redactor.fiX;

    if (redactor.prevFiX > 360) redactor.prevFiX -= 360;
    if (redactor.prevFiY > 360) redactor.prevFiY -= 360;
    if (redactor.prevFiZ > 360) redactor.prevFiZ -= 360;

    if (redactor.prevFiX < -360) redactor.prevFiX += 360;
    if (redactor.prevFiY < -360) redactor.prevFiY += 360;
    if (redactor.prevFiZ < -360) redactor.prevFiZ += 360;

    redactor.fiX = 0;
    redactor.fiY = 0;
    redactor.fiZ = 0;
}

void WireframeGraph::mouseMoveEvent(QMouseEvent *event) {
    auto pos = event->pos();
    auto delta = pos - redactor.lastMouseLocation;

    redactor.fiZ = -0.4 * delta.y();
    redactor.fiY = 0.4 * delta.x();
    redactor.fiX = -0.05 * (delta.x() + delta.y());

    update();
}

void WireframeGraph::wheelEvent(QWheelEvent *event) {
    QWidget::wheelEvent(event);
    redactor.zn += (0.05 * event->angleDelta().y());
    redactor.zn = qBound(1., redactor.zn, 10.);

    update();
}
