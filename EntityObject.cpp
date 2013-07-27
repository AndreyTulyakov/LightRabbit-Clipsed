#include "EntityObject.h"

EntityObject::EntityObject()
{
    position = QVector3D(0, 0, 0);
    zRotation = 0;
    scale = QVector3D(1, 1, 1);
}

void EntityObject::setPosition(float x, float y, float z)
{
    position.setX(x);
    position.setY(y);
    position.setZ(z);
}

void EntityObject::setRotationZ(float z)
{
    zRotation = z;
}

QVector3D EntityObject::getPosition()
{
    return position;
}

float EntityObject::getRotationZ()
{
    return zRotation;
}

QVector3D EntityObject::getScale()
{
    return scale;
}

void EntityObject::setScale(float x, float y, float z)
{
    scale = QVector3D(x, y, z);
}

void EntityObject::setPosition(QVector3D arg)
{
    position = arg;
}

void EntityObject::setScale(QVector3D arg)
{
    scale = arg;
}
