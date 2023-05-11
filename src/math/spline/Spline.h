//
// Created by Влад Кирилов on 17.04.2023.
//

#ifndef WIREFRAME_SPLINE_H
#define WIREFRAME_SPLINE_H

#include <QPoint>
#include <QVector4D>
#include <QMatrix4x4>
#include "types.h"
#include "math/spline/point/SplinePoint.h"

using std::array;

class Spline {
private:
    const int maxSupportPointsSize = 50;

    QMatrix4x4 M_s;
    Vector<QVector2D> supportPoints;
    Vector<SplinePoint> points;

    int n;

    static QVector4D T(double t);

    [[nodiscard]] SplinePoint getSplineValue(double t, QVector4D &G_x, QVector4D &G_y) const;

    void fillPoints();

    bool isNeedUpdatePoints = false;
public:
    Spline();

    void addSupportPoint();

    [[maybe_unused]] void addSupportPoint(QVector2D point);

    void deletePoint();

    void setSupportPoints(const Vector<QVector2D> &supportPoints);

    void movePoint(int i, float dx, float dy);

    void changePointX(int index, float x);

    void changePointY(int index, float y);

    void setN(int n);

    [[nodiscard]] int getN() const;

    [[nodiscard]] std::pair<float, float> getDimensions() const;

    [[nodiscard]] const Vector<SplinePoint> &getSplinePoints();

    [[nodiscard]] const Vector<QVector2D> &getSupportPoints() const;
};


#endif //WIREFRAME_SPLINE_H
