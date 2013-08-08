#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>

namespace Ui {
class TimeLineWidget;
}

class TimeLineWidget : public QWidget
{
    Q_OBJECT

    
public:
    explicit TimeLineWidget(QWidget* parent = 0);
    ~TimeLineWidget();


    void play();
    void stop();
    void pause();
    void nextFrame();
    void prevFrame();

    int getCurrentTime();
    int getCurrentIndex();
    int getTimeLengh();
    int getTimeStep();

    void setTimeLengh(int msec);
    void setTimeStep(int msec);
    void setCurrentTime(int msec);

    QTimer* getTimer();

    

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    QTimer timer;
    int timeLengh;
    int timeStep;
    int cellWidth;

    int currentTime;

    bool playing;

private:
    Ui::TimeLineWidget *ui;


};

#endif // TIMELINEWIDGET_H
