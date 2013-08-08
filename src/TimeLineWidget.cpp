#include "headers/TimeLineWidget.h"
#include "ui_TimeLineWidget.h"




TimeLineWidget::TimeLineWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TimeLineWidget)
{
    ui->setupUi(this);

    cellWidth = 12;

    setTimeStep(50);
    setTimeLengh(5000);
    stop();

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));

    timer.start();
}

TimeLineWidget::~TimeLineWidget()
{
    delete ui;
}

void TimeLineWidget::setTimeStep(int msec)
{
    if(msec < 1)
        msec = 1;

    timeStep = msec;
    timer.setInterval(timeStep);
    this->setFixedWidth((timeLengh/timeStep) * cellWidth + 1);
}

void TimeLineWidget::setCurrentTime(int msec)
{
    currentTime = (msec/timeStep)*timeStep;
    nextFrame();
    prevFrame();
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
    if(currentTime >= timeLengh)
        currentTime = 0;
}

void TimeLineWidget::prevFrame()
{
    currentTime -= timeStep;
    if(currentTime < 0)
        currentTime = timeLengh-timeStep;
}

int TimeLineWidget::getCurrentTime()
{
    return currentTime;
}

int TimeLineWidget::getCurrentIndex()
{
    return currentTime/timeStep;
}

int TimeLineWidget::getTimeLengh()
{
    return timeLengh;
}

int TimeLineWidget::getTimeStep()
{
    return timeStep;
}

void TimeLineWidget::setTimeLengh(int msec)
{
    timeLengh = msec;
    this->setFixedWidth((timeLengh/timeStep) * cellWidth + 1);
}

QTimer *TimeLineWidget::getTimer()
{
    return &timer;
}

void TimeLineWidget::paintEvent(QPaintEvent *event)
{
        QColor backColor(0, 0, 192, 32);
        QColor minuteColor(32, 32, 128, 255);
        QColor color3(0, 0, 0);
        QColor color4(0,0,0,32);


        QPainter painter(this);

        painter.setBrush(backColor);
        painter.setPen(backColor);
        painter.drawRect(QRect(0, 0, width(), height()));

        painter.setBrush(color4);
        painter.setPen(color4);
        int curPos = (currentTime/timeStep)*cellWidth;
        painter.drawRect(QRect(curPos, 0, cellWidth, height()));

        painter.setPen(color3);
        painter.drawLine(0, 10, timeLengh / 2, 10);

        painter.setPen(minuteColor);

        for (int j = 0; j <= timeLengh; j+=timeStep)
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
        if(currentTime >= timeLengh)
            currentTime = 0;
}

void TimeLineWidget::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
    case Qt::MouseButton::LeftButton:
    {
        int selected = (event->x()-1)/cellWidth;
        setCurrentTime(selected * timeStep);
        break;
    }

    default:
        break;
    }
}

void TimeLineWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Space:
    {
        if(playing)
            pause();
        else
            play();

        break;
    }

    default:
        break;
    }
}
