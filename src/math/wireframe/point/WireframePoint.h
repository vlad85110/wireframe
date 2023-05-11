//
// Created by Влад Кирилов on 02.05.2023.
//

#ifndef WIREFRAME_WIREFRAMEPOINT_H
#define WIREFRAME_WIREFRAMEPOINT_H

#include <QVector3D>

struct WireframePoint : public QVector3D {
    WireframePoint(float xpos, float ypos, float zpos, bool isSegmentEnd, bool isVerticalLine);
    bool isVerticalLine;
    bool isSegmentEnd;
};


#endif //WIREFRAME_WIREFRAMEPOINT_H
