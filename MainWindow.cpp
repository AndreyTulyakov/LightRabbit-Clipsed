#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "FormAbout.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    application = 0;

    glWidget = new GLWidget(this);

    QGLFormat base_format = glWidget->format();

    base_format.setProfile(QGLFormat::CoreProfile);
    glWidget->setFormat(base_format);

    ui->verticalLayout->addWidget(glWidget);

    this->statusBar()->showMessage("Started GLWidget", 2000);
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
