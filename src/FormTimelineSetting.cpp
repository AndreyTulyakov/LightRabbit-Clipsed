#include "headers/FormTimelineSetting.h"
#include "ui_FormTimelineSetting.h"

FormTimelineSetting::FormTimelineSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormTimelineSetting)
{
    ui->setupUi(this);
}

FormTimelineSetting::~FormTimelineSetting()
{
    delete ui;
}

void FormTimelineSetting::setTimeLengh(int time)
{
    ui->timeLengh->setValue(time);
}

void FormTimelineSetting::setTimeStep(int time)
{
    ui->timeStep->setValue(time);
}

int FormTimelineSetting::getTimeLengh()
{
    int tl = (ui->timeLengh->value() / ui->timeLengh->minimum()) * ui->timeLengh->minimum();

    return tl/ui->timeStep->value() * ui->timeStep->value();
}

int FormTimelineSetting::getTimeStep()
{
    return (ui->timeStep->value() / ui->timeStep->minimum()) * ui->timeStep->minimum();
}

void FormTimelineSetting::on_timeStep_valueChanged(int arg1)
{
    ui->timeLengh->setMinimum(arg1);
}
