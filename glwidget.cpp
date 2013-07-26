
#include <QtWidgets>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"

#include "defaultshaders.h"
#include "Line.h"

#include <QMouseEvent>

#include <math.h>
#include <locale.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    angularSpeed(0)
{
}

GLWidget::~GLWidget()
{
    DefaultShaders::deleteInstance();
    deleteTexture(texture);
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void GLWidget::timerEvent(QTimerEvent *)
{

    updateGL();
}

void GLWidget::initializeGL()
{
    initializeGLFunctions();

    rootScene.setCamera(&camera);

    Entity::Line* eLine = new Entity::Line(0, 0, width(), height());
    rootScene.attachChild(eLine);

    initTextures();

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glClearColor(0.66f, 0.66f, 0.66f, 1.0f);

    timer.start(15, this);
}

void GLWidget::initTextures()
{
    // Load cube.png image
    glEnable(GL_TEXTURE_2D);
    texture = bindTexture(QImage("res/textures/image.png"));

    // Set nearest filtering mode for texture minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    camera.setOrtho(w, h, -1, 100);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rootScene.update();
    rootScene.draw();

}
