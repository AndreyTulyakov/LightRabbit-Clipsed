#include "DrawableEntity.h"

void DrawableEntity::createVertexBuffer(const void *data, int count)
{
    vertexBuffer = new QGLBuffer(QGLBuffer::VertexBuffer);
    vertexBuffer->create();
    vertexBuffer->bind();
    vertexBuffer->allocate(data, count);
}

void DrawableEntity::createVertexBuffer(int count)
{
    vertexBuffer = new QGLBuffer(QGLBuffer::VertexBuffer);
    vertexBuffer->create();
    vertexBuffer->bind();
    vertexBuffer->allocate(count);
}

DrawableEntity::DrawableEntity()
{
    isTransformed = true;
    camera = 0;
    shaderProgram = 0;
    color = QVector4D(1, 1, 1, 1);
    transform.setToIdentity();
    vertexBuffer = 0;
}

DrawableEntity::~DrawableEntity()
{
    if (vertexBuffer != 0)
    {
        if (vertexBuffer->isCreated())
        {
            vertexBuffer->destroy();
        }
        delete vertexBuffer;
    }
}

void DrawableEntity::setCamera(Camera2D *arg)
{
    camera = arg;
}

void DrawableEntity::setColor(QVector4D arg)
{
    color = arg;
}

void DrawableEntity::setColor(float r, float g, float b, float a)
{
    color = QVector4D(r, g, b, a);
}

QVector4D DrawableEntity::getColor()
{
    return color;
}
