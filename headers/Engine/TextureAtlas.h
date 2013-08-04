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

#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <QGLContext>

class TextureAtlas
{
public:
    TextureAtlas(QString filename, QGLContext* context);
    TextureAtlas(QImage* image, QGLContext* context);

    int textureID();
    int width();
    int height();

private:
    int mTextureID;
    int mWidth, mHeight;
};

#endif // TEXTUREATLAS_H
