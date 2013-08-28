#include "Rect.h"

#include "DefaultShaders.h"
#include "VertexTypes.h"

namespace Entity
{


Rect::Rect(float pX, float pY, float pWidth, float pHeight)
{
    initializeGLFunctions();

    shaderProgram = DefaultShaders::getInstance()->getShader("PrimitiveColor");

    setPosition(pX,pY,0);
    size = QVector3D(pWidth, pHeight, 0);

    filledDraw = false;

    initGeometry();
}

Rect::Rect(QVector3D pPosition, QVector3D pSize)
{
    initializeGLFunctions();

    shaderProgram = DefaultShaders::getInstance()->getShader("PrimitiveColor");

    setPosition(pPosition);
    size = pSize;

    filledDraw = false;

    initGeometry();
}

Rect::~Rect()
{

}

void Rect::setFilledDraw(bool arg)
{
    filledDraw = arg;
}

bool Rect::isFilledDraw()
{
    return filledDraw;
}

void Rect::setSize(float pWidth, float pHeight)
{
    size = QVector3D(pWidth,pHeight,0);

    vertexBuffer->bind();
    Vertex2DSimple *data = (Vertex2DSimple *)vertexBuffer->map(QGLBuffer::ReadWrite);

    float hw = size.x() / 2;
    float hh = size.y() / 2;

    data[0].position =  QVector2D(-hw, -hh);
    data[1].position =  QVector2D( hw, -hh);
    data[2].position =  QVector2D( hw,  hh);
    data[3].position =  QVector2D(-hw,  hh);

    vertexBuffer->unmap();
}

void Rect::setSize(QVector3D pSize)
{
    setSize(pSize.x(),pSize.y());
}

void Rect::update()
{

}

void Rect::draw()
{
    if (!visible)
        return;

    shaderProgram->bind();
    vertexBuffer->bind();

    transform.setToIdentity();

    transform.translate(position);
    transform.rotate(zRotation, 0, 0, 1);
    transform.scale(scale);


    shaderProgram->setUniformValue("mvp_matrix", camera->getCameraMatrix() * transform);
    shaderProgram->setUniformValue("color", color);

    quintptr offset = 0;

    int vertexLocation = shaderProgram->attributeLocation("a_position");
    shaderProgram->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DSimple), (const void *)offset);

    if(filledDraw)
    {
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    else
    {
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

}


void Rect::initGeometry()
{
    float hw = size.x() / 2;
    float hh = size.y() / 2;

    Vertex2DSimple vertices[] =
    {
        {QVector2D(-hw,-hh)},
        {QVector2D( hw,-hh)},
        {QVector2D( hw, hh)},
        {QVector2D(-hw, hh)},
    };

    createVertexBuffer(vertices, 4 * sizeof(Vertex2DSimple));
}





}
