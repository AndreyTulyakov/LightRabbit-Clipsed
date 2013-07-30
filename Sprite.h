#ifndef SPRITE_H
#define SPRITE_H

#include <QGLFunctions>
#include "DrawableEntity.h"
#include "TextureAtlas.h"
#include "TextureRegion.h"
#include <QGLBuffer>


namespace Entity
{


class Sprite : public DrawableEntity , QGLFunctions
{
public:
    Sprite(TextureAtlas* pAtlas);
    Sprite(TextureRegion* pRegion);

    virtual ~Sprite();

    void init();
    void update();
    void draw();

private:
    void initGeometry();
    float width, height;
    TextureAtlas* atlas;
    QGLBuffer *vertexBuffer;
};


}

#endif // ENTITYLINE_H
