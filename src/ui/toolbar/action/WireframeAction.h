//
// Created by Влад Кирилов on 30.04.2023.
//

#ifndef WIREFRAME_WIREFRAMEACTION_H
#define WIREFRAME_WIREFRAMEACTION_H


#include "ToolBarAction.h"
#include "math/wireframe/Wireframe.h"
#include "wireframe/WireframeRedactor.h"

class WireframeAction : public ToolBarAction {

protected:
    WireframeRedactor &wireframe;

public:
    WireframeAction(const QString &iconPath, const QString &name, WireframeRedactor &wireframe);

};


#endif //WIREFRAME_WIREFRAMEACTION_H
