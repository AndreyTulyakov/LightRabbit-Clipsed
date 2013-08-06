#include "SceneObject.h"
#include <QDebug>

SceneObject::SceneObject()
{
    visible = true;
}

SceneObject::~SceneObject()
{

}

void SceneObject::attachChild(SceneObject *arg)
{
    childs << arg;
}

void SceneObject::detachChild(SceneObject *arg)
{
    if (childs.contains(arg))
    {
        childs.removeAt(childs.indexOf(arg));
    }
    else
    {
        qDebug() << "SceneObject::detachChild: detach object not found.\n";
    }
}

int SceneObject::childCount()
{
    return childs.size();
}

bool SceneObject::isVisible()
{
    return visible;
}

void SceneObject::setVisible(bool arg)
{
    visible = arg;
}
