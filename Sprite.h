#ifndef SPRITE_H
#define SPRITE_H

#include <QGLFunctions>
#include "DrawableEntity.h"


namespace Entity
{


class Sprite : public DrawableEntity , QGLFunctions
{
public:
    Sprite(float w, float h);
    virtual ~Sprite();

    void init();

private:
    void initGeometry();
    GLuint vboIds[2];
    float width, height;

public:
    void update();
    void draw();
};


}

#endif // ENTITYLINE_H
