//
// Created by Влад Кирилов on 16.04.2023.
//

#include "MainWindow.h"
#include "ui/toolbar/ToolbarWidget.h"
#include "wireframe/WireframeRedactor.h"
#include "ui/menu/MenuWidget.h"

MainWindow::MainWindow() : QMainWindow() {
    resize(640,480);

    auto wireframeView = new WireframeRedactor(this);
    setCentralWidget(wireframeView);

    auto toolbar = new ToolbarWidget(this, *wireframeView);

    auto menu = new MenuWidget(*toolbar);
    setMenuBar(menu);
    addToolBar(toolbar);
}
