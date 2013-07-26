#include "EntityObject.h"

EntityObject::EntityObject()
{
    position = QVector3D(0, 0, 0);
    rotation = QVector3D(0, 0, 0);
    scale = QVector3D(1, 1, 1);
}

void EntityObject::setPosition(float x, float y, float z)
{
    position.setX(x);
    position.setY(y);
    position.setZ(z);
}

void EntityObject::setRotation(QVector3D arg)
{
    rotation = arg;
}

void EntityObject::setRotation(float x, float y, float z)
{
    rotation.setX(x);
    rotation.setY(y);
    rotation.setZ(z);
}

QVector3D EntityObject::getPosition()
{
    return position;
}

QVector3D EntityObject::getRotation()
{
    return rotation;
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
