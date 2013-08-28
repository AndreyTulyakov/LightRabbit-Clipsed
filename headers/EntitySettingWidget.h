#ifndef ENTITYSETTINGWIDGET_H
#define ENTITYSETTINGWIDGET_H

#include <QWidget>
#include "ListWidgetItems.h"
#include "Sprite.h"

namespace Ui {
class EntitySettingWidget;
}

class EntitySettingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit EntitySettingWidget(QWidget *parent = 0);
    ~EntitySettingWidget();
    void setEntitySetting(ListWidgetEntity* item);

signals:
    void onSettingUpdate(ListWidgetEntity* item);

public slots:

    void spriteSettingEdited();
    void setEntitySetting();
    void notSelectedEntity();


private:

    void settingUpdated(ListWidgetEntity* item);

    void setSpriteSetting(ListWidgetEntity *item);

    Ui::EntitySettingWidget *ui;

    ListWidgetEntity* currentEntity;
};

#endif // ENTITYSETTINGWIDGET_H
