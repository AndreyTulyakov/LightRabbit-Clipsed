#include "camera2d.h"

Camera2D::Camera2D()
{
    translation.setToIdentity();
    rotation.setToIdentity();
    projection.setToIdentity();
}

QMatrix4x4 Camera2D::getCameraMatrix()
{
    return rotation * translation * projection;
}

void Camera2D::setPosition(float x = 0, float y = 0, float z = 0)
{
    setPosition(x,y,z);
    translation.setToIdentity();
    translation.translate(-x, -y, -z);
}

void Camera2D::setRotationRoll(float arg)
{
    rotation.setToIdentity();
    rotation.rotate(arg,0,0,1);
}

void Camera2D::setOrtho(float width, float height, float near, float far)
{
    projection.setToIdentity();
    projection.ortho(0,width,height,0,near,far);
}
