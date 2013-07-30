#include "SpriteBatch.h"

#include "DefaultShaders.h"
#include "VertexTypes.h"

namespace Entity
{


SpriteBatch::SpriteBatch(TextureAtlas *atlas, int capacity)
{
    initializeGLFunctions();

    this->atlas = atlas;
    this->capacity = capacity;
    used = 0;
    nowMapped = false;
    mapedVertices = 0;

    shaderProgram = DefaultShaders::getInstance()->getShader("SpriteBatch");

    initGeometry();
}

SpriteBatch::~SpriteBatch()
{
    indicesBuffer->destroy();
    delete indicesBuffer;
}

void SpriteBatch::update()
{

}

void SpriteBatch::draw()
{
    if (used == 0)
        return;

    shaderProgram->bind();
    vertexBuffer->bind();
    indicesBuffer->bind();


    transform.setToIdentity();

    transform.translate(position);
    transform.rotate(zRotation, 0, 0, 1);
    transform.scale(scale);

    transform = camera->getCameraMatrix() * transform;

    shaderProgram->setUniformValue("mvp_matrix", transform);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, atlas->textureID());
    shaderProgram->setUniformValue("texture", 0);

    quintptr offset = 0;

    // Locate vertex position data
    int vertexLocation = shaderProgram->attributeLocation("a_position");
    shaderProgram->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DTextureColor), (const void *)offset);

    // Offset for texture coordinate
    offset += sizeof(QVector2D);

    // Locate vertex texture coordinate data
    int texcoordLocation = shaderProgram->attributeLocation("a_texcoord");
    shaderProgram->enableAttributeArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DTextureColor), (const void *)offset);

    offset += sizeof(QVector2D);

    // Locate vertex texture coordinate data
    int colorLocation = shaderProgram->attributeLocation("a_color");
    shaderProgram->enableAttributeArray(colorLocation);
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2DTextureColor), (const void *)offset);





    glDrawElements(GL_TRIANGLES, used * 6, GL_UNSIGNED_SHORT, 0);

    shaderProgram->disableAttributeArray(vertexLocation);
    shaderProgram->disableAttributeArray(texcoordLocation);
    shaderProgram->disableAttributeArray(colorLocation);
}

void SpriteBatch::addStart()
{
    used = 0;
    if (!nowMapped) {
        vertexBuffer->bind();
        mapedVertices = (Vertex2DTextureColor*)vertexBuffer->map(QGLBuffer::ReadWrite);
        nowMapped = true;
    }
}



void SpriteBatch::addEnd()
{
    if (nowMapped) {
        vertexBuffer->unmap();
    } else {
        qDebug() << "SpriteBatch::addEnd: try before call :addStart";
    }


    mapedVertices = 0;
    nowMapped = false;
}

void SpriteBatch::addSprite(TextureRegion *texRegion, float x, float y, float scaleX, float scaleY, float rotation, float r, float g, float b, float a)
{
    if (nowMapped) {
        if (used >= capacity) {
            qDebug() << "SpriteBatch::addSprite: max capacity is" << capacity;
        } else {
            float hw = texRegion->getRegion().width() / 2;
            float hh = texRegion->getRegion().height() / 2;

            QRectF reg = texRegion->getAbsRegion();

            int i = used * 4;
            mapedVertices[i + 0] = {QVector2D(-hw, -hh), QVector2D(reg.topLeft()), QVector4D(r, g, b, a)}; // v0
            mapedVertices[i + 1] = {QVector2D(+hw, -hh), QVector2D(reg.topRight()), QVector4D(r, g, b, a)}; // v1
            mapedVertices[i + 2] = {QVector2D(-hw, +hh), QVector2D(reg.bottomLeft()), QVector4D(r, g, b, a)}; // v2
            mapedVertices[i + 3] = {QVector2D(+hw, +hh), QVector2D(reg.bottomRight()), QVector4D(r, g, b, a)}; // v3


            transform.setToIdentity();
            transform.translate(x, y, 0);
            transform.rotate(rotation, 0, 0, 1);
            transform.scale(scaleX, scaleY, 1.0f);

            for (int k = 0; k < 4; k++) {
                QVector4D pos4(mapedVertices[i + k].position, 0, 1);
                pos4 = transform * pos4;
                mapedVertices[i + k].position = QVector2D(pos4.x(), pos4.y());
            }

            used++;
        }
    } else {
        qDebug() << "SpriteBatch::addSprite: try before call :addStart";
    }
}



void SpriteBatch::initGeometry()
{
    GLushort *indices = new GLushort[capacity * 6];

    for (int i = 0; i < capacity; i++) {

        int j = i * 6;
        int k = i * 4;

        GLushort *index = &indices[j];

        index[0] = k + 0;
        index[1] = k + 1;
        index[2] = k + 2;

        index[3] = k + 2;
        index[4] = k + 1;
        index[5] = k + 3;

    }

    createVertexBuffer(capacity * 4 * sizeof(Vertex2DTextureColor));

    indicesBuffer = new QGLBuffer(QGLBuffer::IndexBuffer);
    indicesBuffer->create();
    indicesBuffer->bind();
    indicesBuffer->allocate(indices, capacity * 6 * sizeof(GLushort));
}

}
