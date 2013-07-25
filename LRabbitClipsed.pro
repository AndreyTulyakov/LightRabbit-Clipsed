#-------------------------------------------------
#
# Project created by QtCreator 2013-07-23T10:29:53
#
#-------------------------------------------------

QT       += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LRabbitClipsed
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    formabout.cpp \
    glwidget.cpp \
    shader.cpp \
    geometryengine.cpp

HEADERS  += mainwindow.h \
    formabout.h \
    glwidget.h \
    shader.h \
    geometryengine.h

FORMS    += mainwindow.ui \
    formabout.ui

OTHER_FILES += \
    README.md
