#include "Scene.h"

#include "DrawableEntity.h"

Scene::Scene()
{
    camera = 0;
}

void Scene::setCamera(Camera2D *arg)
{
    camera = arg;
}

void Scene::draw()
{
    if (camera == 0) {
        qDebug() << "You need set camera for scene before draw!\n";
        return;
    }

    for (int i = 0; i < childs.length(); i++) {

        DrawableEntity* object = dynamic_cast< DrawableEntity* >(childs.at(i));

        if (object) {
            object->setCamera(camera);
            object->draw();
        }
    }
}

void Scene::update()
{
    for (int i = 0; i < childs.length(); i++) {
        childs.at(i)->update();
    }
}
