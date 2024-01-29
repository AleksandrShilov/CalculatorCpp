cmake_minimum_required(VERSION 3.5)

project(Calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets PrintSupport REQUIRED)

set(VIEW_SOURCES
        View/mainwindow.cpp
        View/mainwindow.h
        View/mainwindow.ui
        View/graph.cpp
        View/graph.h
        View/graph.ui
        View/input_x.cpp
        View/input_x.h
        View/input_x.ui
        View/creditcalc.cpp
        View/creditcalc.h
        View/creditcalc.ui
        View/deposit.cpp
        View/deposit.h
        View/deposit.ui
)

set(MODEL_SOURCES
        Model/validate.cpp
        Model/validate.h
        Model/calculate.cpp
        Model/calculate.h
        Model/parse.cpp
        Model/parse.h
        Model/rpn.cpp
        Model/rpn.h
        Model/calculatedeposit.cpp
        Model/calculatedeposit.h
)

set(CONTROLLER_SOURCES
        Controller/controller.cpp
        Controller/controller.h
)

set(PROJECT_SOURCES
        main.cpp
        qcustomplot.cpp
        qcustomplot.h
)

add_executable(Calculator ${PROJECT_SOURCES} ${CONTROLLER_SOURCES} ${MODEL_SOURCES} ${VIEW_SOURCES})

target_link_libraries(Calculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt5::PrintSupport)

set_target_properties(Calculator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


