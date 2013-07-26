#ifndef ENTITY_H
#define ENTITY_H

#include <QVector3D>

class Entity
{
    private:
        QVector3D position;
        QVector3D rotation;


    public:
        Entity();

        void setPosition(float x, float y, float z);
        void setX(float arg);
        void setY(float arg);
        void setZ(float arg);

        void setRotation(float x, float y, float z);
        void setPitch(float arg);
        void setYaw(float arg);
        void setRoll(float arg);

        QVector3D getPosition();
        float getX();
        float getY();
        float getZ();

        QVector3D getRotation();
        float getPitch();
        float getYaw();
        float getRoll();

};

#endif // ENTITY_H
