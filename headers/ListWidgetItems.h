#pragma once

#ifndef LISTWIDGETITEMS_H
#define LISTWIDGETITEMS_H

#include <QListWidgetItem>
#include <QFileInfo>

#include "TextureRegion.h"

enum EntityType
{
    Undefined, Sprite, Text, Sound
};

class ListWidgetTextureAtlas : public QListWidgetItem
{
    public:
        ListWidgetTextureAtlas(QString pFilename, QListWidget *view);
        ~ListWidgetTextureAtlas();

        int getIndex();
        TextureAtlas *getAtlas();
        QString getFilename();


    private:
        static int counter;

        TextureAtlas *atlas;
        int index;
        QString filename;
};

class ListWidgetEntity : public QListWidgetItem
{
    public:
        ListWidgetEntity(QString name, QListWidget *view, EntityType pType)  : QListWidgetItem(name, view)
        {
            data = 0;
            type = pType;
            layout = 0;
        }

        ListWidgetEntity(QString name, QListWidget *view, EntityType pType, void *pData)  : QListWidgetItem(name, view)
        {
            data = 0;
            type = pType;
            data = pData;
            layout = 0;
        }

        void *data;
        EntityType type;
        int layout;
};

class ListWidgetRegion : public QListWidgetItem
{
    public:
        ListWidgetRegion(QString name, QListWidget *view)  : QListWidgetItem(name, view)
        {
        }

        TextureRegion region;
        QString textureName;
};


#endif // LISTWIDGETITEMS_H
