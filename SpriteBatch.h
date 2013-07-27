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
    SpriteBatch(int capacity);
    virtual ~SpriteBatch();

    void init();
    void update();
    void draw();

private:
    void initGeometry();
    GLuint vboIds[2];

    int capacity;
    int used;
};


}

#endif // SPRITEBATCH_H
