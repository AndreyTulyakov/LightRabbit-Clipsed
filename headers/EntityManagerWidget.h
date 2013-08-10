#ifndef ENTITYMANAGERWIDGET_H
#define ENTITYMANAGERWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

#include "ListWidgetItems.h"

#include "Sprite.h"
#include "Text.h"
#include "Sound.h"


namespace Ui {
class EntityManagerWidget;
}

class EntityManagerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit EntityManagerWidget(QWidget *parent = 0);
    ~EntityManagerWidget();

    ListWidgetEntity* getSelectedItem();
    
private slots:
    void on_addSprite_clicked();

    void on_addText_clicked();

    void on_addSound_clicked();

    void on_editEntity_clicked();

    void on_removeEntity_clicked();

    void on_entityList_clicked(const QModelIndex &index);

    void on_entityList_itemChanged(QListWidgetItem *item);

    void onUpdatelist();

signals:

    void itemSelected(ListWidgetEntity* selectedItem);
    void itemAdded(ListWidgetEntity* item);
    void itemWasRemoved(ListWidgetEntity* item);

private:
    Ui::EntityManagerWidget *ui;
    static int EntityCounter;
};

#endif // ENTITYMANAGERWIDGET_H
