#ifndef SCENE_H
#define SCENE_H

#include "sceneobject.h"
#include "camera2d.h"

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
