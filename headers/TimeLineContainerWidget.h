#ifndef TIMELINECONTAINERWIDGET_H
#define TIMELINECONTAINERWIDGET_H

#include <QWidget>
#include "TimeLineWidget.h"

namespace Ui {
class TimeLineContainerWidget;
}

class TimeLineContainerWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimeLineContainerWidget(QWidget *parent = 0);
    ~TimeLineContainerWidget();

    TimeLineWidget *getTimeline();
    
private slots:
    void on_play_clicked();

    void on_pause_clicked();

    void on_stop_clicked();

    void on_prevFrame_clicked();

    void on_nextFrame_clicked();

    void timeoutSlot();

    void on_setting_clicked();

private:
    Ui::TimeLineContainerWidget *ui;

protected:
    TimeLineWidget* timeline;
    QTimer* timer;

};

#endif // TIMELINECONTAINERWIDGET_H
