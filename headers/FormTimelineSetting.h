#ifndef FORMTIMELINESETTING_H
#define FORMTIMELINESETTING_H

#include <QDialog>

namespace Ui {
class FormTimelineSetting;
}

class FormTimelineSetting : public QDialog
{
    Q_OBJECT
    
public:
    explicit FormTimelineSetting(QWidget *parent = 0);
    ~FormTimelineSetting();

    void setTimeLengh(int time);
    void setTimeStep(int time);

    int getTimeLengh();
    int getTimeStep();

private slots:
    void on_timeStep_valueChanged(int arg1);

private:
    Ui::FormTimelineSetting *ui;
};

#endif // FORMTIMELINESETTING_H
