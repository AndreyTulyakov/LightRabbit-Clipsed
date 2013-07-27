#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <QGLFunctions>
#include "DrawableEntity.h"
#include "VertexTypes.h"
#include "TextureAtlas.h"
#include "TextureRegion.h"

namespace Entity
{


class SpriteBatch: public DrawableEntity , QGLFunctions
{
public:
    SpriteBatch(TextureAtlas* atlas, int capacity);
    virtual ~SpriteBatch();

    void init();
    void update();
    void draw();

private:
    void initGeometry();
    GLuint vboIds[2];

    int capacity;
    int used;

    TextureAtlas* atlas;
};


}

#endif // SPRITEBATCH_H
