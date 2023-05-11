//
// Created by Влад Кирилов on 04.04.2023.
//

#include "AboutAction.h"

#include <fstream>
#include<sstream>
#include <iostream>
#include <QDialog>
#include <QMessageBox>

AboutAction::AboutAction(const QString &iconPath, const QString &name)
        : ToolBarAction(iconPath, name) {

    std::ifstream file;
    file.open("/Users/vladkirilov/CLionProjects/filters/src/ui/button/about/about");

    if (!file) {
        std::cerr << "fail opening about file";
        return;
    }

    std::ostringstream ss;

    ss << file.rdbuf();
    this->text = ss.str();

    file.close();
}

void AboutAction::onMouseClicked() {
    QMessageBox::information(nullptr, "about", QString::fromStdString(text));
}
