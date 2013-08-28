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
    connect(ui->spriteLayout, SIGNAL(valueChanged(int)), this, SLOT(spriteSettingEdited()));

    connect(ui->sPositionX, SIGNAL(valueChanged(double)), this, SLOT(spriteSettingEdited()));
    connect(ui->sPositionY, SIGNAL(valueChanged(double)), this, SLOT(spriteSettingEdited()));

    connect(ui->sRotation, SIGNAL(valueChanged(double)), this, SLOT(spriteSettingEdited()));

    connect(ui->sScaleX, SIGNAL(valueChanged(double)), this, SLOT(spriteSettingEdited()));
    connect(ui->sScaleY, SIGNAL(valueChanged(double)), this, SLOT(spriteSettingEdited()));
}

EntitySettingWidget::~EntitySettingWidget()
{
    delete ui;
}

void EntitySettingWidget::setEntitySetting(ListWidgetEntity *item)
{
    this->show();

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

void EntitySettingWidget::setEntitySetting()
{
    if(currentEntity == nullptr)
        return;

    setSpriteSetting(currentEntity);
}

void EntitySettingWidget::notSelectedEntity()
{
    this->hide();
    currentEntity = nullptr;
}

void EntitySettingWidget::spriteSettingEdited()
{
    if(currentEntity == nullptr)
        return;

    Entity::Sprite *sprite = (Entity::Sprite*)currentEntity->data;
    currentEntity->setText(ui->spriteName->text());
    currentEntity->layout = ui->spriteLayout->value();

    sprite->setPosition(ui->sPositionX->value(), ui->sPositionY->value(), 0);
    sprite->setRotationZ(ui->sRotation->value());
    sprite->setScale(ui->sScaleX->value(), ui->sScaleY->value(), 1);
}

void EntitySettingWidget::settingUpdated(ListWidgetEntity *item)
{

}

void EntitySettingWidget::setSpriteSetting(ListWidgetEntity *item)
{
    currentEntity = nullptr;

    Entity::Sprite *sprite = (Entity::Sprite*)item->data;

    ui->spriteName->setText(item->text());

    ui->spriteLayout->setValue(item->layout);

    ui->sPositionX->setValue(sprite->getPosition().x());
    ui->sPositionY->setValue(sprite->getPosition().y());

    ui->sRotation->setValue(sprite->getRotationZ());

    ui->sScaleX->setValue(sprite->getScale().x());
    ui->sScaleY->setValue(sprite->getScale().y());

    currentEntity = item;
}
