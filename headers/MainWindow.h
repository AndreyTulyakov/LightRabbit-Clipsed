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
#include "FormNewClip.h"

#include "ListWidgetItems.h"

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

    void showInStatusBar(QString msg, int time);

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

    void on_pushButton_AddSprite_clicked();

    void on_EntityListWidget_clicked(const QModelIndex &index);

    void on_button_SaveProperties_clicked();

    void on_comboBoxTextures_currentIndexChanged(int index);

    void on_button_NewRegion_clicked();

    void on_button_RemoveRegion_clicked();

    void on_RegionListWidget_itemChanged(QListWidgetItem *item);

    void on_cb_RegionTexture_currentIndexChanged(const QString &arg1);

    void on_RegionListWidget_clicked(const QModelIndex &index);


private:

    QListWidgetItem *getSelectedItem(QListWidget* wList);
    void spritePropertiesToEditPanel(Entity::Sprite *spr);
    void spritePropertiesFromEditPanel(Entity::Sprite *spr);

    void updatedRegionListWidget(bool GrabPanel);
    void regionPropertiesToPanel(ListWidgetRegion *regionItem);
    void regionPropertiesFromPanel(ListWidgetRegion *regionItem);

    void textureListWidgetChanged();

    QString fileExtension;
    QString fileExtMask;

    Ui::MainWindow *ui;
    QApplication *application;

    GLWidget *glWidget;
    QList<TextureAtlas*> Atlases;

};



#endif // MAINWINDOW_H
