
#include "Camera2D.h"

Camera2D::Camera2D()
{
    translation.setToIdentity();
    rotation.setToIdentity();
    projection.setToIdentity();
    zoom.setToIdentity();
    zoom.scale(1);
    view.lookAt(QVector3D(0, 0, 1), QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    zoomFactor = 1;
}

float Camera2D::getZoom()
{
    return zoomFactor;
}

void Camera2D::setZoom(float pZoom)
{
    zoomFactor = pZoom;
    if (zoomFactor < 0.01f)
        zoomFactor = 0.01f;

    if (zoomFactor > 1000.0f)
        zoomFactor = 1000.0f;

    zoom.setToIdentity();
    zoom.scale(zoomFactor, zoomFactor, 1);
}

QMatrix4x4 Camera2D::getCameraMatrix()
{

    return projection * view  * translation * rotation * zoom;
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
    if (LeftTopStart)
    {
        projection.ortho(0, width, height, 0, near, far);
    }
    else
    {
        projection.ortho(0, width, 0, height, near, far);
    }

}
