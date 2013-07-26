#include "entity.h"

Entity::Entity()
{
    position = QVector3D(0,0,0);
    rotation = QVector3D(0,0,0);
    scale = QVector3D(1,1,1);
}

void Entity::setPosition(float x, float y, float z)
{
    position.setX(x);
    position.setY(y);
    position.setZ(z);
}

void Entity::setRotation(QVector3D arg)
{
    rotation = arg;
}

void Entity::setRotation(float x, float y, float z)
{
    rotation.setX(x);
    rotation.setY(y);
    rotation.setZ(z);
}

QVector3D Entity::getPosition()
{
    return position;
}

QVector3D Entity::getRotation()
{
    return rotation;
}

QVector3D Entity::getScale()
{
    return scale;
}

void Entity::setScale(float x, float y, float z)
{
    scale = QVector3D(x,y,z);
}

void Entity::setPosition(QVector3D arg)
{
    position = arg;
}

void Entity::setScale(QVector3D arg)
{
    scale = arg;
}
