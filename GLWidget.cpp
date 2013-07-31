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

    workArea = QRect(0,0,400,300);
}

GLWidget::~GLWidget()
{
    VertexBufferManager::deleteInstance();
    DefaultShaders::deleteInstance();
    deleteTexture(texture);
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

    glClearColor(0.66f, 0.66f, 0.99f, 1.0f);


    // FUNCTIONAL TESTING ===============================================

    atlas = new TextureAtlas("image.png", this->context());

    new TextureAtlas("image.png", this->context());

    //VBManager = VertexBufferManager::getInstance();

    rootScene.setCamera(&camera);

    Entity::Line* eLine = new Entity::Line(0, -100, 0, 100);
    rootScene.attachChild(eLine);

    rootScene.attachChild(new Entity::Line(-100, 0, 100, 0));

    eRect = new Entity::Rect(workArea.x(), workArea.y(), workArea.width(), workArea.height());
    eRect->setColor(1, 1, 1, 0.5f);
    rootScene.attachChild(eRect);

    TextureAtlas* atlas2 = new TextureAtlas("image2.png", this->context());

    Entity::Sprite* eSprite = new Entity::Sprite(atlas2);
    eSprite->setPosition(100, 100, 0);
    rootScene.attachChild(eSprite);

    esb = new Entity::SpriteBatch(atlas, 100);
    rootScene.attachChild(esb);

    timer.start(1000 / 60, this);
}


void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    camera.setOrtho(w, h, -10, 100, false);
    camera.setPosition(-width() / 2, - height() / 2, 1);
}


static float tick = 0;

void GLWidget::paintGL()
{

    float rcut = 256 * tick / 6.28f;
    TextureRegion region(atlas, rcut, 0, 512 - rcut, 512);
    esb->addStart();
    for (float i = 0; i <= 6.28; i += 0.314f) {
        esb->addSprite(&region, cos(i + tick) * 2 * 100, sin(i * 2 + tick) * 100, i / 20, i / 20, 360 * (tick + i), 1, 1, 1, i / 6.28f);
    }
    esb->addEnd();



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rootScene.update();
    rootScene.draw();


    if (tick > 6.28f) {
        tick = 0.0f;

    }

    float f = sin(tick);
    if (f < 0) f *= -1.0f;
    eRect->setScale(1 + f, 1 + f, 1);

    tick += 0.02f;

}
