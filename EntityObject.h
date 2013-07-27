#ifndef ENTITY_H
#define ENTITY_H

#include <QVector3D>

class EntityObject
{
protected:
    QVector3D position;
    float zRotation;
    QVector3D scale;

public:
    EntityObject();

    void setPosition(float x, float y, float z);
    void setPosition(QVector3D arg);

    void setRotationZ(float z);

    void setScale(float x, float y, float z);
    void setScale(QVector3D arg);

    QVector3D getPosition();
    float getRotationZ();
    QVector3D getScale();
};

#endif // ENTITY_H
