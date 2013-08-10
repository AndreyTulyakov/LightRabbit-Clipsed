/*
 * Copyright (C) 2013 Andrey Tulyakov
 * @mail: mhyhre@gmail.com
 *
 * This work is licensed under a Creative Commons
 * Attribution-NonCommercial-NoDerivs 3.0 Unported License.
 * You may obtain a copy of the License at
 *
 *              http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>

#include "ui_MainWindow.h"
#include <QMessageBox>

#include <QFileDialog>

#include "Sprite.h"
#include "GLWidget.h"
#include "TextureAtlas.h"
#include "FormAbout.h"
#include "FormNewClip.h"
#include "ListWidgetItems.h"

#include "TimeLineContainerWidget.h"
#include "EntityManagerWidget.h"

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
        void on_actionNew_triggered();
        void on_actionOpen_triggered();
        void on_actionClose_triggered();
        void on_actionSave_As_triggered();
        void on_actionAbout_triggered();
        void on_actionExit_triggered();

        void on_actionBackgroundColor_triggered();

        void entitySelected(ListWidgetEntity* item);
        void entityAdded(ListWidgetEntity* item);
        void entityWasRemoved(ListWidgetEntity* item);

private:

        void startGLWidget(ClipInfo pInfo);
        void killGLWidget();


        Ui::MainWindow *ui;
        QApplication *application;

        // Widgets
        GLWidget *glWidget;
        TimeLineContainerWidget *timelineContainer;
        EntityManagerWidget *entityManager;

        QString fileExtension;
        QString fileExtMask;
};



#endif // MAINWINDOW_H
