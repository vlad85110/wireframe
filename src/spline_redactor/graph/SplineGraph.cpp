//
// Created by Влад Кирилов on 16.04.2023.
//

#include "SplineGraph.h"
#include <QPainter>
#include <QMouseEvent>
#include "spline_redactor/SplineRedactor.h"

SplineGraph::SplineGraph(QWidget *parent, SplineRedactor &redactor) :
        QWidget(parent), redactor(redactor), notchLen(8) {}

void SplineGraph::paintEvent(QPaintEvent *event) {
    centerX = width() / 2;
    centerY = height() / 2;

    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    QPen pen;
    pen.setColor(Qt::lightGray);
    painter.setPen(pen);

    drawAxes(painter);
    drawNotches(painter);

    pen.setWidth(2);
    pen.setColor(Qt::darkRed);
    painter.setPen(pen);

    if (redactor.isShowSupportPoints) {
        drawSupportPoints(painter);
    }

    pen.setColor(Qt::darkCyan);
    painter.setPen(pen);

    drawSpline(painter);

    painter.end();
}

void SplineGraph::mouseMoveEvent(QMouseEvent *event) {
    QWidget::mouseMoveEvent(event);

    if (!redactor.isShowSupportPoints) return;

    auto pos = event->pos();
    auto delta = pos - lastMouseLocation;

    if (mouseButton == Qt::LeftButton) {
        if (redactor.selectedPointIndex == -1) return;

        auto dx = (double) delta.x() / redactor.scale;
        auto dy = (double) -delta.y() / redactor.scale;
        if (dx == 0 && dy == 0) return;

        redactor.moveSelected((float) dx, (float) dy);
        lastMouseLocation = pos;
    }

    update();
}

void SplineGraph::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    auto x = event->pos().x();
    auto y = event->pos().y();

    if (!redactor.isShowSupportPoints) return;

    if (event->button() & Qt::LeftButton) {
        mouseButton = Qt::LeftButton;
        auto pointIndex = findNearestPoint(x, y);
        redactor.setSelectedPointIndex(pointIndex, true);
        update();
    }

    lastMouseLocation = event->pos();
}

void SplineGraph::wheelEvent(QWheelEvent *event) {
    QWidget::wheelEvent(event);
    redactor.changeScale((int) (0.5 * event->angleDelta().y()));
    update();
}

void SplineGraph::drawNotches(QPainter &painter) {
    auto scale = redactor.scale;

    for (int x = centerX + scale; x < width(); x += scale) {
        painter.drawLine(x, centerY - notchLen / 2, x, centerY + notchLen / 2);
        painter.drawLine(width() - x, centerY - notchLen / 2, width() - x, centerY + notchLen / 2);
    }

    for (int y = centerY + scale; y < height(); y += scale) {
        painter.drawLine(centerX - notchLen / 2, y, centerX + notchLen / 2, y);
        painter.drawLine(centerX - notchLen / 2, height() - y, centerX + notchLen / 2, height() - y);
    }
}

void SplineGraph::drawAxes(QPainter &painter) {
    painter.drawLine(0, centerY, width(), centerY);
    painter.drawLine(centerX, 0, centerX, height());
}

void SplineGraph::drawSupportPoints(QPainter &painter) {
    auto supportPoints = redactor.spline.getSupportPoints();
    auto scale = redactor.scale;

    supportPointsCords.clear();

    if (!supportPoints.empty()) {
        if (supportPoints.size() == 1) {
            auto first = supportPoints[0];
            auto x = (double) first.x() * scale + centerX;
            auto y = centerY - (double) first.y() * scale;
            supportPointsCords.emplace(x, 0);

            if (redactor.selectedPointIndex == 0) {
                QPen pen;
                pen.setColor(Qt::blue);
                painter.setPen(pen);
            }

            painter.drawEllipse(QPointF(x, y), 6, 6);

            QPen pen;
            pen.setColor(Qt::darkRed);
            painter.setPen(pen);

            return;
        }

        for (auto it = supportPoints.begin(); it < supportPoints.end() - 1; ++it) {
            auto x = (double) it->x() * scale + centerX;
            auto y = centerY - (double) it->y() * scale;

            auto nextX = (double) (it + 1)->x() * scale + centerX;
            auto nextY = centerY - (double) (it + 1)->y() * scale;

            supportPointsCords.emplace(x, it - supportPoints.begin());

            if (redactor.selectedPointIndex == it - supportPoints.begin()) {
                QPen pen;
                pen.setColor(Qt::blue);
                painter.setPen(pen);
            }

            painter.drawEllipse(QPointF(x, y), 6, 6);

            QPen pen;
            pen.setColor(Qt::darkRed);
            painter.setPen(pen);

            painter.drawEllipse(QPointF((x + nextX) / 2, (y + nextY) / 2), 3, 3);
            painter.drawLine((int) x, (int) y, (int) nextX, (int) nextY);

            if (it == supportPoints.end() - 2) {
                if (redactor.selectedPointIndex == supportPoints.size() - 1) {
                    pen.setColor(Qt::blue);
                    painter.setPen(pen);
                }

                painter.drawEllipse(QPointF(nextX, nextY), 6, 6);

                pen.setColor(Qt::darkRed);
                painter.setPen(pen);

                supportPointsCords.emplace(nextX, it - supportPoints.begin() + 1);
            }
        }
    }
}

void SplineGraph::drawSpline(QPainter &painter) {
    auto scale = redactor.scale;

    auto splinePoints = redactor.spline.getSplinePoints();

    if (!splinePoints.empty()) {
        for (auto it = splinePoints.begin(); it < splinePoints.end() - 1; ++it) {
            auto x = round((double) it->x() * scale + centerX);
            auto y = round(centerY - (double) it->y() * scale);

            auto nextX = round((double) (it + 1)->x() * scale + centerX);
            auto nextY = round(centerY - (double) (it + 1)->y() * scale);

            if (it - splinePoints.begin() == 10 || it - splinePoints.begin() == 11) {
            }

            painter.drawLine((int) x, (int) y, (int) nextX, (int) nextY);
        }
    }
}

int SplineGraph::findNearestPoint(int x, int y) {
    if (supportPointsCords.empty()) return -1;

    auto scale = redactor.scale;
    auto &spline = redactor.spline;

    auto right = supportPointsCords.lower_bound(x);

    if (right == supportPointsCords.end()) {
        right--;

        auto point = spline.getSupportPoints().at(right->second);
        auto pointX = (double) point.x() * scale + centerX;
        auto pointY = centerY - (double) point.y() * scale;

        if (isInPointCircle((int) pointX, (int) pointY, 6, x, y)) {
            return right->second;
        } else return -1;

    } else if (right == supportPointsCords.begin()) {
        auto point = spline.getSupportPoints().at(right->second);
        auto pointX = (double) point.x() * scale + centerX;
        auto pointY = centerY - (double) point.y() * scale;

        if (isInPointCircle((int) pointX, (int) pointY, 6, x, y)) {
            return right->second;
        } else return -1;
    } else {
        auto next = right;

        while (next != supportPointsCords.end() && next->first == right->first) {
            auto point = spline.getSupportPoints().at(next->second);
            auto pointX = (double) point.x() * scale + centerX;
            auto pointY = centerY - (double) point.y() * scale;

            if (isInPointCircle((int) pointX, (int) pointY, 6, x, y)) {
                return next->second;
            }

            next++;
        }

        auto left = right;
        left--;
        auto prev = left;

        if (prev == supportPointsCords.begin()) {
            auto point = spline.getSupportPoints().at(prev->second);
            auto pointX = (double) point.x() * scale + centerX;
            auto pointY = centerY - (double) point.y() * scale;

            if (isInPointCircle((int) pointX, (int) pointY, 6, x, y)) {
                return prev->second;
            } else {
                return -1;
            }
        }

        while (prev != supportPointsCords.begin() && prev->first == left->first) {
            auto point = spline.getSupportPoints().at(prev->second);
            auto pointX = (double) point.x() * scale + centerX;
            auto pointY = centerY - (double) point.y() * scale;

            if (isInPointCircle((int) pointX, (int) pointY, 6, x, y)) {
                return prev->second;
            }

            prev--;

            if (prev == supportPointsCords.begin()) {
                point = spline.getSupportPoints().at(prev->second);
                pointX = (double) point.x() * scale + centerX;
                pointY = centerY - (double) point.y() * scale;

                if (isInPointCircle((int) pointX, (int) pointY, 6, x, y)) {
                    return prev->second;
                } else {
                    return -1;
                }
            }
        }
    }

    return -1;
}

bool SplineGraph::isInPointCircle(int centerX, int centerY, int radius, int x, int y) {
    if (abs(x - centerX) > radius || abs(y - centerY) > radius) {
        return false;
    }

    return true;
}
