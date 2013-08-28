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

#pragma once

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "Camera2D.h"
#include "Scene.h"

#include <QGLWidget>
#include <QGLBuffer>
#include <QtOpenGL/qglshaderprogram.h>

#include <QGLFunctions>
#include <QBasicTimer>
#include <QMap>

#include "Rect.h"
#include "SpriteBatch.h"
#include "TextureAtlas.h"

#include "VertexBufferManager.h"

#include "FormNewClip.h"
#include "Sprite.h"
#include "Text.h"


#include "ListWidgetItems.h"


enum GLWidgetMode
{
    ClipEdit, TextureList, SoundList
};

class GLWidget : public QGLWidget, protected QGLFunctions
{
        Q_OBJECT

        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void wheelEvent(QWheelEvent *event);

    public:
        GLWidgetMode mode;

        explicit GLWidget(QWidget *parent, QString pInstanceName);
        ~GLWidget();

        void setClipInfo(ClipInfo pInfo);
        void showTextureSprite(TextureAtlas *pAtlas);
        void centerTexCamera();
        void selectTexture(TextureAtlas* arg);

        void attachToRootScene(SceneObject *obj);
        void detachFromRootScene(SceneObject *obj);

        static GLWidget* getInstance(QString pInstanceName);

        void setBackgroundColor(QColor color);
        QColor getBackgroundColor();

        void selectSprite(Entity::Sprite* sprite);
        void selectText(Entity::Text* text);

        void unselectAll();

    protected:
        void timerEvent(QTimerEvent *e);

        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();

        void initShaders();

        void updateSelected();

    signals:
        void onSelectedChanged();

    private:
        QString widgetName;

        static QMap<QString, GLWidget*> instances;

        ClipInfo clipInfo;
        bool mouseRight, mouseLeft;
        QPoint oldMousePos;

        Entity::Rect *eRect;

        Camera2D camera, texCamera;
        Scene rootScene, textureScene, sceneSound;
        Entity::Sprite *spriteCurrentTexture, *spriteSound;
        TextureAtlas *atlasSound, *atlasTexture;
        QBasicTimer timer;

        EntityType entityIsSelected;
        SceneObject *selectedEntity;
        Entity::Rect* rectSelection;

};

#endif

