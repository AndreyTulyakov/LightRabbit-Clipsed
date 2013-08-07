#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class TimelineWidget;
}

class TimelineWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimelineWidget(QWidget *parent = 0);
    ~TimelineWidget();

protected:
    void paintEvent(QPaintEvent *event);

    QTimer timer;
    
private:
    Ui::TimelineWidget *ui;
};

#endif // TIMELINEWIDGET_H
