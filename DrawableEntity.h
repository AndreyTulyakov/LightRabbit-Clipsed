#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H

#include "Camera2D.h"
#include "SceneObject.h"

#include <QGLShaderProgram>

class DrawableEntity : public SceneObject
{
protected:
    Camera2D* camera;
    QGLShaderProgram* shaderProgram;
    QVector4D color;

    QMatrix4x4 transform;
    bool isTransformed;

public:

    DrawableEntity();
    void setCamera(Camera2D* arg);

    void setColor(QVector4D arg);
    void setColor(float r, float g, float b, float a);
    QVector4D getColor();

    virtual void draw() = 0;
};

#endif // DRAWABLEENTITY_H
