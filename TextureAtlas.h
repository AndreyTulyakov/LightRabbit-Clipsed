#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <QGLContext>

class TextureAtlas
{
public:
    TextureAtlas(QString filename, QGLContext* context);

    int textureID();
    int width();
    int height();

private:
    int mTextureID;
    int mWidth, mHeight;
};

#endif // TEXTUREATLAS_H
