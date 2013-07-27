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
    camera2d.cpp \
    defaultshaders.cpp \
    sceneobject.cpp \
    scene.cpp \
    DrawableEntity.cpp \
    EntityObject.cpp \
    Line.cpp \
    rect.cpp \
    VertexBufferManager.cpp \
    Sprite.cpp

HEADERS  += mainwindow.h \
    formabout.h \
    glwidget.h \
    shader.h \
    camera2d.h \
    defaultshaders.h \
    sceneobject.h \
    scene.h \
    DrawableEntity.h \
    VertexTypes.h \
    EntityObject.h \
    Line.h \
    rect.h \
    VertexBufferManager.h \
    Sprite.h

FORMS    += mainwindow.ui \
    formabout.ui

OTHER_FILES += \
    README.md

RESOURCES += \
    Shaders.qrc
