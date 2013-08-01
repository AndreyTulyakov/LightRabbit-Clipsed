#include "GLWidget.h"

#include <QtWidgets>
#include <QtOpenGL>
#include <math.h>

#include "DefaultShaders.h"
#include "Line.h"
#include "Rect.h"
#include "Sprite.h"

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
}

void GLWidget::setClipInfo(ClipInfo pInfo)
{
    clipInfo = pInfo;
}

void GLWidget::timerEvent(QTimerEvent *)
{
    updateGL();
}

void GLWidget::initializeGL()
{
    initializeGLFunctions();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glEnable(GL_POLYGON_STIPPLE);

    glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_MULTISAMPLE);

    QVector4D color = clipInfo.Color;
    glClearColor(color.x(),color.y(),color.z(),color.w());


    // FUNCTIONAL TESTING ===============================================

    rootScene.setCamera(&camera);

    Entity::Line* eLine1 = new Entity::Line(0, -100, 0, 100);
    eLine1->setColor(1, 1, 1, 0.5f);
    rootScene.attachChild(eLine1);

    Entity::Line* eLine2 = new Entity::Line(-100, 0, 100, 0);
    eLine2->setColor(1, 1, 1, 0.5f);
    rootScene.attachChild(eLine2);

    Entity::Rect* eRect = new Entity::Rect(-clipInfo.Width/2, -clipInfo.Height/2, clipInfo.Width, clipInfo.Height);
    eRect->setColor(1, 1, 1, 0.5f);
    rootScene.attachChild(eRect);

    timer.start(1000 / 60, this);
}


void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    camera.setOrtho(w, h, -10, 100, false);
    camera.setPosition(-width() / 2, - height() / 2, 1);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rootScene.update();
    rootScene.draw();
}
