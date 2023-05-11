//
// Created by Влад Кирилов on 24.04.2023.
//

#include "ToolbarWidget.h"


ToolbarWidget::ToolbarWidget(QWidget *parent, WireframeRedactor &view) : QToolBar(parent) {
    setFixedHeight(25);

    setMovable(false);

    auto iconPrefix = QString("/Users/vladkirilov/CLionProjects/wireframe/resources/");

    openFileAction = std::make_shared<OpenFileAction>(iconPrefix + "open.png", "Open", view);
    saveFileAction = std::make_shared<SaveFileAction>(iconPrefix + "save.png", "Save", view);
    showRedactorAction = std::make_shared<ShowRedactorAction>(iconPrefix + "settings.png",
                                                              "Show spline redactor", view);
    resetAnglesAction = std::make_shared<ResetAnglesAction>(iconPrefix + "reset.png",
                                                            "Reset angles", view);
    aboutAction = std::make_shared<AboutAction>(iconPrefix + "about.png", "About");

    addAction(openFileAction.get());
    addAction(saveFileAction.get());

    addSeparator();

    addAction(showRedactorAction.get());
    addAction(resetAnglesAction.get());

    addSeparator();

    addAction(aboutAction.get());
}

SaveFileAction *ToolbarWidget::getSaveFileAction() const {
    return saveFileAction.get();
}

OpenFileAction *ToolbarWidget::getOpenFileAction() const {
    return openFileAction.get();
}

ShowRedactorAction *ToolbarWidget::getShowRedactorAction() const {
    return showRedactorAction.get();
}

ResetAnglesAction *ToolbarWidget::getResetAnglesAction() const {
    return resetAnglesAction.get();
}

AboutAction *ToolbarWidget::getAboutAction() const {
    return aboutAction.get();
}
