#include "headers/EntitySettingWidget.h"
#include "ui_EntitySettingWidget.h"

EntitySettingWidget::EntitySettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntitySettingWidget)
{
    ui->setupUi(this);

    QPalette pal;
    pal.setColor(QPalette::Background, QColor(200,200,220));
    pal.setColor(QPalette::WindowText, Qt::black);
    this->setPalette(pal);
}

EntitySettingWidget::~EntitySettingWidget()
{
    delete ui;
}
