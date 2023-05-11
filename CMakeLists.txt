cmake_minimum_required(VERSION 3.25)
project(wireframe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/vladkirilov/Qt/6.4.2/macos/lib/cmake:/Users/vladkirilov/CLionProjects/wireframe/src")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
include_directories("src")

add_executable(wireframe src/main.cpp src/spline_redactor/SplineRedactor.cpp src/spline_redactor/SplineRedactor.h src/spline_redactor/form/SplineForm.cpp src/spline_redactor/form/SplineForm.h src/spline_redactor/graph/SplineGraph.cpp src/spline_redactor/graph/SplineGraph.h src/ui/MainWindow.cpp src/ui/MainWindow.h src/math/spline/spline.cpp src/math/spline/spline.h src/types.h src/Fwd.h src/math/spline/Spline.cpp src/math/spline/Spline.h src/math/spline/Spline.cpp src/math/spline/point/SplinePoint.cpp src/math/spline/point/SplinePoint.h src/wireframe/WireframeRedactor.cpp src/wireframe/WireframeRedactor.h src/math/wireframe/Wireframe.cpp src/math/wireframe/Wireframe.h src/ui/toolbar/ToolbarWidget.cpp src/ui/toolbar/ToolbarWidget.h src/ui/toolbar/action/ToolBarAction.cpp src/ui/toolbar/action/ToolBarAction.h src/ui/toolbar/action/file/open/OpenFileAction.cpp  src/ui/toolbar/action/file/save/SaveFileAction.h src/ui/toolbar/action/file/save/SaveFileAction.cpp src/ui/toolbar/action/redactor/ShowRedactorAction.cpp src/ui/toolbar/action/redactor/ShowRedactorAction.h src/ui/toolbar/action/reset/ResetAnglesAction.cpp src/ui/toolbar/action/reset/ResetAnglesAction.h src/ui/toolbar/action/WireframeAction.cpp src/ui/toolbar/action/WireframeAction.h src/math/wireframe/point/WireframePoint.cpp src/math/wireframe/point/WireframePoint.h src/wireframe/view/WireframeGraph.cpp src/wireframe/view/WireframeGraph.h src/ui/toolbar/action/about/AboutAction.h src/ui/toolbar/action/about/AboutAction.cpp src/ui/menu/MenuWidget.h src/ui/menu/MenuWidget.cpp)

target_link_libraries(wireframe
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

