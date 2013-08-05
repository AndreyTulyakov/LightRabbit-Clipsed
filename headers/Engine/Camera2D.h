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

#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "EntityObject.h"

#include <QMatrix4x4>


class Camera2D : public EntityObject
{
    private:
        QMatrix4x4 projection;
        QMatrix4x4 translation;
        QMatrix4x4 rotation;
        QMatrix4x4 view;
        QMatrix4x4 zoom;
        float zoomFactor;

    public:
        Camera2D();

        float getZoom();
        void setZoom(float pZoom);

        QMatrix4x4 getCameraMatrix();

        void setOrtho(float width, float height, float near, float far, bool LeftTopStart = false);
        void setRotationRoll(float arg);
        void setPosition(float x, float y, float z);

};

#endif // CAMERA2D_H
