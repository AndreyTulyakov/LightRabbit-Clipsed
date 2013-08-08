#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QWidget>

namespace Ui {
class TimeLineWidget;
}

class TimeLineWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimeLineWidget(QWidget *parent = 0);
    ~TimeLineWidget();
    
private:
    Ui::TimeLineWidget *ui;
};

#endif // TIMELINEWIDGET_H
