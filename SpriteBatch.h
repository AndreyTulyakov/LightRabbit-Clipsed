#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <QGLFunctions>
#include "DrawableEntity.h"
#include "VertexTypes.h"

namespace Entity
{


class SpriteBatch: public DrawableEntity , QGLFunctions
{
public:
    SpriteBatch(float w, float h);
    virtual ~SpriteBatch();

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

#endif // SPRITEBATCH_H
