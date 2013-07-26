
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "camera2d.h"
#include "scene.h"

#include <QGLWidget>
#include <QGLBuffer>
#include <QtOpenGL/qglshaderprogram.h>
#include <shader.h>

#include <QGLFunctions>
#include <QBasicTimer>


class GLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT


public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
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

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

};

#endif

