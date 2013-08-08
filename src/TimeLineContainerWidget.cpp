#include "headers/TimeLineContainerWidget.h"
#include "ui_TimeLineContainerWidget.h"

#include <QPalette>
#include "FormTimelineSetting.h"
#include <QSpacerItem>

TimeLineContainerWidget::TimeLineContainerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeLineContainerWidget)
{
    ui->setupUi(this);

    QSpacerItem *item = ui->horizontalSpacer_2;
    ui->TimelineLayout->removeItem(item);

    timeline = new TimeLineWidget(this);
    ui->TimelineLayout->addWidget(timeline);

    ui->TimelineLayout->addItem(item, 1, 1);

    timer = timeline->getTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutSlot()));


    QPalette *pal = new QPalette();
    pal->setColor(QPalette::Background, QColor(200,200,220));
    pal->setColor(QPalette::WindowText, Qt::black);
    this->setPalette(*pal);

    pal->setColor(QPalette::Background, QColor(128,128,128));
    pal->setColor(QPalette::WindowText, Qt::white);
    ui->scrollAreaWidgetContents->setPalette(*pal);

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Background, Qt::black);
    palette->setColor(QPalette::WindowText, Qt::white);

    ui->lcdCurrentTime->setPalette(*palette);

    palette->setColor(QPalette::WindowText, Qt::cyan);
    ui->lcdCurrentIndex->setPalette(*palette);
}

TimeLineContainerWidget::~TimeLineContainerWidget()
{
    ui->TimelineLayout->removeWidget(timeline);
    delete timeline;
    delete ui;
}

TimeLineWidget *TimeLineContainerWidget::getTimeline()
{
    return timeline;
}

void TimeLineContainerWidget::on_play_clicked()
{
    timeline->play();
}

void TimeLineContainerWidget::on_pause_clicked()
{
    timeline->pause();
}

void TimeLineContainerWidget::on_stop_clicked()
{
    timeline->stop();
}

void TimeLineContainerWidget::on_prevFrame_clicked()
{
    timeline->prevFrame();
}

void TimeLineContainerWidget::on_nextFrame_clicked()
{
    timeline->nextFrame();
}


void TimeLineContainerWidget::timeoutSlot()
{
    ui->lcdCurrentTime->display(timeline->getCurrentTime());
    ui->lcdCurrentIndex->display(timeline->getCurrentIndex());
}

void TimeLineContainerWidget::on_setting_clicked()
{
    FormTimelineSetting *form = new FormTimelineSetting(this);
    form->setTimeLengh(timeline->getTimeLengh());
    form->setTimeStep(timeline->getTimeStep());

    if (form->exec() == QDialog::Accepted)
    {
        timeline->setTimeLengh(form->getTimeLengh());
        timeline->setTimeStep(form->getTimeStep());
    }
    delete form;
}
