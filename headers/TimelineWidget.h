#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>

namespace Ui {
class TimelineWidget;
}

class TimelineWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimelineWidget(QWidget *parent = 0);
    ~TimelineWidget();
    
private:
    Ui::TimelineWidget *ui;
};

#endif // TIMELINEWIDGET_H
