//
// Created by Влад Кирилов on 24.04.2023.
//

#include "ShowRedactorAction.h"


void ShowRedactorAction::onMouseClicked() {
    wireframe.showRedactor();
}

ShowRedactorAction::ShowRedactorAction(const QString &iconPath, const QString &name, WireframeRedactor &wireframe)
        : WireframeAction(iconPath, name, wireframe) {}
