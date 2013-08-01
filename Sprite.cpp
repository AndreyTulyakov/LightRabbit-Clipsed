#include "Sprite.h"

#include "DefaultShaders.h"
#include "VertexTypes.h"

namespace Entity
{


Sprite::Sprite()
{
    initializeGLFunctions();

    atlas = 0;
    width = 0;
    height = 0;

    shaderProgram = DefaultShaders::getInstance()->getShader("SimpleTextured");

    initGeometry();
}

Sprite::Sprite(TextureAtlas* pAtlas)
{
    initializeGLFunctions();

    atlas = pAtlas;
    width = atlas->width();
    height = atlas->height();

    shaderProgram = DefaultShaders::getInstance()->getShader("SimpleTextured");

    initGeometry();
}

Sprite::Sprite(TextureRegion *pRegion)
{
    initializeGLFunctions();

    atlas =  pRegion->getAtlas();
    width = pRegion->getRegion().width();
    height =  pRegion->getRegion().height();

    shaderProgram = DefaultShaders::getInstance()->getShader("SimpleTextured");

    initGeometry();
}

Sprite::~Sprite()
{

}

void Sprite::setAtlas(TextureAtlas *pAtlas)
{
    this->atlas = pAtlas;

    if(atlas != 0 || atlas !=nullptr)
    {
        vertexBuffer->bind();
        Vertex2D* data = (Vertex2D*)vertexBuffer->map(QGLBuffer::ReadWrite);

        float hw = atlas->width() /2;
        float hh = atlas->height() /2;

        data[0].position =  QVector2D(-hw, -hh);
        data[1].position =  QVector2D( hw, -hh);
        data[2].position =  QVector2D(-hw,  hh);
        data[3].position =  QVector2D( hw,  hh);

        data[0].texCoord =  QVector2D(0.0, 0.0);
        data[1].texCoord =  QVector2D(1.0, 0.0);
        data[2].texCoord =  QVector2D(0.0, 1.0);
        data[3].texCoord =  QVector2D(1.0, 1.0);

        vertexBuffer->unmap();
    }
}

void Sprite::update()
{

}

void Sprite::draw()
{
    if(atlas == 0)
        return;

    shaderProgram->bind();
    vertexBuffer->bind();

    transform.setToIdentity();

    transform.translate(position);
    transform.rotate(zRotation, 0, 0, 1);
    transform.scale(scale);

    transform = camera->getCameraMatrix() * transform;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, atlas->textureID());
    shaderProgram->setUniformValue("texture", 0);

    shaderProgram->setUniformValue("mvp_matrix", transform);
    shaderProgram->setUniformValue("color", color);

    quintptr offset = 0;

    // Locate vertex position data
    int vertexLocation = shaderProgram->attributeLocation("a_position");
    shaderProgram->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void *)offset);

    // Offset for texture coordinate
    offset += sizeof(QVector2D);

    // Locate vertex texture coordinate data
    int texcoordLocation = shaderProgram->attributeLocation("a_texcoord");
    shaderProgram->enableAttributeArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void *)offset);



    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    shaderProgram->disableAttributeArray(vertexLocation);
    shaderProgram->disableAttributeArray(texcoordLocation);

}




void Sprite::initGeometry()
{
    float hw = width / 2;
    float hh = height / 2;

    Vertex2D vertices[4] = {
        {QVector2D(-hw, -hh), QVector2D(0.0, 0.0)},  // v0
        {QVector2D(hw, -hh), QVector2D(1.0, 0.0)},    // v1
        {QVector2D(-hw,  hh), QVector2D(0.0, 1.0)},  // v2
        {QVector2D(hw,  hh), QVector2D(1.0, 1.0)},    // v3
    };

    vertexBuffer = new QGLBuffer(QGLBuffer::VertexBuffer);
    vertexBuffer->create();
    vertexBuffer->bind();
    vertexBuffer->allocate(vertices, sizeof(Vertex2D) * 4);
}

}
