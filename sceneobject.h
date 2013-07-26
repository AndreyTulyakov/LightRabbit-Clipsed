#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QList>

class SceneObject
{
private:
    QList<SceneObject *> childs;

public:
    SceneObject();

    void attachChild(SceneObject* arg);
    void detachChild(SceneObject* arg);

    virtual void update() = 0;
};

#endif // SCENEOBJECT_H