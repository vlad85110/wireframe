//
// Created by Влад Кирилов on 24.04.2023.
//

#ifndef WIREFRAME_WIREFRAME_H
#define WIREFRAME_WIREFRAME_H

#include "types.h"
#include "math/spline/point/SplinePoint.h"
#include "math/wireframe/point/WireframePoint.h"
#include <QVector3D>

class Wireframe {
private:
    int m1, m2;
    float dimension;

    Vector<WireframePoint> originalPoints;
    Vector<WireframePoint> handledPoints;
    Vector<pair<QVector3D &, QVector3D &>> lines;

    void createLines();

public:
    explicit Wireframe(const Vector<SplinePoint> &points, int m1, int m2,
                       std::pair<float, float> dimensions);
    [[nodiscard]] const Vector<pair<QVector3D&, QVector3D&>>& getLines() const;
    void handlePoints(double fiX, double fiY, double fiZ, double zn);

    [[nodiscard]] float getDimension() const;
};


#endif //WIREFRAME_WIREFRAME_H
