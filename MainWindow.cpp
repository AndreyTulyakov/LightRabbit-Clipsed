#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    application = 0;

    fileExtension = ".lrclip";
    fileExtMask = "LRabbit Clips (*" + fileExtension + ")";

    formTextureList = new FormTextureList(this);

    glWidget = nullptr;

    ui->tabWidget->setVisible(false);

}


void MainWindow::startGLWidget(ClipInfo pInfo)
{
    killGLWidget();

    glWidget = new GLWidget(this);
    glWidget->setClipInfo(pInfo);
    QGLFormat base_format = glWidget->format();
    base_format.setProfile(QGLFormat::CoreProfile);
    glWidget->setFormat(base_format);


    ui->tabWidget->setVisible(true);
    ui->gridLayout->addWidget(glWidget);


    this->statusBar()->showMessage("Started GLWidget", 2000);

}

void MainWindow::killGLWidget()
{
    if(glWidget != nullptr)
    {
        ui->gridLayout->removeWidget(glWidget);
        delete glWidget;
        glWidget = nullptr;
    }

    ui->tabWidget->setVisible(false);
}


MainWindow::~MainWindow()
{
    delete formTextureList;
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

void MainWindow::on_actionAdd_Sprite_triggered()
{
    FormAddSprite *form = new FormAddSprite(this);

    if(form->exec() == QDialog::Accepted)
    {
        ui->statusBar->showMessage("New Sprite Add",1000);
    }

    delete form;
}

void MainWindow::on_actionAdd_Text_triggered()
{

}

void MainWindow::on_actionAdd_Sound_triggered()
{

}

void MainWindow::on_actionTextures_triggered()
{
    formTextureList->exec();
}



void MainWindow::on_actionNew_triggered()
{
    FormNewClip* formNewClip = new FormNewClip(this);
    ClipInfo info;

    if(formNewClip->exec() == QDialog::Accepted)
    {
        info = formNewClip->getInfo();

        startGLWidget(info);
    }

    delete formNewClip;
}

void MainWindow::on_actionClose_triggered()
{
    if(glWidget != nullptr)
    {
        int button = QMessageBox::question(this,"Alarm!","Do you want save clip?",QMessageBox::Ok, QMessageBox::Cancel);
        if(button == QMessageBox::Ok)
        {
            on_actionSave_As_triggered();
        }
        killGLWidget();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save clip file"),"",fileExtMask,0);

    if(!filename.isNull())
    {
        if( filename.mid(filename.size()-fileExtension.size()) != fileExtension)
        {
            filename.append(fileExtension);
        }
        ui->statusBar->showMessage("Saved " + filename, 2000);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open clip file"),"",fileExtMask,0);

    if(!filename.isNull())
    {
        ui->statusBar->showMessage("Opened " + filename, 2000);
    }
}
