//
// Created by Влад Кирилов on 24.04.2023.
//

#ifndef WIREFRAME_WIREFRAMEREDACTOR_H
#define WIREFRAME_WIREFRAMEREDACTOR_H

#include <QWidget>
#include "types.h"
#include "math/wireframe/Wireframe.h"
#include "spline_redactor/SplineRedactor.h"

#include "Fwd.h"

class WireframeRedactor : public QWidget {
Q_OBJECT

private:
    double fiX, fiY, fiZ, prevFiX, prevFiY, prevFiZ;
    double zn = 1.8;

    std::shared_ptr<Wireframe> wireframe;
    std::shared_ptr<SplineRedactor> redactor;
    std::shared_ptr<WireframeGraph> graph;

    QPoint lastMouseLocation;

public:
    explicit WireframeRedactor(QWidget *parent);

    friend class WireframeGraph;

    [[nodiscard]] double getPrevFiX() const;

    [[nodiscard]] double getPrevFiY() const;

    [[nodiscard]] double getPrevFiZ() const;

    [[nodiscard]] double getZn() const;

    void setPrevFiX(double prevFiX);

    void setPrevFiY(double prevFiY);

    void setPrevFiZ(double prevFiZ);

    void setZn(double zn);

    void setSupportPoints(const Vector<QVector2D> &supportPoints);

    void setN(int n);

    void setM1(int m1);

    void setM2(int m2);

    void createWireframe();

public slots:

    void showRedactor();

    void resetAngles();

    [[nodiscard]] const SplineRedactor &getRedactor() const;
};


#endif //WIREFRAME_WIREFRAMEREDACTOR_H
