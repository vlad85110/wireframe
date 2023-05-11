//
// Created by Влад Кирилов on 02.05.2023.
//

#include "WireframePoint.h"

WireframePoint::WireframePoint(float xpos, float ypos, float zpos, bool isSegmentEnd, bool isVerticalLine)
        : QVector3D(xpos, ypos, zpos),
          isSegmentEnd(isSegmentEnd), isVerticalLine(isVerticalLine) {}
