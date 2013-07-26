#include "DrawableEntity.h"

#ifndef ENTITYLINE_H
#define ENTITYLINE_H

#include <QGLFunctions>

class EntityLine : public DrawableEntity , QGLFunctions
{
public:
    EntityLine();
    virtual ~EntityLine();

    void init();
    void drawCubeGeometry(QGLShaderProgram *program);

private:
    void initCubeGeometry();
    GLuint vboIds[2];

public:
    void update();
    void draw();
};

#endif // ENTITYLINE_H
