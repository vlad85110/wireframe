//
// Created by Влад Кирилов on 16.04.2023.
//

#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include "spline_redactor/SplineRedactor.h"
#include "SplineForm.h"

SplineForm::SplineForm(QWidget *parent, SplineRedactor &redactor) : QWidget(parent), redactor(redactor) {
    n.setMinimum(1);
    n.setMaximum(30);

    m1.setMinimum(2);
    m1.setMaximum(30);

    m2.setMinimum(1);
    m2.setMaximum(30);

    n.setValue(redactor.getN());
    m1.setValue(redactor.m1);
    m2.setValue(redactor.m2);

    auto label1 = new QLabel("Point number:");
    label1->setAlignment(Qt::AlignRight);
    auto label2 = new QLabel("x:");
    label2->setAlignment(Qt::AlignRight);
    auto label3 = new QLabel("y:");
    label3->setAlignment(Qt::AlignRight);

    auto *gridLayout = new QGridLayout();
    gridLayout->addWidget(label1, 0, 0);
    gridLayout->addWidget(&currentPoint, 0, 1);
    gridLayout->addWidget(label2, 1, 0);
    gridLayout->addWidget(&currentX, 1, 1);
    gridLayout->addWidget(label3, 2, 0);
    gridLayout->addWidget(&currentY, 2, 1);

    currentX.setMinimum(-100);
    currentX.setMaximum(100);

    currentY.setMinimum(-100);
    currentY.setMaximum(100);

    currentPoint.setMaximum(0);

    connect(&currentPoint, &QSpinBox::valueChanged, &redactor,
            &SplineRedactor::setSelectedPointIndexSlot);

    connect(&currentPoint, &QSpinBox::valueChanged, this,
            &SplineForm::currentPointMoved);

    connect(&currentX, &QDoubleSpinBox::valueChanged, &redactor,
            &SplineRedactor::setCurrentPointX);

    connect(&currentY, &QDoubleSpinBox::valueChanged, &redactor,
            &SplineRedactor::setCurrentPointY);

    auto label4 = new QLabel("n:");
    label4->setAlignment(Qt::AlignRight);
    auto label5 = new QLabel("M1:");
    label5->setAlignment(Qt::AlignRight);
    auto label6 = new QLabel("M2:");
    label6->setAlignment(Qt::AlignRight);

    gridLayout->addWidget(label4, 0, 2);
    gridLayout->addWidget(&n, 0, 3);
    gridLayout->addWidget(label5, 1, 2);
    gridLayout->addWidget(&m1, 1, 3);
    gridLayout->addWidget(label6, 2, 2);
    gridLayout->addWidget(&m2, 2, 3);

    connect(&m1, &QSpinBox::valueChanged, &redactor,
            &SplineRedactor::setM1);

    connect(&m2, &QSpinBox::valueChanged, &redactor,
            &SplineRedactor::setM2);

    connect(&n, &QSpinBox::valueChanged, &redactor,
            &SplineRedactor::setN);

    auto autoScaleLabel = new QLabel("Auto scale :");

    auto showSupportPointsLabel = new QLabel("Show support points :");
    auto showSupportPoints = new QCheckBox();

    connect(showSupportPoints, &QCheckBox::stateChanged, &redactor,
            &SplineRedactor::setShowSupportPoints);

    showSupportPoints->setCheckState(Qt::Checked);

    autoScaleLabel->setAlignment(Qt::AlignRight);
    showSupportPointsLabel->setAlignment(Qt::AlignRight);

    gridLayout->addWidget(showSupportPointsLabel, 3, 0);
    gridLayout->addWidget(showSupportPoints, 3, 1);

    auto add = new QPushButton("add");
    auto del = new QPushButton("delete");

    connect(add, &QPushButton::clicked, &redactor, &SplineRedactor::addSupportPoint);
    connect(add, &QPushButton::clicked, this, &SplineForm::pointAdded);

    connect(del, &QPushButton::clicked, &redactor, &SplineRedactor::deleteSupportPoint);
    connect(del, &QPushButton::clicked, this, &SplineForm::pointDeleted);

    auto apply = new QPushButton("apply");

    auto zoomIn = new QPushButton("zoom in");
    auto zoomOut = new QPushButton("zoom out");

    connect(zoomIn, &QPushButton::clicked, &redactor, &SplineRedactor::zoomIn);
    connect(zoomOut, &QPushButton::clicked, &redactor, &SplineRedactor::zoomOut);

    add->setMaximumWidth(80);
    del->setMaximumWidth(80);
    apply->setMaximumWidth(80);
    zoomIn->setMaximumWidth(80);
    zoomOut->setMaximumWidth(80);

    gridLayout->addWidget(apply, 4, 1);

    gridLayout->addWidget(add, 4, 2);
    gridLayout->addWidget(del, 4, 3);

    gridLayout->addWidget(zoomIn, 4, 4);
    gridLayout->addWidget(zoomOut, 4, 5);

    setLayout(gridLayout);
}

void SplineForm::currentPointChanged() {
    currentPoint.setValue(redactor.selectedPointIndex + 1);
}

void SplineForm::currentPointMoved() {
    auto selectedPointIndex = redactor.selectedPointIndex;

    if (selectedPointIndex == -1) {
        currentX.setValue(0);
        currentY.setValue(0);
        return;
    }

    auto currenPoint = redactor.spline.getSupportPoints().at(selectedPointIndex);

    currentX.setValue(currenPoint.x());
    currentY.setValue(currenPoint.y());
}

void SplineForm::pointDeleted() {
    auto selectedPointIndex = redactor.selectedPointIndex;
    if (selectedPointIndex == redactor.spline.getSupportPoints().size()) {
        currentPoint.setValue(0);
        currentX.setValue(0);
        currentY.setValue(0);
    }

    currentPoint.setMaximum((int) redactor.spline.getSupportPoints().size());
}

void SplineForm::pointAdded() {
    currentPoint.setMaximum((int) redactor.spline.getSupportPoints().size());
}

