#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H

#include "camera2d.h"
#include "sceneobject.h"

#include <QGLShaderProgram>

class DrawableEntity : public SceneObject
{
protected:
    Camera2D* camera;
    QGLShaderProgram* shaderProgram;

    QMatrix4x4 transform;
    bool isTransformed;

public:

    DrawableEntity();
    void setCamera(Camera2D* arg);

    virtual void draw() = 0;
};

#endif // DRAWABLEENTITY_H
