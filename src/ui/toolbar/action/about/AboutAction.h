//
// Created by Влад Кирилов on 04.04.2023.
//

#ifndef FILTERS_ABOUTACTION_H
#define FILTERS_ABOUTACTION_H

#include "types.h"


#include "types.h"
#include "ui/toolbar/action/ToolBarAction.h"

class AboutAction : public ToolBarAction {
private:
    String text;
public:
    AboutAction(const QString &iconPath, const QString &name);

public:

    void onMouseClicked() override;
};


#endif //FILTERS_ABOUTACTION_H
