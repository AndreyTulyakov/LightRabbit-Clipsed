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
#include <QListWidgetItem>

class QListItemTextureAtlas : public QListWidgetItem
{
public:
    QListItemTextureAtlas(QString name, QListWidget* view)  : QListWidgetItem(name, view)
    {
        data = 0;
    }

    TextureAtlas* data;
};


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
    void killGLWidget();

    void on_actionNew_triggered();

    void on_actionClose_triggered();

    void on_actionSave_As_triggered();

    void on_actionOpen_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_AddTexture_clicked();

    void on_pushButton_RemoveTexture_clicked();

    void on_listWidgetTextures_clicked(const QModelIndex &index);

private:

    QString fileExtension;
    QString fileExtMask;

    Ui::MainWindow *ui;
    QApplication *application;

    FormTextureList *formTextureList;

    GLWidget *glWidget;
    QList<TextureAtlas*> Atlases;

};

#endif // MAINWINDOW_H
