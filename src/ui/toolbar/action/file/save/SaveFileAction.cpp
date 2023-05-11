//
// Created by Влад Кирилов on 03.04.2023.
//

#include <QFileDialog>
#include "SaveFileAction.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

SaveFileAction::SaveFileAction(const QString &iconPath, const QString &name, WireframeRedactor &wireframe)
        : WireframeAction(iconPath, name, wireframe) {}

void SaveFileAction::onMouseClicked() {
    auto name = QFileDialog::getSaveFileName(nullptr, tr("Save scene"),
                                             QString("Wireframe Files (*.wirf)"));
    if (name.isEmpty()) return;


    QFileInfo fileInfo(name);
    if (fileInfo.suffix().isEmpty()) {
        name += ".wirf";
    }

    QJsonObject jsonObject;
    QJsonObject wireframeJson;

    wireframeJson["x"] = wireframe.getPrevFiX();
    wireframeJson["y"] = wireframe.getPrevFiY();
    wireframeJson["z"] = wireframe.getPrevFiZ();
    wireframeJson["zn"] = wireframe.getZn();
    jsonObject["wireframe"] = wireframeJson;

    auto &redactor = wireframe.getRedactor();

    QJsonObject splineJson;
    splineJson["n"] = redactor.getN();
    splineJson["m1"] = redactor.getM1();
    splineJson["m2"] = redactor.getM2();

    QJsonArray pointsArray;
    auto &points = redactor.getSpline().getSupportPoints();

    for (auto &point: points) {
        QJsonObject pointJson;
        pointJson["x"] = point.x();
        pointJson["y"] = point.y();
        pointsArray.append(pointJson);
    }

    splineJson["points"] = pointsArray;
    jsonObject["spline"] = splineJson;

    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Indented);

    QFile saveFile(name);
    if (saveFile.open(QIODevice::WriteOnly)) {
        saveFile.write(jsonData);
        saveFile.close();
    }

    saveFile.close();
}

