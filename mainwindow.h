#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "glwidget.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void setApplication(QApplication *app);

    private slots:
        void on_actionAbout_triggered();

        void on_actionExit_triggered();

    private:
        Ui::MainWindow *ui;
        QApplication *application;

        GLWidget *glWidget;
};

#endif // MAINWINDOW_H
