//
// Created by Влад Кирилов on 30.04.2023.
//

#include "WireframeAction.h"

WireframeAction::WireframeAction(const QString &iconPath, const QString &name, WireframeRedactor &wireframe)
        : ToolBarAction(iconPath, name), wireframe(wireframe) {}
