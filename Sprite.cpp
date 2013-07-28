#include "Sprite.h"

#include "DefaultShaders.h"
#include "VertexTypes.h"

namespace Entity
{


Sprite::Sprite(float w, float h)
{
    width = w;
    height = h;

    shaderProgram = DefaultShaders::getInstance()->getShader("SimpleTextured");

    initializeGLFunctions();

    glGenBuffers(2, vboIds);

    initGeometry();
}

Sprite::~Sprite()
{
    glDeleteBuffers(2, vboIds);
}

void Sprite::update()
{

}

void Sprite::draw()
{
    shaderProgram->bind();

    transform.setToIdentity();

    transform.translate(position);
    transform.rotate(zRotation,0,0,1);
    transform.scale(scale);

    transform = camera->getCameraMatrix() * transform;

    shaderProgram->setUniformValue("mvp_matrix", transform);
    shaderProgram->setUniformValue("color", color);

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


    glEnable(GL_TEXTURE_2D);
    shaderProgram->setUniformValue("texture", 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    shaderProgram->disableAttributeArray(vertexLocation);
    shaderProgram->disableAttributeArray(texcoordLocation);

}



void Sprite::initGeometry()
{
    float hw = width / 2;
    float hh = height / 2;

    VertexData vertices[4] = {
        {QVector3D(-hw, -hh,  0.0), QVector2D(0.0, 0.0)},  // v0
        {QVector3D(hw, -hh,  0.0), QVector2D(1.0, 0.0)},   // v1
        {QVector3D(-hw,  hh,  0.0), QVector2D(0.0, 1.0)},  // v2
        {QVector3D(hw,  hh,  0.0), QVector2D(1.0, 1.0)},   // v3
    };

    GLushort indices[] = {
        0,  1,  2,  2,  1, 3
    };

    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexData), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), indices, GL_STATIC_DRAW);
}

}
