#include "ListWidgetItems.h"


int ListWidgetTextureAtlas::counter = 0;


ListWidgetTextureAtlas::ListWidgetTextureAtlas(QString pFilename, QListWidget *view) : QListWidgetItem(pFilename, view)
{
    index = counter;
    counter++;

    QFileInfo fileInfo(pFilename);
    filename = fileInfo.fileName();

    atlas = new TextureAtlas(pFilename, GLWidget::getInstance("Main")->context());

    setText(QString("#") + QString::number(index) + QString(" - ") + filename);
}

ListWidgetTextureAtlas::~ListWidgetTextureAtlas()
{
    delete atlas;
    atlas = 0;
}

int ListWidgetTextureAtlas::getIndex()
{
    return index;
}

TextureAtlas* ListWidgetTextureAtlas::getAtlas()
{
    return atlas;
}

QString ListWidgetTextureAtlas::getFilename()
{
    return filename;
}
