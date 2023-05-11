//
// Created by Влад Кирилов on 30.04.2023.
//

#ifndef WIREFRAME_RESETANGLESACTION_H
#define WIREFRAME_RESETANGLESACTION_H

#include "ui/toolbar/action/ToolBarAction.h"
#include "wireframe/WireframeRedactor.h"
#include "ui/toolbar/action/WireframeAction.h"

class ResetAnglesAction : public WireframeAction {

public:
    ResetAnglesAction(const QString &iconPath, const QString &name, WireframeRedactor &wireframe);

    void onMouseClicked() override;

};


#endif //WIREFRAME_RESETANGLESACTION_H
