//
// Created by Влад Кирилов on 20.03.2023.
//

#include "MenuWidget.h"

MenuWidget::MenuWidget(const ToolbarWidget &widget) {
    auto fileMenu = new QMenu("File");

    fileMenu->addAction(widget.getOpenFileAction());
    fileMenu->addAction(widget.getSaveFileAction());

    auto helpMenu = new QMenu("Help");

    helpMenu->addAction(widget.getAboutAction());

    auto settingsMenu = new QMenu("Settings");
    settingsMenu->addAction(widget.getShowRedactorAction());
    settingsMenu->addAction(widget.getResetAnglesAction());

    addMenu(fileMenu);
    addMenu(settingsMenu);
    addMenu(helpMenu);
}
