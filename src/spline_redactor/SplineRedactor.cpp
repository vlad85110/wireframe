//
// Created by Влад Кирилов on 16.04.2023.
//

#include "SplineRedactor.h"

#include <QDialog>

SplineRedactor::SplineRedactor() :
        scale(40), m1(10), m2(20) {

    graph = std::make_shared<SplineGraph>(this, *this);
    form = std::make_shared<SplineForm>(this, *this);

    auto layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(graph.get(), 9);
    layout->addWidget(form.get(), 1);

    connect(this, &SplineRedactor::selectedPointMoved,
            form.get(), &SplineForm::currentPointMoved);

    connect(this, &SplineRedactor::selectedPointChanged,
            form.get(), &SplineForm::currentPointChanged);

    setLayout(layout);
}

void SplineRedactor::addSupportPoint() {
    spline.addSupportPoint();
    graph->update();
}

void SplineRedactor::deleteSupportPoint() {
    spline.deletePoint();
    graph->update();
}

void SplineRedactor::setShowSupportPoints(int arg) {
    isShowSupportPoints = arg > 0;
    graph->update();
}

void SplineRedactor::zoomIn() {
    changeScale(10);
    graph->update();
}

void SplineRedactor::zoomOut() {
    changeScale(-10);
    graph->update();
}

void SplineRedactor::changeScale(int add) {
    scale += add;
    scale = qBound(10, scale, 100);
}

void SplineRedactor::setSelectedPointIndex(int index, bool withZero) {

    if (!withZero) {
        selectedPointIndex = index - 1;
    } else {
        selectedPointIndex = index;
        emit selectedPointChanged();
    }

    graph->update();
}

void SplineRedactor::setCurrentPointX(float x) {
    spline.changePointX(selectedPointIndex, x);
    graph->update();
}

void SplineRedactor::setCurrentPointY(float y) {
    spline.changePointY(selectedPointIndex, y);
    graph->update();
}

void SplineRedactor::moveSelected(float dx, float dy) {
    spline.movePoint(selectedPointIndex, dx, dy);
    emit selectedPointMoved();
}

void SplineRedactor::setSelectedPointIndexSlot(int index) {
    setSelectedPointIndex(index, false);
}

void SplineRedactor::setN(int newN) {
    spline.setN(newN);
    graph->update();
}

void SplineRedactor::setM1(int newM1) {
    SplineRedactor::m1 = newM1;
}

void SplineRedactor::setM2(int newM2) {
    SplineRedactor::m2 = newM2;
}

int SplineRedactor::getN() const {
    return spline.getN();
}

int SplineRedactor::getM1() const {
    return m1;
}

int SplineRedactor::getM2() const {
    return m2;
}

const Vector<SplinePoint> &SplineRedactor::getSplinePoints() {
    return spline.getSplinePoints();
}

void SplineRedactor::addPoint(QVector2D point) {
    spline.addSupportPoint(point);
}

std::pair<float, float> SplineRedactor::getDimensions() const {
    return spline.getDimensions();
}

const Spline &SplineRedactor::getSpline() const {
    return spline;
}

void SplineRedactor::setSupportPoints(const Vector<QVector2D> &supportPoints) {
    spline.setSupportPoints(supportPoints);
}

