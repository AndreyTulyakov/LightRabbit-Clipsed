#ifndef ENTITYSETTINGWIDGET_H
#define ENTITYSETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class EntitySettingWidget;
}

class EntitySettingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit EntitySettingWidget(QWidget *parent = 0);
    ~EntitySettingWidget();
    
private:
    Ui::EntitySettingWidget *ui;
};

#endif // ENTITYSETTINGWIDGET_H
