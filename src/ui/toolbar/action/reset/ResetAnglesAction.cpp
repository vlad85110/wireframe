//
// Created by Влад Кирилов on 30.04.2023.
//

#include "ResetAnglesAction.h"

ResetAnglesAction::ResetAnglesAction(const QString &iconPath, const QString &name, WireframeRedactor &wireframe)
        : WireframeAction(iconPath, name, wireframe) {}

void ResetAnglesAction::onMouseClicked() {
    wireframe.resetAngles();
}
