//
// Created by Влад Кирилов on 04.05.2023.
//

#ifndef WIREFRAME_WIREFRAMEGRAPH_H
#define WIREFRAME_WIREFRAMEGRAPH_H

#include <QWidget>
#include "Fwd.h"


class WireframeGraph : public QWidget {
protected:
public:
    explicit WireframeGraph(WireframeRedactor &redactor);

protected:

    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    WireframeRedactor &redactor;


};


#endif //WIREFRAME_WIREFRAMEGRAPH_H
