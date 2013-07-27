
#include <QtWidgets>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"

#include "defaultshaders.h"
#include "Line.h"
#include "rect.h"

#include <QMouseEvent>

#include <math.h>
#include <locale.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{

}

GLWidget::~GLWidget()
{
    DefaultShaders::deleteInstance();
    deleteTexture(texture);
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{

}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{

}

void GLWidget::timerEvent(QTimerEvent *)
{

    updateGL();
}

void GLWidget::initializeGL()
{
    initializeGLFunctions();

    rootScene.setCamera(&camera);

    Entity::Line* eLine = new Entity::Line(100, 50, 100, 300);
    rootScene.attachChild(eLine);
    eLine->setColor(1,1,1,0.5f);

    Entity::Rect* eRect = new Entity::Rect(50,100,300,100);
    eRect->setColor(1,1,1,0.5f);
    rootScene.attachChild(eRect);

    initTextures();

    //GL.Enable(EnableCap.Blend);
    //GL.BlendFunc(BlendingFactorSrc.SrcAlpha, BlendingFactorDest.OneMinusSrcAlpha);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
