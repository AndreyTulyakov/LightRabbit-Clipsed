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

#ifndef SCENE_H
#define SCENE_H

#include "SceneObject.h"
#include "Camera2D.h"

class Scene : public SceneObject
{
    public:
        Scene();

        void setCamera(Camera2D *arg);
        void draw();
        void update();

    private:
        Camera2D *camera;
};

#endif // SCENE_H
