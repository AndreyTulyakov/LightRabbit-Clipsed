#include "headers/TimeLineWidget.h"
#include "ui_TimeLineWidget.h"

TimeLineWidget::TimeLineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeLineWidget)
{
    ui->setupUi(this);
}

TimeLineWidget::~TimeLineWidget()
{
    delete ui;
}
