//
// Created by Влад Кирилов on 24.04.2023.
//

#ifndef WIREFRAME_TOOLBARWIDGET_H
#define WIREFRAME_TOOLBARWIDGET_H

#include <QToolBar>
#include "wireframe/WireframeRedactor.h"
#include "ui/toolbar/action/file/save/SaveFileAction.h"
#include "ui/toolbar/action/file/open/OpenFileAction.h"
#include "ui/toolbar/action/redactor/ShowRedactorAction.h"
#include "ui/toolbar/action/reset/ResetAnglesAction.h"
#include "ui/toolbar/action/about/AboutAction.h"

class ToolbarWidget : public QToolBar {
Q_OBJECT

public:
    explicit ToolbarWidget(QWidget *parent, WireframeRedactor &view);

    std::shared_ptr<SaveFileAction> saveFileAction;
    std::shared_ptr<OpenFileAction> openFileAction;
    std::shared_ptr<ShowRedactorAction> showRedactorAction;
    std::shared_ptr<ResetAnglesAction> resetAnglesAction;
    std::shared_ptr<AboutAction> aboutAction;

    [[nodiscard]]  SaveFileAction *getSaveFileAction() const;

    [[nodiscard]]  OpenFileAction *getOpenFileAction() const;

    [[nodiscard]]  ShowRedactorAction *getShowRedactorAction() const;

    [[nodiscard]]  ResetAnglesAction *getResetAnglesAction() const;

    [[nodiscard]]  AboutAction *getAboutAction() const;
};


#endif //WIREFRAME_TOOLBARWIDGET_H
