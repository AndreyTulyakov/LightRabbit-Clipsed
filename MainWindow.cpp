#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

#include <QFileDialog>

#include "Sprite.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    application = 0;

    fileExtension = ".lrclip";
    fileExtMask = "LRabbit Clips (*" + fileExtension + ")";

    glWidget = nullptr;

    ui->ListTabs->setVisible(false);
    ui->tabProperty->setVisible(false);
    ui->sa_RegionProperties->setEnabled(false);

}

void MainWindow::startGLWidget(ClipInfo pInfo)
{
    killGLWidget();

    glWidget = new GLWidget(this);
    glWidget->setClipInfo(pInfo);
    QGLFormat base_format = glWidget->format();
    base_format.setProfile(QGLFormat::CoreProfile);
    glWidget->setFormat(base_format);
    glWidget->setMinimumWidth(400);
    glWidget->setMinimumHeight(240);



    ui->gridLayout->addWidget(glWidget);

    ui->ListTabs->setVisible(true);
    ui->tabProperty->setVisible(true);

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

    ui->ListTabs->setVisible(false);
    ui->tabProperty->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setApplication(QApplication *app)
{
    application = app;
}

void MainWindow::showInStatusBar(QString msg, int time)
{
    this->statusBar()->showMessage(msg, time);

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

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
    {
        glWidget->mode = GLWidgetMode::TextureShow;
        glWidget->centerTexCamera();
    }

    if(index == 0)
    {
        glWidget->mode = GLWidgetMode::ClipEdit;
    }
}

void MainWindow::spritePropertiesToEditPanel(Entity::Sprite *spr)
{
    ui->sb_PositionX->setValue(spr->getPosition().x());
    ui->sb_PositionY->setValue(spr->getPosition().y());

    ui->sb_ScaleX->setValue(spr->getScale().x());
    ui->sb_ScaleX->setValue(spr->getScale().y());

    ui->sb_Rotation->setValue(spr->getRotationZ());

    ui->sb_Alpha->setValue(spr->getColor().w());
    ui->sb_ColorR->setValue(spr->getColor().x());
    ui->sb_ColorG->setValue(spr->getColor().y());
    ui->sb_ColorB->setValue(spr->getColor().z());
}

void MainWindow::spritePropertiesFromEditPanel(Entity::Sprite *spr)
{
    spr->setPosition(ui->sb_PositionX->value(), ui->sb_PositionY->value(), 0);
    spr->setScale(ui->sb_ScaleX->value(), ui->sb_ScaleY->value(), 1);
    spr->setRotationZ(ui->sb_Rotation->value());

    spr->setColor(ui->sb_ColorR->value(), ui->sb_ColorG->value(), ui->sb_ColorB->value(), ui->sb_Alpha->value());
}

void MainWindow::on_pushButton_AddSprite_clicked()
{
    Entity::Sprite *spr = new Entity::Sprite();
    ListWidgetEntity *lwe = new ListWidgetEntity("unnamed",ui->EntityListWidget,EntityType::Sprite, spr);
    ui->EntityListWidget->addItem(lwe);
    glWidget->attachToRootScene(spr);
}

void MainWindow::on_EntityListWidget_clicked(const QModelIndex &index)
{
    ListWidgetEntity *lwe = (ListWidgetEntity *)ui->EntityListWidget->item(index.row());


    Entity::Sprite* spr = (Entity::Sprite*)lwe->data;

    ui->editSpriteName->setText(lwe->text());
    spritePropertiesToEditPanel(spr);


}

void MainWindow::on_button_SaveProperties_clicked()
{
    ListWidgetEntity* lwe = ((ListWidgetEntity*)getSelectedItem(ui->EntityListWidget));
    if(lwe != 0)
    {
        lwe->setText(ui->editSpriteName->text());
        Entity::Sprite* spr = (Entity::Sprite*)lwe->data;
        spritePropertiesFromEditPanel(spr);
    }
}
