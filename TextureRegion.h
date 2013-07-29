#ifndef TEXTUREREGION_H
#define TEXTUREREGION_H

#include "TextureAtlas.h"

#include <QRect>
#include <QRectF>

class TextureRegion
{
public:
    TextureRegion();
    TextureRegion(TextureAtlas* atlas);
    TextureRegion(TextureAtlas* atlas, float x, float y, float width, float height);

    void setTextureAtlas(TextureAtlas* atlas);
    void setRegion(float x, float y, float width, float height);
    void setRegion(QRect region);

    TextureAtlas* getAtlas();
    QRect getRegion();
    QRectF getAbsRegion(); // in [0-1] coordinates;

private:
    TextureAtlas* atlas;
    QRect region;
};

#endif // TEXTUREREGION_H
