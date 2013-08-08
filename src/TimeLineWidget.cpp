#include "headers/TimeLineWidget.h"
#include "ui_TimeLineWidget.h"

TimeLineWidget::TimeLineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeLineWidget)
{
    ui->setupUi(this);

    timeMax = 5000;
    cellWidth = 12;

    stop();

    setTimeStep(50);

    this->setMinimumWidth( (timeMax/timeStep) * cellWidth + 1);

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start();

}

TimeLineWidget::~TimeLineWidget()
{
    delete ui;
}

void TimeLineWidget::setTimeStep(int msec)
{
    timeStep = 50;
    timer.setInterval(timeStep);
}

void TimeLineWidget::play()
{
    playing = true;
    timer.stop();
    timer.start();
}

void TimeLineWidget::stop()
{
    currentTime = 0;
    playing = false;
}

void TimeLineWidget::pause()
{
    playing = false;
}

void TimeLineWidget::nextFrame()
{
    currentTime += timeStep;
    if(currentTime >= timeMax)
        currentTime = 0;
}

void TimeLineWidget::prevFrame()
{
    currentTime -= timeStep;
    if(currentTime < 0)
        currentTime = timeMax-1;
}

int TimeLineWidget::getCurrentTime()
{
    return currentTime;
}

void TimeLineWidget::paintEvent(QPaintEvent *event)
{
        QColor backColor(192, 192, 255);
        QColor minuteColor(32, 32, 128, 255);
        QColor color3(0, 0, 0);
        QColor color4(0,0,0,32);


        QPainter painter(this);

        painter.setPen(backColor);
        painter.drawRect(QRect(0, 0, width(), height()));

        painter.setBrush(color4);
        painter.setPen(color4);
        int curPos = (currentTime/timeStep)*cellWidth;
        painter.drawRect(QRect(curPos, 0, cellWidth, height()));

        painter.setPen(color3);
        painter.drawLine(0, 10, timeMax / 2, 10);

        painter.setPen(minuteColor);

        for (int j = 0; j <= timeMax; j+=timeStep)
        {
            int i = (j/timeStep)*cellWidth;

            if ((j % 1000) == 0)
            {
                painter.drawLine( i, 0, i, 40);
            }
            else
            {
                if ((j % 500) == 0)
                    painter.drawLine( i, 0, i, 20);
                else
                    painter.drawLine( i, 0, i, 10);
            }

        }

        if(playing)
        {
            currentTime += timeStep;
        }
        if(currentTime >= timeMax)
            currentTime = 0;
}
