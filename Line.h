#include "DrawableEntity.h"

#ifndef ENTITYLINE_H
#define ENTITYLINE_H

#include <QGLFunctions>

namespace Entity
{



class Line : public DrawableEntity , QGLFunctions
{
public:
    Line(float x1, float y1, float x2, float y2);
    virtual ~Line();

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

}

#endif // ENTITYLINE_H
