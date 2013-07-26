#include "sceneobject.h"

#include <QDebug>

SceneObject::SceneObject()
{

}

void SceneObject::attachChild(SceneObject *arg)
{
    childs << arg;
}

void SceneObject::detachChild(SceneObject *arg)
{
    if (childs.contains(arg)) {
        childs.removeAt(childs.indexOf(arg));
    } else {
        qDebug() << "SceneObject::detachChild: detach object not found.\n";
    }
}
