/*
 * Copyright (C) 2013 Andrey Tulyakov
 * @mail: mhyhre@gmail.com
 *
 * This work is licensed under a Creative Commons
 * Attribution-NonCommercial-NoDerivs 3.0 Unported License.
 * You may obtain a copy of the License at
 *
 *              http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode
 *
 */

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QList>
#include "EntityObject.h"

class SceneObject : public EntityObject
{
    protected:
        QList<SceneObject *> childs;
        bool visible;

    public:
        SceneObject();
        virtual ~SceneObject();

        void attachChild(SceneObject *arg);
        void detachChild(SceneObject *arg);

        virtual void update() = 0;
        virtual void draw() = 0;

        int childCount();
        bool isVisible();
        void setVisible(bool arg);
};

#endif // SCENEOBJECT_H
