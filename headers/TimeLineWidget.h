#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QPainter>

namespace Ui {
class TimeLineWidget;
}

class TimeLineWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimeLineWidget(QWidget *parent = 0);
    ~TimeLineWidget();

    void setTimeStep(int msec);
    void play();
    void stop();
    void pause();
    void nextFrame();
    void prevFrame();
    int getCurrentTime();

    

protected:
    void paintEvent(QPaintEvent *event);

    QTimer timer;
    int timeMax;
    int timeStep;
    int cellWidth;

    int currentTime;

    bool playing;

private:
    Ui::TimeLineWidget *ui;
};

#endif // TIMELINEWIDGET_H
