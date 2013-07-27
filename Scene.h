#ifndef SCENE_H
#define SCENE_H

#include "SceneObject.h"
#include "Camera2D.h"

class Scene : public SceneObject
{
public:
    Scene();

    void setCamera(Camera2D* arg);
    void draw();
    void update();

private:
    Camera2D* camera;
};

#endif // SCENE_H
