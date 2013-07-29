#include "TextureAtlas.h"

#include <QImage>
#include <qdebug.h>

TextureAtlas::TextureAtlas(QString filename, QGLContext* context)
{
    filename = "res/textures/" + filename;

    glEnable(GL_TEXTURE_2D);

    QImage image = QImage(filename);

    width = image.width();
    height = image.height();

    textureID = context->bindTexture(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
