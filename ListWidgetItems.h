#ifndef LISTWIDGETITEMS_H
#define LISTWIDGETITEMS_H

#include <QListWidgetItem>

enum EntityType
{
    Undefined, Sprite, Text, Sound
};

class ListItemTextureAtlas : public QListWidgetItem
{
public:
    ListItemTextureAtlas(QString name, QListWidget* view)  : QListWidgetItem(name, view)
    {
        data = 0;
    }

    TextureAtlas* data;
};

class ListWidgetEntity : public QListWidgetItem
{
public:
    ListWidgetEntity(QString name, QListWidget* view, EntityType pType)  : QListWidgetItem(name, view)
    {
        data = 0;
        type = pType;
    }

    ListWidgetEntity(QString name, QListWidget* view, EntityType pType, void* pData)  : QListWidgetItem(name, view)
    {
        data = 0;
        type = pType;
        data = pData;
    }

    void* data;
    EntityType type;
};


#endif // LISTWIDGETITEMS_H
