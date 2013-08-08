#include "headers/TimeLineContainerWidget.h"
#include "ui_TimeLineContainerWidget.h"

TimeLineContainerWidget::TimeLineContainerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeLineContainerWidget)
{
    ui->setupUi(this);

    timeline = new TimeLineWidget(this);
    ui->TimelineLayout->addWidget(timeline);
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
