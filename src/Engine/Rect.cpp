#include "Rect.h"

#include "DefaultShaders.h"
#include "VertexTypes.h"

namespace Entity
{


Rect::Rect(float x1, float y1, float x2, float y2)
{
    initializeGLFunctions();

    shaderProgram = DefaultShaders::getInstance()->getShader("PrimitiveColor");

    p1 = QPoint(x1, y1);
    p2 = QPoint(x2, y2);

    initGeometry();
}

Rect::~Rect()
{

}

void Rect::update()
{

}

void Rect::draw()
{
    shaderProgram->bind();
    vertexBuffer->bind();

    transform.setToIdentity();

    transform.translate(position);
    transform.scale(scale);
    transform.rotate(zRotation, 0, 0, 1);

    shaderProgram->setUniformValue("mvp_matrix", camera->getCameraMatrix() * transform);
    shaderProgram->setUniformValue("color", color);

    quintptr offset = 0;

    int vertexLocation = shaderProgram->attributeLocation("a_position");
    shaderProgram->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DSimple), (const void *)offset);

    glDrawArrays(GL_LINE_LOOP, 0, 4);
}


void Rect::initGeometry()
{

    Vertex2DSimple vertices[] =
    {
        {QVector2D(p1.x(), p1.y())},
        {QVector2D(p1.x() + p2.x(), p1.y())},
        {QVector2D(p1.x() + p2.x(), p1.y() + p2.y())},
        {QVector2D(p1.x(), p1.y() + p2.y())},
    };

    createVertexBuffer(vertices, 4 * sizeof(Vertex2DSimple));
}





}
