//
// Created by Влад Кирилов on 17.04.2023.
//

#include "SplinePoint.h"

SplinePoint::SplinePoint(float xpos, float ypos, bool isSegmentEnd) :
        QVector2D(xpos, ypos), isSegmentEnd(isSegmentEnd) {}
