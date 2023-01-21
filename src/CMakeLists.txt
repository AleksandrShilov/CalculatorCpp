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

set(PROJECT_SOURCES
        main.cpp
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
        Controller/controller.cpp
        Controller/controller.h
        qcustomplot.cpp
        qcustomplot.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Calculator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Calculator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Calculator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Calculator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Calculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt5::PrintSupport)

set_target_properties(Calculator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Calculator)
endif()
