#ifndef RECT_H
#define RECT_H

#include "DrawableEntity.h"
#include <QGLFunctions>

namespace Entity
{

class Rect : public DrawableEntity , QGLFunctions
{

public:
    Rect(float x1, float y1, float x2, float y2);
    virtual ~Rect();

    void init();

    void update();
    void draw();

private:

    void initGeometry();
    QPoint p1, p2;
};

}

#endif // RECT_H
