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

    vertexBuffer = new QGLBuffer(QGLBuffer::VertexBuffer);
    vertexBuffer->create();

    indicesBuffer = new QGLBuffer(QGLBuffer::IndexBuffer);
    indicesBuffer->create();

    shaderProgram = DefaultShaders::getInstance()->getShader("SimpleTextured");

    initGeometry();
}

SpriteBatch::~SpriteBatch()
{
    vertexBuffer->destroy();
    delete vertexBuffer;

    indicesBuffer->destroy();
    delete indicesBuffer;
}

void SpriteBatch::update()
{

}

void SpriteBatch::draw()
{
    shaderProgram->bind();

    transform.setToIdentity();

    transform.translate(position);
    transform.rotate(zRotation, 0,0,1);
    transform.scale(scale);

    transform = camera->getCameraMatrix() * transform;

    shaderProgram->setUniformValue("mvp_matrix", transform);

    vertexBuffer->bind();
    indicesBuffer->bind();

    quintptr offset = 0;

    // Locate vertex position data
    int vertexLocation = shaderProgram->attributeLocation("a_position");
    shaderProgram->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Locate vertex texture coordinate data
    int texcoordLocation = shaderProgram->attributeLocation("a_texcoord");
    shaderProgram->enableAttributeArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);


    glEnable(GL_TEXTURE_2D);
    shaderProgram->setUniformValue("texture", 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    shaderProgram->disableAttributeArray(vertexLocation);
    shaderProgram->disableAttributeArray(texcoordLocation);

}

void SpriteBatch::addStart()
{

    if(!nowMapped){
        //mapedVertices = vertexBuffer->map(QGLBuffer::ReadWrite);
    }
}



void SpriteBatch::addEnd()
{
    if(nowMapped)
    {
        //vertexBuffer->unmap();
    }
    else
    {
        qDebug() << "SpriteBatch::addEnd: try before call :addStart";
    }

    mapedVertices = 0;
    nowMapped = false;
}

void SpriteBatch::addSprite(TextureRegion *region, QVector2D position, QVector2D scale, float rotation, QVector4D color)
{
    if(nowMapped)
    {
        if(used >= capacity)
        {
            qDebug() << "SpriteBatch::addSprite: max capacity!";
        }
        else
        {

        }
    }
    else
    {
        qDebug() << "SpriteBatch::addSprite: try before call :addStart";
    }
}



void SpriteBatch::initGeometry()
{
    float hw = 48;
    float hh = 48;

    VertexData vertices[4] = {
        {QVector3D(-hw, -hh,  0.0), QVector2D(0.0, 0.0)},  // v0
        {QVector3D(hw, -hh,  0.0), QVector2D(1.0, 0.0)},   // v1
        {QVector3D(-hw,  hh,  0.0), QVector2D(0.0, 1.0)},  // v2
        {QVector3D(hw,  hh,  0.0), QVector2D(1.0, 1.0)},   // v3
    };

    GLushort indices[] = {
        0,  1,  2,  2,  1, 3
    };

    vertexBuffer->bind();
    vertexBuffer->allocate(vertices,4 * sizeof(VertexData));

    indicesBuffer->bind();
    indicesBuffer->allocate(indices,6 * sizeof(GLushort));

}

}
