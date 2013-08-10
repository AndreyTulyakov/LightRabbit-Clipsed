#include "headers/EntityManagerWidget.h"
#include "ui_EntityManagerWidget.h"

#include <QMessageBox>
#include <QPalette>

int EntityManagerWidget::EntityCounter = 0;

EntityManagerWidget::EntityManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntityManagerWidget)
{
    ui->setupUi(this);

    QPalette pal;
    pal.setColor(QPalette::Background, QColor(200,200,220));
    pal.setColor(QPalette::WindowText, Qt::black);
    this->setPalette(pal);
}

EntityManagerWidget::~EntityManagerWidget()
{
    delete ui;
}

ListWidgetEntity *EntityManagerWidget::getSelectedItem()
{
    QList<QListWidgetItem *> list = ui->entityList->selectedItems();
    if (list.size() > 0)
    {
        return (ListWidgetEntity *)list.at(0);
    }
    return 0;
}

void EntityManagerWidget::on_addSprite_clicked()
{
    ListWidgetEntity *item = new ListWidgetEntity("Sprite_" + QString::number(EntityCounter) ,ui->entityList,EntityType::Sprite);
    item->data = new Entity::Sprite();
    ui->entityList->addItem(item);
    emit itemAdded(item);

    onUpdatelist();
    EntityCounter ++;
}

void EntityManagerWidget::on_addText_clicked()
{
    ListWidgetEntity *item = new ListWidgetEntity("Text_" + QString::number(EntityCounter) ,ui->entityList,EntityType::Text);
    item->data = new Entity::Text();
    ui->entityList->addItem(item);
    emit itemAdded(item);

    onUpdatelist();
    EntityCounter ++;
}

void EntityManagerWidget::on_addSound_clicked()
{
    ListWidgetEntity *item = new ListWidgetEntity("Sound_" + QString::number(EntityCounter) ,ui->entityList,EntityType::Sound);
    item->data = new Entity::Sound();
    ui->entityList->addItem(item);
    emit itemAdded(item);

    onUpdatelist();
    EntityCounter ++;
}

void EntityManagerWidget::on_editEntity_clicked()
{
    ListWidgetEntity *item = getSelectedItem();
    if(item != 0)
    {
        // TODO: edit item code
    }
}

void EntityManagerWidget::on_removeEntity_clicked()
{
    ListWidgetEntity *item = getSelectedItem();
    if(item != 0)
    {
        emit itemWasRemoved(item);

        switch(item->type)
        {
        case Sprite:
            delete (Entity::Sprite*)item->data;
            break;

        case Text:
            delete (Entity::Text*)item->data;
            break;

        case Sound:
            delete (Entity::Sound*)item->data;
            break;

        default:
            break;
        }

        delete item;
        onUpdatelist();
    }
}

void EntityManagerWidget::on_entityList_clicked(const QModelIndex &index)
{
    onUpdatelist();
}

void EntityManagerWidget::on_entityList_itemChanged(QListWidgetItem *pItem)
{
    onUpdatelist();
}

void EntityManagerWidget::onUpdatelist()
{
    ListWidgetEntity *item = getSelectedItem();
    if(item != 0)
    {
        emit itemSelected(item);
    }
}
