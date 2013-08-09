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
        void on_actionAbout_triggered();

        void on_actionExit_triggered();


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
        void on_listWidgetTextures_itemSelectionChanged();



        void on_EntityListWidget_clicked(const QModelIndex &index);

        void on_button_SaveProperties_clicked();

        void on_comboBoxTextures_currentIndexChanged(int index);

        void on_ListTabs_currentChanged(int index);

        void on_TextureListWidget_clicked(const QModelIndex &index);

        void on_AddSprite_clicked();
        void on_AddText_clicked();
        void on_AddSound_clicked();
        void on_RemoveEntity_clicked();

        void on_actionBackgroundColor_triggered();

private:

        void showEntityProperties(ListWidgetEntity *arg);
        void grabEntityProperties(ListWidgetEntity *arg);
        void onEntityListChanged();

        QListWidgetItem *getSelectedItem(QListWidget *wList);
        void spritePropertiesToEditPanel(Entity::Sprite *spr);
        void spritePropertiesFromEditPanel(Entity::Sprite *spr);

        void textureListWidgetChanged();

        QString fileExtension;
        QString fileExtMask;

        Ui::MainWindow *ui;
        QApplication *application;

        GLWidget *glWidget;
        TimeLineContainerWidget *timelineContainer;
        EntityManagerWidget *entityManager;


        QList<TextureAtlas *> Atlases;

};



#endif // MAINWINDOW_H
