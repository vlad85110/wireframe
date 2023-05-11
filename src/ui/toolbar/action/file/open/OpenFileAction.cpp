//
// Created by Влад Кирилов on 03.04.2023.
//

#include <iostream>
#include <QFileDialog>
#include "OpenFileAction.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "math/spline/point/SplinePoint.h"
#include <QMessageBox>


OpenFileAction::OpenFileAction(const QString &iconPath, const QString &name, WireframeRedactor &wireframe) :
        WireframeAction(iconPath, name, wireframe) {}

void OpenFileAction::onMouseClicked() {
    auto name = QFileDialog::getOpenFileName(nullptr, tr("Open scene"),
                                             QString(),
                                             tr("WIRF Files (*.wirf)"));
    if (name.isEmpty()) return;

    QFile file(name);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QByteArray jsonData = file.readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);

    if (jsonDoc.isNull()) {
        QMessageBox::warning(&wireframe, "warning", "Ошибка чтения JSON");
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    if (!jsonObj.contains("wireframe") || !jsonObj.contains("spline")) {
        QMessageBox::warning(&wireframe, "warning", "Ошибка чтения файла");
        return;
    }

    auto wireframeJson = jsonObj["wireframe"].toObject();
    auto splineJson = jsonObj["spline"].toObject();

    if (!splineJson.contains("n") || !splineJson.contains("m1") || !splineJson.contains("m2")) {
        QMessageBox::warning(&wireframe, "warning", "Ошибка чтения файла");
        return;
    }

    auto nRef = splineJson["n"];
    auto m1Ref = splineJson["m1"];
    auto m2Ref = splineJson["m2"];

    if (!nRef.isDouble() || !m1Ref.isDouble() || !m2Ref.isDouble()) {
        QMessageBox::warning(&wireframe, "warning", "Ошибка чтения файла");
        return;
    }

    auto n = nRef.toInt();
    auto m1 = m1Ref.toInt();
    auto m2 = m2Ref.toInt();

    if (!splineJson.contains("points")) {
        QMessageBox::warning(&wireframe, "warning", "Ошибка чтения файла");
        return;
    }

    auto splinePointsArrayRef = splineJson["points"];

    if (!splinePointsArrayRef.isArray()) {
        QMessageBox::warning(&wireframe, "warning", "Ошибка чтения файла");
        return;
    }

    auto splinePointsArray = splinePointsArrayRef.toArray();

    Vector<QVector2D> points;

    for (auto pointJson: splinePointsArray) {
        if (!pointJson.isObject()) {
            QMessageBox::warning(&wireframe, "warning", "Ошибка чтения файла");
            return;
        }

        auto pointJsonObj = pointJson.toObject();

        if (!pointJsonObj.contains("x") || !pointJsonObj.contains("y")) {
            QMessageBox::warning(&wireframe, "warning", "Ошибка чтения файла");
            return;
        }

        auto xRef = pointJsonObj["x"];
        auto yRef = pointJsonObj["y"];

        if (!xRef.isDouble() || !yRef.isDouble()) {
            QMessageBox::warning(&wireframe, "warning", "Ошибка чтения файла");
            return;
        }

        auto x = xRef.toDouble();
        auto y = yRef.toDouble();

        points.emplace_back(x, y);
    }

    if (!wireframeJson.contains("x") || !wireframeJson.contains("y")
        || !wireframeJson.contains("z") || !wireframeJson.contains("zn")) {

        QMessageBox::warning(&wireframe, "warning", "Ошибка чтения файла");
        return;
    }

    auto xRef = wireframeJson["x"];
    auto yRef = wireframeJson["y"];
    auto zRef = wireframeJson["z"];
    auto znRef = wireframeJson["zn"];

    if (!xRef.isDouble() || !yRef.isDouble() || !zRef.isDouble() || !znRef.isDouble()) {
        QMessageBox::warning(&wireframe, "warning", "Ошибка чтения файла");
        return;
    }

    auto x = xRef.toDouble();
    auto y = xRef.toDouble();
    auto z = zRef.toDouble();
    auto zn = znRef.toDouble();

    wireframe.setPrevFiX(x);
    wireframe.setPrevFiY(y);
    wireframe.setPrevFiZ(z);
    wireframe.setZn(zn);

    wireframe.setN(n);
    wireframe.setM1(m1);
    wireframe.setM2(m2);
    wireframe.setSupportPoints(points);

    wireframe.createWireframe();
    wireframe.update();

    file.close();
}


