/*
 * Copyright (C) 2013 Andrey Tulyakov
 * @mail: mhyhre@gmail.com
 *
 * This work is licensed under a Creative Commons
 * Attribution-NonCommercial-NoDerivs 3.0 Unported License.
 * You may obtain a copy of the License at
 *
 *              http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode
 *
 */

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
