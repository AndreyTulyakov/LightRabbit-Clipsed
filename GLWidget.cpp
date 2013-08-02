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
    mode = GLWidgetMode::ClipEdit;
    setMouseTracking(true);


    mouseRight = false;
}

GLWidget::~GLWidget()
{
    delete textureSprite;
    DefaultShaders::deleteInstance();
    timer.stop();
}

void GLWidget::setClipInfo(ClipInfo pInfo)
{
    clipInfo = pInfo;
}

void GLWidget::showTextureSprite(TextureAtlas *pAtlas)
{

    textureSprite->setAtlas(pAtlas);
    textureScene.attachChild(textureSprite);
}

void GLWidget::centerTexCamera()
{
    texCamera.setPosition(-width() / 2, - height() / 2, 1);
    texCamera.setZoom(1);
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


    textureSprite = new Entity::Sprite();


    // FUNCTIONAL TESTING ===============================================

    rootScene.setCamera(&camera);
    {
        Entity::Line* eLine1 = new Entity::Line(0, -100, 0, 100);
        eLine1->setColor(1, 1, 1, 0.5f);
        rootScene.attachChild(eLine1);

        Entity::Line* eLine2 = new Entity::Line(-100, 0, 100, 0);
        eLine2->setColor(1, 1, 1, 0.5f);
        rootScene.attachChild(eLine2);

        Entity::Rect* eRect = new Entity::Rect(-clipInfo.Width / 2, -clipInfo.Height / 2, clipInfo.Width, clipInfo.Height);
        eRect->setColor(1, 1, 1, 0.5f);
        rootScene.attachChild(eRect);
    }

    textureScene.setCamera(&texCamera);
    {
        Entity::Line* eLine1 = new Entity::Line(0, -100, 0, 100);
        eLine1->setColor(1, 1, 1, 0.5f);
        textureScene.attachChild(eLine1);

        Entity::Line* eLine2 = new Entity::Line(-100, 0, 100, 0);
        eLine2->setColor(1, 1, 1, 0.5f);
        textureScene.attachChild(eLine2);

        textureScene.attachChild(textureSprite);
    }

    timer.start(1000 / 60, this);
}




void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    camera.setOrtho(w, h, -10, 100, false);
    camera.setPosition(-width() / 2, - height() / 2, 1);

    texCamera.setOrtho(w, h, -10, 10, false);
    texCamera.setPosition(-width() / 2, - height() / 2, 1);
}

void GLWidget::paintGL()
{

    switch (mode) {
    case GLWidgetMode::ClipEdit:

        glClearColor(clipInfo.Color.x(), clipInfo.Color.y(), clipInfo.Color.z(), 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        rootScene.update();
        rootScene.draw();

        break;


    case GLWidgetMode::TextureShow:

        glClearColor(0.66f, 0.66f, 0.75f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        textureScene.update();
        textureScene.draw();

        break;
    }


}


void GLWidget::mouseMoveEvent(QMouseEvent * event)
{
    // Move Camera
    if (mouseRight) {
        QPoint pos = event->pos() - oldMousePos;

        if (mode == GLWidgetMode::TextureShow)
            texCamera.setPosition(texCamera.getPosition().x() - pos.x(), texCamera.getPosition().y() + pos.y(), 0);
        else
            camera.setPosition(camera.getPosition().x() - pos.x(), camera.getPosition().y() + pos.y(), 0);

        oldMousePos = event->pos();
    }
}

void GLWidget::mousePressEvent(QMouseEvent * event)
{
    switch (event->button()) {
    case Qt::MouseButton::LeftButton:
        qDebug() << "Left press";
        break;

    case Qt::MouseButton::RightButton:
        mouseRight = true;
        oldMousePos = event->pos();
        break;

    default:
        break;
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::MouseButton::LeftButton:
        qDebug() << "Left release";

        break;

    case Qt::MouseButton::RightButton:
        mouseRight = false;
        break;

    default:
        break;
    }
}

void GLWidget::wheelEvent(QWheelEvent * event)
{
    float k = 0.2f;
    float sf = 0;

    if (event->delta() > 0)
        sf += k;
    else
        sf -= k;

    if (mode == GLWidgetMode::TextureShow)
        texCamera.setZoom(texCamera.getZoom() + sf);
    else
        camera.setZoom(camera.getZoom() + sf);
}
