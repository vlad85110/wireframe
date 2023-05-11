//
// Created by Влад Кирилов on 03.04.2023.
//

#ifndef FILTERS_OPENFILEACTION_H
#define FILTERS_OPENFILEACTION_H

#include "ui/toolbar/action/ToolBarAction.h"
#include "ui/toolbar/action/WireframeAction.h"

class OpenFileAction : public WireframeAction {
public:
    OpenFileAction(const QString &iconPath, const QString &name, WireframeRedactor &wireframe);

    void onMouseClicked() override;

};


#endif //FILTERS_OPENFILEACTION_H
