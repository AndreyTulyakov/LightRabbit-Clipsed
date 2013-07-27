#ifndef ENTITYLINE_H
#define ENTITYLINE_H

#include <QGLFunctions>
#include "DrawableEntity.h"


namespace Entity
{



class Line : public DrawableEntity , QGLFunctions
{
public:
    Line(float x1, float y1, float x2, float y2);
    virtual ~Line();

    void init();
    void update();
    void draw();

private:

    void initGeometry();
    GLuint vboIds[2];
    QPoint p1, p2;
};

}

#endif // ENTITYLINE_H
