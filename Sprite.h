#ifndef SPRITE_H
#define SPRITE_H

#include <QGLFunctions>
#include "DrawableEntity.h"
#include "TextureAtlas.h"

namespace Entity
{


class Sprite : public DrawableEntity , QGLFunctions
{
public:
    Sprite(TextureAtlas* pAtlas);
    virtual ~Sprite();

    void init();

private:
    void initGeometry();
    GLuint vboIds[2];
    float width, height;
    TextureAtlas* atlas;

public:
    void update();
    void draw();
};


}

#endif // ENTITYLINE_H
