#include "DrawableEntity.h"

DrawableEntity::DrawableEntity()
{
    isTransformed = true;
    camera = 0;
    shaderProgram = 0;
    color = QVector4D(1,1,1,1);
    transform.setToIdentity();
}

void DrawableEntity::setCamera(Camera2D *arg)
{
    camera = arg;
}
