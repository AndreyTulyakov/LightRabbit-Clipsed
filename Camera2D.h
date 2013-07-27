#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "EntityObject.h"

#include <QMatrix4x4>


class Camera2D : public EntityObject
{
private:
    QMatrix4x4 projection;
    QMatrix4x4 translation;
    QMatrix4x4 rotation;
    QMatrix4x4 view;

public:
    Camera2D();

    QMatrix4x4 getCameraMatrix();

    void setOrtho(float width, float height, float near, float far, bool LeftTopStart = false);
    void setRotationRoll(float arg);
    void setPosition(float x, float y, float z);

};

#endif // CAMERA2D_H
