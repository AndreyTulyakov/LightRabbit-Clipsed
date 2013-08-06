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

QMap<QString, GLWidget*> GLWidget::instances;

GLWidget::GLWidget(QWidget *parent, QString pInstanceName) :
    QGLWidget(parent)
{
    widgetName = pInstanceName;
    mode = GLWidgetMode::ClipEdit;
    setMouseTracking(true);
    instances.insert(widgetName,this);
    mouseRight = false;
}

GLWidget::~GLWidget()
{
    delete atlasSound;
    instances.remove(widgetName);
    delete spriteCurrentTexture;
    delete spriteSound;
    DefaultShaders::deleteInstance();
    timer.stop();
}

void GLWidget::setClipInfo(ClipInfo pInfo)
{
    clipInfo = pInfo;
}

void GLWidget::showTextureSprite(TextureAtlas *pAtlas)
{
    if(pAtlas == 0)
    {
        spriteCurrentTexture->setAtlas(atlasTexture);
    }
    else
    {
        spriteCurrentTexture->setAtlas(pAtlas);
    }


}

void GLWidget::centerTexCamera()
{
    texCamera.setPosition(-width() / 2, - height() / 2, 1);
    texCamera.setZoom(1);
}

void GLWidget::selectTexture(TextureAtlas *arg)
{
    if(arg == 0 || arg == nullptr)
    {
        spriteCurrentTexture->setAtlas(atlasTexture);
    }
    else
    {
        spriteCurrentTexture->setAtlas(arg);
    }

}

void GLWidget::attachToRootScene(SceneObject *obj)
{
    rootScene.attachChild(obj);
}

void GLWidget::detachFromRootScene(SceneObject *obj)
{
    rootScene.detachChild(obj);
}

GLWidget* GLWidget::getInstance(QString pInstanceName)
{
    if (instances.contains(pInstanceName))
    {
        return instances.value(pInstanceName);
    }
    else
    {
        qDebug() << "GLWidget::getInstance: can't find instance:" << pInstanceName << endl;
    }

    return 0;
}

void GLWidget::setBackgroundColor(QColor color)
{
    qreal r,g,b;
    color.getRgbF(&r, &g, &b);
    clipInfo.Color = QVector4D(r,g,b,1);
    eRect->setColor(clipInfo.Color.x(), clipInfo.Color.y(), clipInfo.Color.z(), 1.0f);
}

QColor GLWidget::getBackgroundColor()
{
    return QColor::fromRgbF(clipInfo.Color.x(), clipInfo.Color.y(), clipInfo.Color.z(), 1);
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


    spriteCurrentTexture = new Entity::Sprite();
    spriteSound = new Entity::Sprite();
    spriteEmptyScene = new Entity::Sprite();

    atlasSound = new TextureAtlas(":/Icons/sound_icon.png");
    atlasTexture = new TextureAtlas(":/Icons/texture_icon.png");
    atlasScene = new TextureAtlas(":/Icons/scene_icon.png");

    spriteSound->setAtlas(atlasSound);
    spriteEmptyScene->setAtlas(atlasScene);

    sceneSound.setCamera(&texCamera);
    sceneSound.attachChild(spriteSound);

    textureScene.attachChild(spriteCurrentTexture);

    // FUNCTIONAL TESTING ===============================================

    rootScene.setCamera(&camera);
    {
        /*
        Entity::Line *eLine1 = new Entity::Line(0, -100, 0, 100);
        eLine1->setColor(1, 1, 1, 0.5f);
        rootScene.attachChild(eLine1);

        Entity::Line *eLine2 = new Entity::Line(-100, 0, 100, 0);
        eLine2->setColor(1, 1, 1, 0.5f);
        rootScene.attachChild(eLine2);
        */

        eRect = new Entity::Rect(-clipInfo.Width / 2, -clipInfo.Height / 2, clipInfo.Width, clipInfo.Height);
        eRect->setColor(clipInfo.Color.x(), clipInfo.Color.y(), clipInfo.Color.z(), 1.0f);
        eRect->setFilledDraw(true);
        rootScene.attachChild(eRect);

        rootScene.attachChild(spriteEmptyScene);
    }

    textureScene.setCamera(&texCamera);
    {
        textureScene.attachChild(spriteCurrentTexture);
    }

    selectTexture(0);

    timer.start(1000 / 60, this);

    this->makeCurrent();
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

    switch (mode)
    {
        case GLWidgetMode::ClipEdit:

            glClearColor(0.66f, 0.66f, 0.66f, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            rootScene.update();
            rootScene.draw();

            break;


        case GLWidgetMode::TextureList:

            glClearColor(0.66f, 0.66f, 0.85f, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            textureScene.update();
            textureScene.draw();

            break;

        case GLWidgetMode::SoundList:

            glClearColor(0.4f, 0.9f, 0.4f, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            sceneSound.update();
            sceneSound.draw();
            break;
    }

}


void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Move Camera
    if (mouseRight)
    {
        QPoint pos = event->pos() - oldMousePos;

        if (mode == GLWidgetMode::TextureList)
            texCamera.setPosition(texCamera.getPosition().x() - pos.x(), texCamera.getPosition().y() + pos.y(), 0);

        if (mode == GLWidgetMode::ClipEdit)
            camera.setPosition(camera.getPosition().x() - pos.x(), camera.getPosition().y() + pos.y(), 0);

        oldMousePos = event->pos();
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
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
    switch (event->button())
    {
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

void GLWidget::wheelEvent(QWheelEvent *event)
{
    float k = 0.5f;
    float sf = 0;

    if (event->delta() > 0)
        sf += k;
    else
        sf -= k;

    if (mode == GLWidgetMode::TextureList)
    {
        if((texCamera.getZoom() + sf)>2.0f)
        {
            texCamera.setZoom(2.0f);
            return;
        }

        if((texCamera.getZoom() + sf)<0.5f)
        {
            texCamera.setZoom(0.5f);
            return;
        }
        texCamera.setZoom(texCamera.getZoom() + sf);
    }

    if (mode == GLWidgetMode::ClipEdit)
    {
        if((camera.getZoom() + sf)>2.0f)
        {
            camera.setZoom(2.0f);
            return;
        }

        if((camera.getZoom() + sf)<0.5f)
        {
            camera.setZoom(0.5f);
            return;
        }

        camera.setZoom(camera.getZoom() + sf);
    }
}
