#include "headers/EntityManagerWidget.h"
#include "ui_EntityManagerWidget.h"

#include <QPalette>

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
