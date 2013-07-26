#include "entity.h"

Entity::Entity()
{
}

void Entity::setPosition(float x, float y, float z)
{
    position.setX(x);
    position.setY(y);
    position.setZ(z);
}

void Entity::setX(float arg)
{
    position.setX(arg);
}

void Entity::setY(float arg)
{
    position.setY(arg);
}

void Entity::setZ(float arg)
{
    position.setZ(arg);
}

void Entity::setRotation(float x, float y, float z)
{
    rotation.setX(x);
    rotation.setY(y);
    rotation.setZ(z);
}

void Entity::setPitch(float arg)
{
    rotation.setX(arg);
}

void Entity::setYaw(float arg)
{
    rotation.setY(arg);
}

void Entity::setRoll(float arg)
{
    rotation.setZ(arg);
}



QVector3D Entity::getPosition()
{
    return position;
}

float Entity::getX()
{
    return position.x();
}

float Entity::getY()
{
    return position.y();
}

float Entity::getZ()
{
    return position.z();
}

QVector3D Entity::getRotation()
{
    return rotation;
}

float Entity::getPitch()
{
    return rotation.x();
}

float Entity::getYaw()
{
    return rotation.y();
}

float Entity::getRoll()
{
    return rotation.z();
}
