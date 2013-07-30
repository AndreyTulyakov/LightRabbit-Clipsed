/*
 * Copyright (C) 2013 Andrey Tulyakov
 * @mail: mhyhre@gmail.com
 *
 * This work is licensed under a Creative Commons
 * Attribution-NonCommercial-NoDerivs 3.0 Unported License.
 * You may obtain a copy of the License at
 *
 *              http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode
 *
 */


#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "Camera2D.h"
#include "Scene.h"

#include <QGLWidget>
#include <QGLBuffer>
#include <QtOpenGL/qglshaderprogram.h>

#include <QGLFunctions>
#include <QBasicTimer>

#include "Rect.h"
#include "SpriteBatch.h"
#include "TextureAtlas.h"

#include "VertexBufferManager.h"


class GLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT


public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void timerEvent(QTimerEvent *e);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();

private:

    Camera2D camera;
    Scene rootScene;

    QBasicTimer timer;

    GLuint texture;

    Entity::Rect* eRect;
    Entity::SpriteBatch* esb;

    TextureAtlas *atlas;

    VertexBufferManager *VBManager;

};

#endif

