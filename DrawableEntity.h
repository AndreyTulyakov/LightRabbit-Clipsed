#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H

#include "camera2d.h"

class DrawableEntity : public Entity
{
private:
    Camera2D* camera;

public:

    DrawableEntity();
    void setCamera(Camera2D* arg);

    virtual void draw() = 0;
};

#endif // DRAWABLEENTITY_H
