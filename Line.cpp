#include "Line.h"

#include "DefaultShaders.h"
#include "VertexTypes.h"

namespace Entity
{

Line::Line(float x1, float y1, float x2, float y2)
{
    initializeGLFunctions();

    shaderProgram = DefaultShaders::getInstance()->getShader("PrimitiveColor");

    p1 = QPoint(x1, y1);
    p2 = QPoint(x2, y2);

    initGeometry();
}

Line::~Line()
{

}

void Line::update()
{

}

void Line::draw()
{
    shaderProgram->bind();
    vertexBuffer->bind();

    transform.setToIdentity();

    transform.translate(position);
    transform.scale(scale);
    transform.rotate(zRotation, 0, 0, 1);


    // Set modelview-projection matrix
    shaderProgram->setUniformValue("mvp_matrix", camera->getCameraMatrix() * transform);
    shaderProgram->setUniformValue("color", color);

    quintptr offset = 0;

    // Locate vertex position data
    int vertexLocation = shaderProgram->attributeLocation("a_position");
    shaderProgram->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DSimple), (const void *)offset);

    // Draw from VBO 1
    glDrawArrays(GL_LINES, 0, 2);
}


void Line::initGeometry()
{
    Vertex2DSimple vertices[] = {
        {QVector2D(p1.x(), p1.y())},  // v0
        {QVector2D(p2.x(), p2.y())},  // v1
    };

    createVertexBuffer(vertices, sizeof(Vertex2DSimple) * 2);
}

}
