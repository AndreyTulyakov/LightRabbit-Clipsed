#include "Camera2D.h"

Camera2D::Camera2D()
{
    translation.setToIdentity();
    rotation.setToIdentity();
    projection.setToIdentity();
    view.lookAt(QVector3D(0, 0, 1), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
}

QMatrix4x4 Camera2D::getCameraMatrix()
{

    return projection * view * rotation * translation;
}

void Camera2D::setPosition(float x = 0, float y = 0, float z = 0)
{
    EntityObject::setPosition(x, y, z);
    translation.setToIdentity();
    translation.translate(-x, -y, -z);
}

void Camera2D::setRotationRoll(float arg)
{
    rotation.setToIdentity();
    rotation.rotate(arg, 0, 0, 1);
}

void Camera2D::setOrtho(float width, float height, float near, float far, bool LeftTopStart)
{
    projection.setToIdentity();
    if (LeftTopStart) {
        projection.ortho(0, width, height, 0, near, far);
    } else {
        projection.ortho(0, width, 0, height, near, far);
    }

}
