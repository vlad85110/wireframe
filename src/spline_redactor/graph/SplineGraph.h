//
// Created by Влад Кирилов on 16.04.2023.
//

#ifndef WIREFRAME_SPLINEGRAPH_H
#define WIREFRAME_SPLINEGRAPH_H


#include <QWidget>
#include "types.h"
#include "math/spline/Spline.h"
#include "Fwd.h"
#include <unordered_map>

class SplineGraph : public QWidget {
Q_OBJECT
private:
    SplineRedactor &redactor;

    int notchLen;

    QPoint lastMouseLocation;
    Qt::MouseButton mouseButton = Qt::RightButton;

    int centerX = 0;
    int centerY = 0;

    std::multimap<int, int> supportPointsCords;

    int findNearestPoint(int x, int y);

    void drawNotches(QPainter &painter);

    void drawAxes(QPainter &painter);

    void drawSupportPoints(QPainter &painter);

    void drawSpline(QPainter &painter);

    static inline bool isInPointCircle(int centerX, int centerY, int radius, int x, int y);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

public:
    SplineGraph(QWidget *parent, SplineRedactor &redactor);
};

#endif //WIREFRAME_SPLINEGRAPH_H
