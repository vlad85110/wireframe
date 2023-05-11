//
// Created by Влад Кирилов on 17.04.2023.
//

#ifndef WIREFRAME_SPLINEPOINT_H
#define WIREFRAME_SPLINEPOINT_H

#include <QVector2D>

struct SplinePoint : public QVector2D {
    bool isSegmentEnd;

    SplinePoint(float xpos, float ypos, bool isSegmentEnd);
};


#endif //WIREFRAME_SPLINEPOINT_H
