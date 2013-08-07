#ifndef TEXT_H
#define TEXT_H

#include "DrawableEntity.h"
#include <QGLFunctions>
#include <QFont>

namespace Entity {

class Text : public DrawableEntity , QGLFunctions
{
public:
    Text(QFont* pFont);

private:
    QFont* font;

    // SceneObject interface
public:
    void update();
    void draw();
};


}


#endif // TEXT_H
