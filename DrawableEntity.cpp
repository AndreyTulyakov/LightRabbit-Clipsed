#include "DrawableEntity.h"

DrawableEntity::DrawableEntity()
{
    isTransformed = true;
    camera = 0;
    shaderProgram = 0;
    transform.setToIdentity();
}

void DrawableEntity::setCamera(Camera2D *arg)
{
    camera = arg;
}
