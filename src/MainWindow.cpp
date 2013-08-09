#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

#include <QFileDialog>
#include <QColorDialog>
#include "Text.h"



#include "Sprite.h"
#include "Sound.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    application = 0;
    glWidget = nullptr;
    timelineContainer = nullptr;
    entityManager = nullptr;

    ClipInfo info;
    info.Width = 400;
    info.Height = 300;
    info.Color = QVector4D(0.9f,0.9f,0.9f,1);

    startGLWidget(info);
}

void MainWindow::startGLWidget(ClipInfo pInfo)
{
    killGLWidget();


    entityManager = new EntityManagerWidget(this);
    ui->horizontalLayout->addWidget(entityManager);


    glWidget = new GLWidget(this, "Main");

    glWidget->setClipInfo(pInfo);
    QGLFormat base_format = glWidget->format();
    base_format.setProfile(QGLFormat::CoreProfile);
    glWidget->setFormat(base_format);
    glWidget->setMinimumWidth(400);
    glWidget->setMinimumHeight(240);

    ui->horizontalLayout->addWidget(glWidget);

    ui->actionBackgroundColor->setEnabled(true);

    ui->actionNew->setEnabled(false);
    ui->actionOpen->setEnabled(false);

    timelineContainer = new TimeLineContainerWidget(this);
    ui->verticalLayout->addWidget(timelineContainer);
}

void MainWindow::killGLWidget()
{
    if (glWidget != nullptr)
    {
        ui->gridLayout->removeWidget(glWidget);
        delete glWidget;
        glWidget = nullptr;
    }

    ui->actionBackgroundColor->setEnabled(false);

    ui->actionNew->setEnabled(true);
    ui->actionOpen->setEnabled(true);



    if(timelineContainer != nullptr)
    {
        ui->verticalLayout->removeWidget(timelineContainer);
        delete timelineContainer;
        timelineContainer = nullptr;
    }
}

MainWindow::~MainWindow()
{


    delete ui;
}

void MainWindow::setApplication(QApplication *app)
{
    application = app;
}

void MainWindow::on_actionAbout_triggered()
{
    FormAbout *form = new FormAbout(this);
    form->exec();
    delete form;
}

void MainWindow::on_actionExit_triggered()
{
    application->exit(0);
}

void MainWindow::on_actionNew_triggered()
{
    FormNewClip *formNewClip = new FormNewClip(this);
    ClipInfo info;

    if (formNewClip->exec() == QDialog::Accepted)
    {
        info = formNewClip->getInfo();

        startGLWidget(info);
    }
    delete formNewClip;
}

void MainWindow::on_actionClose_triggered()
{
    if (glWidget != nullptr)
    {
        int button = QMessageBox::question(this, "Alarm!", "Do you want save clip?", QMessageBox::Ok, QMessageBox::Cancel);
        if (button == QMessageBox::Ok)
        {
            on_actionSave_As_triggered();
        }
        killGLWidget();

    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save clip file"), "", fileExtMask, 0);

    if (!filename.isNull())
    {
        if (filename.mid(filename.size() - fileExtension.size()) != fileExtension)
        {
            filename.append(fileExtension);
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open clip file"), "", fileExtMask, 0);

    if (!filename.isNull())
    {

    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 1)
    {
        glWidget->mode = GLWidgetMode::TextureList;
        glWidget->centerTexCamera();
    }

    if (index == 0)
    {
        glWidget->mode = GLWidgetMode::ClipEdit;
    }
}

void MainWindow::spritePropertiesToEditPanel(Entity::Sprite *spr)
{

}

void MainWindow::spritePropertiesFromEditPanel(Entity::Sprite *spr)
{

}

static int EntityCounter = 0;

void MainWindow::on_AddSprite_clicked()
{

}

void MainWindow::on_AddText_clicked()
{

}

void MainWindow::on_AddSound_clicked()
{

}

void MainWindow::showEntityProperties(ListWidgetEntity *lwe)
{


}

void MainWindow::grabEntityProperties(ListWidgetEntity *arg)
{

}

void MainWindow::onEntityListChanged()
{

}


void MainWindow::on_RemoveEntity_clicked()
{

}


void MainWindow::on_EntityListWidget_clicked(const QModelIndex &index)
{

}

void MainWindow::on_button_SaveProperties_clicked()
{

}


// TEXTURES CODE

void MainWindow::on_pushButton_AddTexture_clicked()
{

}

void MainWindow::on_pushButton_RemoveTexture_clicked()
{

}

void MainWindow::on_listWidgetTextures_clicked(const QModelIndex &index)
{
    on_listWidgetTextures_itemSelectionChanged();
}

void MainWindow::on_listWidgetTextures_itemSelectionChanged()
{


}

void MainWindow::on_TextureListWidget_clicked(const QModelIndex &index)
{
    on_listWidgetTextures_itemSelectionChanged();
}

// ----------------------------------------------------------------------------------------

QListWidgetItem *MainWindow::getSelectedItem(QListWidget *wList)
{
    QList<QListWidgetItem *> list = wList->selectedItems();
    if (list.size() > 0)
    {
        return list.at(0);
    }
    return 0;
}

void MainWindow::on_comboBoxTextures_currentIndexChanged(int index)
{

}


void MainWindow::on_ListTabs_currentChanged(int index)
{
    qDebug() << "Switched tab:" << QString::number(index);

    if (index == 0)
    {
        glWidget->mode = GLWidgetMode::ClipEdit;
        return;
    }

    if (index == 1)
    {
        glWidget->centerTexCamera();
        glWidget->mode = GLWidgetMode::TextureList;
        return;
    }

    if (index == 2)
    {
        glWidget->centerTexCamera();
        glWidget->mode = GLWidgetMode::SoundList;
        return;
    }
}

void MainWindow::on_actionBackgroundColor_triggered()
{
    if (glWidget != 0 && glWidget != nullptr)
    {
        QColor c = QColorDialog::getColor(glWidget->getBackgroundColor(), this);
        if (c.isValid())
        {
            glWidget->setBackgroundColor(c);
        }
    }
}
