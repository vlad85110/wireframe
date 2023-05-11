//
// Created by Влад Кирилов on 16.04.2023.
//

#ifndef WIREFRAME_SPLINEFORM_H
#define WIREFRAME_SPLINEFORM_H

#include "Fwd.h"

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>

class SplineForm : public QWidget {
Q_OBJECT
private:
    SplineRedactor &redactor;
    QSpinBox n, m1, m2, k, currentPoint;
    QDoubleSpinBox currentX, currentY;

public:
    explicit SplineForm(QWidget *parent, SplineRedactor &redactor);

public slots:

    void currentPointMoved();

    void currentPointChanged();

    void pointDeleted();

    void pointAdded();
};


#endif //WIREFRAME_SPLINEFORM_H
