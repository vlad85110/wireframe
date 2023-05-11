//
// Created by Влад Кирилов on 24.04.2023.
//

#include <QLineF>
#include "Wireframe.h"
#include <QMatrix4x4>

Wireframe::Wireframe(const Vector<SplinePoint> &points, int m1, int m2, std::pair<float, float> dimensions) :
        m1(m1), m2(m2), dimension(2 * std::max(dimensions.first, dimensions.second)) {
    auto M = m1 + m1 * (m2 - 1);

    if (!points.empty()) {
        for (const auto &point: points) {
            for (int j = 0; j < M; ++j) {
                auto c = cos((double) j * 2 / M * M_PI);
                auto s = sin((double) j * 2 / M * M_PI);

                auto x = point.y() * c;
                auto y = point.x();
                auto z = point.y() * s;

                bool isVerticalLine = false;

                if (j % (M / m1) == 0) {
                    isVerticalLine = true;
                }

                this->originalPoints.emplace_back(x, y, z,
                                                  point.isSegmentEnd, isVerticalLine);

                this->handledPoints.emplace_back(x, y, z,
                                                 point.isSegmentEnd, isVerticalLine);
            }
        }
    }

    createLines();
}

const Vector<pair<QVector3D &, QVector3D &>> &Wireframe::getLines() const {
    return lines;
}

void Wireframe::handlePoints(double fiX, double fiY, double fiZ, double zn) {
    fiX = fiX * M_PI / 180;
    fiY = fiY * M_PI / 180;
    fiZ = fiZ * M_PI / 180;

    QMatrix4x4 matrixZ{
            (float) cos(fiX), (float) -sin(fiX), 0, 0,
            (float) sin(fiX), (float) cos(fiX), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };

    QMatrix4x4 matrixY{
            (float) cos(fiY), 0, (float) sin(fiY), 0,
            0, 1, 0, 0,
            (float) -sin(fiY), 0, (float) cos(fiY), 0,
            0, 0, 0, 1
    };

    QMatrix4x4 matrixX{
            1, 0, 0, 0,
            0, (float) cos(fiZ), (float) -sin(fiZ), 0,
            0, (float) sin(fiZ), (float) cos(fiZ), 0,
            0, 0, 0, 1
    };

    QMatrix4x4 proj{
            (float) (zn / dimension), 0, 0, 0,
            0, (float) (zn / dimension), 0, 0,
            0, 0, 0, 0,
            0, 0, 1, 0
    };

    QMatrix4x4 cam{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 10,
            0, 0, 0, 1
    };

    auto resMatrix = proj * cam * matrixX * matrixY * matrixZ;

    for (int i = 0; i < originalPoints.size(); ++i) {
        auto &originalPoint = originalPoints[i];
        auto &p = handledPoints[i];

        QVector4D vector{
                originalPoint.x(),
                originalPoint.y(),
                originalPoint.z(),
                1
        };

        auto result = resMatrix * vector;

        p.setX((float) result[0] / result[3]);
        p.setY((float) result[1] / result[3]);
        p.setZ((float) result[2] / result[3]);
    }
}

void Wireframe::createLines() {
    auto M = m1 + m1 * (m2 - 1);
    auto n = handledPoints.size() / M;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < M; ++j) {
            auto &point = handledPoints[i * M + j];

            if (point.isVerticalLine) {
                if (i != n - 1) {
                    auto &nextPointI = handledPoints[(i + 1) * M + j];
                    lines.emplace_back(point, nextPointI);
                }
            }

            if (point.isSegmentEnd) {
                if (j != M - 1) {
                    auto &nextPointJ = handledPoints[i * M + (j + 1)];
                    lines.emplace_back(point, nextPointJ);
                } else {
                    lines.emplace_back(point, handledPoints[i * M]);
                }
            }
        }
    }
}

float Wireframe::getDimension() const {
    return dimension;
}


