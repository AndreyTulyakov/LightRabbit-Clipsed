#include "DrawableEntity.h"

#ifndef ENTITYLINE_H
#define ENTITYLINE_H

#include <QGLFunctions>

class EntityLine : public DrawableEntity , QGLFunctions
{
public:
    EntityLine(float x1, float y1, float x2, float y2);
    virtual ~EntityLine();

    void init();
    void drawCubeGeometry(QGLShaderProgram *program);

private:


    void initGeometry();
    GLuint vboIds[2];
    QPoint p1, p2;
public:


    void update();
    void draw();
};

#endif // ENTITYLINE_H
