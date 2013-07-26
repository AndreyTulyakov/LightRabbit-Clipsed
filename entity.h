#ifndef ENTITY_H
#define ENTITY_H

#include <QVector3D>

class Entity
{
    protected:
        QVector3D position;
        QVector3D rotation;
        QVector3D scale;

    public:
        Entity();

        void setPosition(float x, float y, float z);
        void setRotation(float x, float y, float z);
        void setScale(float x, float y, float z);

        void setPosition(QVector3D arg);
        void setRotation(QVector3D arg);
        void setScale(QVector3D arg);

        QVector3D getPosition();
        QVector3D getRotation();
        QVector3D getScale();


};

#endif // ENTITY_H
