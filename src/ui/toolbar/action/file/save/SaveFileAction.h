//
// Created by Влад Кирилов on 03.04.2023.
//

#ifndef FILTERS_SAVEFILEACTION_H
#define FILTERS_SAVEFILEACTION_H

#include "ui/toolbar/action/ToolBarAction.h"
#include "ui/toolbar/action/WireframeAction.h"

class SaveFileAction : public WireframeAction {
public:
    SaveFileAction(const QString &iconPath, const QString &name, WireframeRedactor &wireframe);

    void onMouseClicked() override;
};


#endif //FILTERS_SAVEFILEACTION_H
