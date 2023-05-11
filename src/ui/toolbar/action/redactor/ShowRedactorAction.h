//
// Created by Влад Кирилов on 24.04.2023.
//

#ifndef WIREFRAME_SHOWREDACTORACTION_H
#define WIREFRAME_SHOWREDACTORACTION_H


#include "ui/toolbar/action/ToolBarAction.h"
#include "wireframe/WireframeRedactor.h"
#include "ui/toolbar/action/WireframeAction.h"

class ShowRedactorAction : public WireframeAction {
public:
    ShowRedactorAction(const QString &iconPath, const QString &name, WireframeRedactor &wireframe);

    void onMouseClicked() override;
};


#endif //WIREFRAME_SHOWREDACTORACTION_H
