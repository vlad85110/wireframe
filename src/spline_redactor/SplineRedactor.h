//
// Created by Влад Кирилов on 16.04.2023.
//

#ifndef WIREFRAME_SPLINEREDACTOR_H
#define WIREFRAME_SPLINEREDACTOR_H

#include "Fwd.h"
#include <QWindow>
#include <QVBoxLayout>
#include <QWidget>
#include "types.h"
#include "Fwd.h"
#include "math/spline/Spline.h"
#include "spline_redactor/graph/SplineGraph.h"
#include "spline_redactor/form//SplineForm.h"

class SplineRedactor : public QWidget {
Q_OBJECT
private:
    Spline spline;
    std::shared_ptr<SplineForm> form;
    std::shared_ptr<SplineGraph> graph;

    int selectedPointIndex = -1;
    int scale;
    int m1, m2;

    bool isShowSupportPoints = true;

public:
    explicit SplineRedactor();

    friend class SplineGraph;

    friend class SplineForm;

    void moveSelected(float dx, float dy);

    void setSelectedPointIndex(int index, bool withZero);

    const Vector<SplinePoint> &getSplinePoints();

    void setSupportPoints(const Vector<QVector2D> &supportPoints);

    void addPoint(QVector2D point);

    void changeScale(int add);

    [[nodiscard]] int getM1() const;

    [[nodiscard]] int getM2() const;

    [[nodiscard]] int getN() const;

    [[nodiscard]] std::pair<float, float> getDimensions() const;

    [[nodiscard]] const Spline &getSpline() const;

public slots:

    void addSupportPoint();

    void deleteSupportPoint();

    void setShowSupportPoints(int arg);

    void setSelectedPointIndexSlot(int index);

    void setCurrentPointX(float x);

    void setCurrentPointY(float y);

    void zoomIn();

    void zoomOut();

    void setN(int n);

    void setM1(int m1);

    void setM2(int m2);

signals:

    void selectedPointMoved();

    void selectedPointChanged();
};


#endif //WIREFRAME_SPLINEREDACTOR_H
