#include "TextureAtlas.h"

#include <QImage>
#include <qdebug.h>

TextureAtlas::TextureAtlas(QString filename, QGLContext* context)
{
    filename = "res/textures/" + filename;

    glEnable(GL_TEXTURE_2D);

    QImage image = QImage(filename);

    mWidth = image.width();
    mHeight = image.height();

    mTextureID = context->bindTexture(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

TextureAtlas::TextureAtlas(QImage* image, QGLContext* context)
{
    glEnable(GL_TEXTURE_2D);

    mWidth = image->width();
    mHeight = image->height();

    mTextureID = context->bindTexture(*image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}



int TextureAtlas::textureID()
{
    return mTextureID;
}

int TextureAtlas::width()
{
    return mWidth;
}

int TextureAtlas::height()
{
    return mHeight;
}
