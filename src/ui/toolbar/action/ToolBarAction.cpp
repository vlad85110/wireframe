//
// Created by Влад Кирилов on 15.03.2023.
//

#include "ToolBarAction.h"

#include <QIcon>
#include <iostream>
#include <QSignalMapper>

ToolBarAction::ToolBarAction(const QString &iconPath, const QString &name) : QAction(), name(name) {
    auto *icon = new QIcon(iconPath);
    setText(name);
    setIconVisibleInMenu(false);
    setIcon(*icon);
    setToolTip(name);

    connect(this, &QAction::triggered, this, &ToolBarAction::onTrigger);
}

void ToolBarAction::onTrigger() {
    onMouseClicked();
}

ToolBarAction::~ToolBarAction() = default;
