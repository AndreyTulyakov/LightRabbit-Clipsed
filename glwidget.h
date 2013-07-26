
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLBuffer>
#include <QtOpenGL/qglshaderprogram.h>
#include <shader.h>
#include <geometryengine.h>

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
        QBasicTimer timer;
        QGLShaderProgram* program;
        GeometryEngine geometries;

        GLuint texture;

        QMatrix4x4 projection;

        QVector2D mousePressPosition;
        QVector3D rotationAxis;
        qreal angularSpeed;
        QQuaternion rotation;

};

#endif

