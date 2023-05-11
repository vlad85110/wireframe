//
// Created by Влад Кирилов on 17.04.2023.
//

#include "Spline.h"
#include <cmath>

Spline::Spline() : n(10) {
    M_s = QMatrix4x4{
            -1, 3, -3, 1,
            3, -6, 3, 0,
            -3, 0, 3, 0,
            1, 4, 1, 0
    } / 6;
}

void Spline::setN(int n) {
    Spline::n = n;
    isNeedUpdatePoints = true;
}

void Spline::addSupportPoint() {
    if (supportPoints.size() == maxSupportPointsSize) return;

    if (supportPoints.empty()) {
        supportPoints.emplace_back(0, 0);
        return;
    }

    auto &last = supportPoints[supportPoints.size() - 1];
    supportPoints.emplace_back(last.x() + 1, last.y());

    isNeedUpdatePoints = true;
}

void Spline::addSupportPoint(QVector2D point) {
    isNeedUpdatePoints = true;
    supportPoints.push_back(point);
}

void Spline::deletePoint() {
    isNeedUpdatePoints = true;
    if (!supportPoints.empty()) {
        supportPoints.pop_back();
    }
}

void Spline::fillPoints() {
    points.clear();

    auto k = supportPoints.size();
    if (k < 4) return;

    Vector<QVector2D> G{supportPoints[0], supportPoints[1], supportPoints[2], supportPoints[3]};

    for (int i = 0; i < k - 3; ++i) {
        auto dt = 1. / n;

        QVector4D G_x{G[0].x(), G[1].x(), G[2].x(), G[3].x()};
        QVector4D G_y{G[0].y(), G[1].y(), G[2].y(), G[3].y()};

        for (int j = 0; j <= n; ++j) {
            if (j == n && i != k - 4) break;

            auto t = dt * j;
            auto newPoint = getSplineValue(t, G_x, G_y);

            if (t == 0 || t == 1) {
                newPoint.isSegmentEnd = true;
            }

            points.push_back(newPoint);
        }

        G.erase(G.begin());
        G.emplace_back(supportPoints[i + 4].x(), supportPoints[i + 4].y());
    }
}

QVector4D Spline::T(double t) {
    return {(float) pow(t, 3), (float) pow(t, 2), (float) t, 1};
}

SplinePoint Spline::getSplineValue(double t, QVector4D &G_x, QVector4D &G_y) const {
    auto T = Spline::T(t);

    auto TM_s = T * M_s;

    auto x = QVector4D::dotProduct(TM_s, G_x);
    auto y = QVector4D::dotProduct(TM_s, G_y);

    return {x, y, false};
}

const Vector<SplinePoint> &Spline::getSplinePoints() {
    if (isNeedUpdatePoints) {
        fillPoints();
        isNeedUpdatePoints = false;
    }

    return points;
}

const Vector<QVector2D> &Spline::getSupportPoints() const {
    return supportPoints;
}

void Spline::movePoint(int i, float dx, float dy) {
    auto &oldPoint = supportPoints[i];
    auto newPoint = QVector2D(oldPoint.x() + dx, oldPoint.y() + dy);
    supportPoints[i] = newPoint;
    isNeedUpdatePoints = true;
}

void Spline::changePointX(int index, float x) {
    auto &oldPoint = supportPoints[index];
    auto newPont = QVector2D(x, oldPoint.y());
    supportPoints[index] = newPont;
    isNeedUpdatePoints = true;
}

void Spline::changePointY(int index, float y) {
    auto &oldPoint = supportPoints[index];
    auto newPont = QVector2D(oldPoint.x(), y);
    supportPoints[index] = newPont;
    isNeedUpdatePoints = true;
}

int Spline::getN() const {
    return n;
}

std::pair<float, float> Spline::getDimensions() const {
    auto maxX = -1.;
    auto maxY = -1.;

    for (auto &point: supportPoints) {
        if (abs(point.x()) > maxX) {
            maxX = abs(point.x());
        }

        if (abs(point.y()) > maxY) {
            maxY = abs(point.y());
        }
    }

    return std::pair<float, float>{maxX, maxY};
}

void Spline::setSupportPoints(const Vector<QVector2D> &supportPoints) {
    Spline::supportPoints = supportPoints;
    isNeedUpdatePoints = true;
}





