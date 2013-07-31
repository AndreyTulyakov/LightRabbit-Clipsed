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

#include <QMainWindow>
#include "GLWidget.h"
#include "TextureAtlas.h"

#include "FormAbout.h"
#include "FormAddSprite.h"
#include "FormTextureList.h"
#include "FormNewClip.h"

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

    void on_actionAdd_Sprite_triggered();

    void on_actionAdd_Text_triggered();

    void on_actionAdd_Sound_triggered();

    void on_actionTextures_triggered();

    void startGLWidget(ClipInfo pInfo);

    void on_actionNew_triggered();

private:



    Ui::MainWindow *ui;
    QApplication *application;

    FormTextureList *formTextureList;

    GLWidget *glWidget;
    QList<TextureAtlas*> Atlases;

};

#endif // MAINWINDOW_H
