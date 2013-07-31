#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    application = 0;
    formTextureList = new FormTextureList(this);

    glWidget = nullptr;

}


void MainWindow::startGLWidget(ClipInfo pInfo)
{
    if(glWidget != nullptr)
    {
        ui->gridLayout->removeWidget(glWidget);
        delete glWidget;
        glWidget = nullptr;
    }

    glWidget = new GLWidget(this);
    glWidget->setClipInfo(pInfo);
    QGLFormat base_format = glWidget->format();
    base_format.setProfile(QGLFormat::CoreProfile);
    glWidget->setFormat(base_format);
    ui->gridLayout->addWidget(glWidget);
    this->statusBar()->showMessage("Started GLWidget", 2000);
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
