#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <QGLFunctions>
#include "DrawableEntity.h"
#include "VertexTypes.h"
#include "TextureAtlas.h"
#include "TextureRegion.h"

#include <QGLBuffer>


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

    void addStart();
    void addEnd();
    void addSprite(TextureRegion* region, QVector2D position, QVector2D scale, float rotation, QVector4D color);


private:
    void initGeometry();

    int capacity;
    int used;

    QGLBuffer *vertexBuffer;
    QGLBuffer *indicesBuffer;

    bool nowMapped;
    VertexData* mapedVertices;

    TextureAtlas* atlas;
};


}

#endif // SPRITEBATCH_H
