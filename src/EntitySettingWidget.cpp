#include "headers/EntitySettingWidget.h"
#include "ui_EntitySettingWidget.h"

EntitySettingWidget::EntitySettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntitySettingWidget)
{
    ui->setupUi(this);

    currentEntity = nullptr;

    this->hide();

    QPalette pal;
    pal.setColor(QPalette::Background, QColor(200,200,220));
    pal.setColor(QPalette::WindowText, Qt::black);
    this->setPalette(pal);

    connect(ui->spriteName, SIGNAL(textEdited(QString)), this, SLOT(spriteSettingEdited()));
}

EntitySettingWidget::~EntitySettingWidget()
{
    delete ui;
}

void EntitySettingWidget::setEntitySetting(ListWidgetEntity *item)
{
    this->show();

    currentEntity = item;

    switch (item->type)
    {
        case Sprite:
            ui->stackedProperties->setCurrentIndex(0);
            setSpriteSetting(item);
            break;

        case Text:
            this->hide();
            break;

        case Sound:
            this->hide();
            break;

        default:
            break;
    }
}

void EntitySettingWidget::notSelectedEntity()
{
    this->hide();
    currentEntity = nullptr;
}

void EntitySettingWidget::spriteSettingEdited()
{
    Entity::Sprite *sprite = (Entity::Sprite*)currentEntity->data;
    currentEntity->setText(ui->spriteName->text());
}

void EntitySettingWidget::settingUpdated(ListWidgetEntity *item)
{

}

void EntitySettingWidget::setSpriteSetting(ListWidgetEntity *item)
{
    Entity::Sprite *sprite = (Entity::Sprite*)item->data;

    ui->spriteName->setText(item->text());

    ui->spriteLayout->setValue(item->layout);

    ui->sPositionX->setValue(sprite->getPosition().x());
    ui->sPositionY->setValue(sprite->getPosition().y());

    ui->sRotation->setValue(sprite->getRotationZ());

    ui->sScaleX->setValue(sprite->getScale().x());
    ui->sScaleY->setValue(sprite->getScale().y());
}
