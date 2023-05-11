//
// Created by Влад Кирилов on 24.04.2023.
//

#include "WireframeRedactor.h"

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QDialogButtonBox>
#include "wireframe/view/WireframeGraph.h"

WireframeRedactor::WireframeRedactor(QWidget *parent) :
        QWidget(parent), fiX(0), fiY(0), fiZ(0), prevFiX(0), prevFiY(0), prevFiZ(0) {

    redactor = std::make_shared<SplineRedactor>();
    graph = std::make_shared<WireframeGraph>(*this);

    redactor->addPoint({-4.1, 1});
    redactor->addPoint({-4, 0.5});
    redactor->addPoint({-4, 0});
    redactor->addPoint({-2, 0});
    redactor->addPoint({-1, 0});
    redactor->addPoint({0, 1});
    redactor->addPoint({3, .75});
    redactor->addPoint({4, .5});

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(graph.get());
}

void WireframeRedactor::showRedactor() {
    QDialog dialog;

    dialog.setMinimumSize(640, 480);
    auto layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    buttonBox->setCenterButtons(true);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);

    layout->addWidget(redactor.get());
    layout->addWidget(buttonBox);
    dialog.setLayout(layout);

    auto res = dialog.exec();

    if (res == QDialog::Accepted) {
        createWireframe();
    }

    redactor->setParent(nullptr);
}


void WireframeRedactor::resetAngles() {
    prevFiY = 0;
    prevFiZ = 0;
    prevFiX = 0;

    update();
}

double WireframeRedactor::getPrevFiX() const {
    return prevFiX;
}

double WireframeRedactor::getPrevFiY() const {
    return prevFiY;
}

double WireframeRedactor::getPrevFiZ() const {
    return prevFiZ;
}

double WireframeRedactor::getZn() const {
    return zn;
}

const SplineRedactor &WireframeRedactor::getRedactor() const {
    return *redactor;
}

void WireframeRedactor::setPrevFiX(double prevFiX) {
    WireframeRedactor::prevFiX = prevFiX;
}

void WireframeRedactor::setZn(double zn) {
    WireframeRedactor::zn = zn;
}

void WireframeRedactor::setPrevFiY(double prevFiY) {
    WireframeRedactor::prevFiY = prevFiY;
}

void WireframeRedactor::setPrevFiZ(double prevFiZ) {
    WireframeRedactor::prevFiZ = prevFiZ;
}

void WireframeRedactor::setSupportPoints(const Vector<QVector2D> &supportPoints) {
    redactor->setSupportPoints(supportPoints);
}

void WireframeRedactor::setN(int n) {
    redactor->setN(n);
}

void WireframeRedactor::setM1(int m1) {
    redactor->setM1(m1);
}

void WireframeRedactor::setM2(int m2) {
    redactor->setM2(m2);
}

void WireframeRedactor::createWireframe() {
    wireframe = std::make_shared<Wireframe>(redactor->getSplinePoints(), redactor->getM1(),
                                            redactor->getM2(), redactor->getDimensions());
}