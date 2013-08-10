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
    info.Color = QVector4D(0.9f, 0.9f, 0.9f, 1);

    startGLWidget(info);
}

void MainWindow::startGLWidget(ClipInfo pInfo)
{
    killGLWidget();

    {
        entityManager = new EntityManagerWidget(this);
        ui->horizontalLayout->addWidget(entityManager);

        connect(entityManager, SIGNAL(itemAdded(ListWidgetEntity *)), this, SLOT(entityAdded(ListWidgetEntity *)));
        connect(entityManager, SIGNAL(itemSelected(ListWidgetEntity *)), this, SLOT(entitySelected(ListWidgetEntity *)));
        connect(entityManager, SIGNAL(itemWasRemoved(ListWidgetEntity *)), this, SLOT(entityWasRemoved(ListWidgetEntity *)));
    }

    {
        glWidget = new GLWidget(this, "Main");
        glWidget->setClipInfo(pInfo);
        QGLFormat base_format = glWidget->format();
        base_format.setProfile(QGLFormat::CoreProfile);
        glWidget->setFormat(base_format);
        glWidget->setMinimumWidth(400);
        glWidget->setMinimumHeight(240);
        ui->horizontalLayout->addWidget(glWidget);
    }

    {
        timelineContainer = new TimeLineContainerWidget(this);
        ui->verticalLayout->addWidget(timelineContainer);
    }

    ui->actionBackgroundColor->setEnabled(true);

    ui->actionNew->setEnabled(false);
    ui->actionOpen->setEnabled(false);
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



    if (timelineContainer != nullptr)
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

void MainWindow::on_actionBackgroundColor_triggered()
{
    if (glWidget != nullptr)
    {
        QColor c = QColorDialog::getColor(glWidget->getBackgroundColor(), this);
        if (c.isValid())
        {
            glWidget->setBackgroundColor(c);
        }
    }
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


void MainWindow::entitySelected(ListWidgetEntity *item)
{

}

void MainWindow::entityAdded(ListWidgetEntity *item)
{
    switch (item->type)
    {
        case Sprite:
            glWidget->attachToRootScene((Entity::Sprite *)item->data);
            break;

        case Text:
            glWidget->attachToRootScene((Entity::Text *)item->data);
            break;

        case Sound:
            break;

        default:
            break;
    }
}

void MainWindow::entityWasRemoved(ListWidgetEntity *item)
{
    switch (item->type)
    {
        case Sprite:
            glWidget->detachFromRootScene((Entity::Sprite *)item->data);
            break;

        case Text:
            glWidget->detachFromRootScene((Entity::Text *)item->data);
            break;

        case Sound:
            break;

        default:
            break;
    }
}
