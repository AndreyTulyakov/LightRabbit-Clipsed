#include "DrawableEntity.h"

DrawableEntity::DrawableEntity()
{
    camera = 0;
    shaderProgram = 0;
}

void DrawableEntity::setCamera(Camera2D *arg)
{
    camera = arg;
}
