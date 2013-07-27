
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "Camera2D.h"
#include "Scene.h"

#include <QGLWidget>
#include <QGLBuffer>
#include <QtOpenGL/qglshaderprogram.h>

#include <QGLFunctions>
#include <QBasicTimer>

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
    void initTextures();

private:
    Camera2D camera;
    Scene rootScene;

    QBasicTimer timer;

    GLuint texture;

    VertexBufferManager *VBManager;
};

#endif

