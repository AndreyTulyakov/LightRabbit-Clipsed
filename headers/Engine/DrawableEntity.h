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

#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H

#include "Camera2D.h"
#include "SceneObject.h"

#include <QGLBuffer>
#include <QGLShaderProgram>

class DrawableEntity : public SceneObject
{
    protected:
        Camera2D *camera;
        QGLShaderProgram *shaderProgram;
        QGLBuffer *vertexBuffer;
        QVector4D color;

        QMatrix4x4 transform;
        bool isTransformed;

        void createVertexBuffer(const void *data, int count);
        void createVertexBuffer(int count);

    public:

        DrawableEntity();
        virtual ~DrawableEntity();
        void setCamera(Camera2D *arg);

        void setColor(QVector4D arg);
        void setColor(float r, float g, float b, float a);
        QVector4D getColor();

        virtual void draw() = 0;
};

#endif // DRAWABLEENTITY_H
