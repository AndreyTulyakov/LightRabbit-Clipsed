#ifndef ENTITYSETTINGWIDGET_H
#define ENTITYSETTINGWIDGET_H

#include <QWidget>
#include "ListWidgetItems.h"

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
    void notSelectedEntity();

signals:
    void onSettingUpdate(ListWidgetEntity* item);

public slots:

    void spriteSettingEdited();
    
private:

    void settingUpdated(ListWidgetEntity* item);

    void setSpriteSetting(ListWidgetEntity *item);

    Ui::EntitySettingWidget *ui;

    ListWidgetEntity* currentEntity;
};

#endif // ENTITYSETTINGWIDGET_H
