#include "entityline.h"

#include "defaultshaders.h"
#include "VertexTypes.h"

EntityLine::EntityLine()
{
    shaderProgram = DefaultShaders::getInstance()->getShader("SimpleTextured");

    initializeGLFunctions();

    glGenBuffers(2, vboIds);

    initCubeGeometry();
}

EntityLine::~EntityLine()
{
    glDeleteBuffers(2, vboIds);
}

void EntityLine::update()
{

}

static float rotator = 0;

void EntityLine::draw()
{
    shaderProgram->setUniformValue("texture", 0);

    rotator += 1.0f;
    if (rotator > 360) rotator = 0;

    transform.setToIdentity();
    transform.translate(100.0, 100.0, 0.0);
    transform.scale(100, 100, 1);
    transform.rotate(rotator, 0, 0, 1.0f);

    // Set modelview-projection matrix
    shaderProgram->setUniformValue("mvp_matrix", camera->getCameraMatrix() * transform);

    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);

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

    // Draw from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
}


void EntityLine::initCubeGeometry()
{

    VertexData vertices[] = {
        {QVector3D(-1.0, -1.0,  0.0), QVector2D(0.0, 0.0)},  // v0
        {QVector3D(1.0, -1.0,  0.0),  QVector2D(1.0, 0.0)},  // v1
        {QVector3D(-1.0,  1.0,  0.0), QVector2D(0.0, 1.0)},  // v2
        {QVector3D(1.0,  1.0,  0.0),  QVector2D(1.0, 1.0)},  // v3
    };

    GLushort indices[] = {
        0,  1,  2,  3,  3
    };

    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexData), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 5 * sizeof(GLushort), indices, GL_STATIC_DRAW);
}

