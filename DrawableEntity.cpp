#include "DrawableEntity.h"

DrawableEntity::DrawableEntity()
{
    isTransformed = true;
    camera = 0;
    shaderProgram = 0;
    color = QVector4D(1, 1, 1, 1);
    transform.setToIdentity();
}

void DrawableEntity::setCamera(Camera2D *arg)
{
    camera = arg;
}

void DrawableEntity::setColor(QVector4D arg)
{
    color = arg;
}

void DrawableEntity::setColor(float r, float g, float b, float a)
{
    color = QVector4D(r, g, b, a);
}

QVector4D DrawableEntity::getColor()
{
    return color;
}
