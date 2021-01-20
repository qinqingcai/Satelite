QT       += core gui multimedia multimediawidgets
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SkyBox
TEMPLATE = app

SOURCES += \
    src/Cube.cpp \
    src/Matrix.cpp \
    src/SkyBox.cpp \
    src/TWindow.cpp \
    src/bg_btn.cpp \
    src/demo_show.cpp \
    src/earth.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/start_widget.cpp \
    src/switchcontrol.cpp \
    src/wx.cpp

HEADERS += \
    src/Cube.h \
    src/GLHeaders.h \
    src/Matrix.h \
    src/SkyBox.h \
    src/TWindow.h \
    src/bg_btn.h \
    src/demo_show.h \
    src/earth.h \
    src/mainwindow.h \
    src/start_widget.h \
    src/switchcontrol.h \
    src/wx.h

RESOURCES += \
    Assets.qrc

FORMS += \
    src/mainwindow.ui
