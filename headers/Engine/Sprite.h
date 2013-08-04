/*
 * Copyright (C) 2013 Andrey Tulyakov
 * @mail: mhyhre@gmail.com
 *
 * This work is licensed under a Creative Commons
 * Attribution-NonCommercial-NoDerivs 3.0 Unported License.
 * You may obtain a copy of the License at
 *
 *              http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode
 *
 */

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

    Sprite();
    Sprite(TextureAtlas* pAtlas);
    Sprite(TextureRegion* pRegion);

    virtual ~Sprite();

    void setAtlas(TextureAtlas* pAtlas);
    void setRegion(TextureRegion* pRegion);

    void init();
    void update();
    void draw();

private:
    void initGeometry();
    TextureRegion* region;
};


}

#endif // ENTITYLINE_H
