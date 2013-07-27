#ifndef TEXTUREREGION_H
#define TEXTUREREGION_H

#include "TextureAtlas.h"

#include <QRect>

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

private:
    TextureAtlas* atlas;
    QRect region;
};

#endif // TEXTUREREGION_H
