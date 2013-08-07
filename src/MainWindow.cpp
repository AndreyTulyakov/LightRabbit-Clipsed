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

    fileExtension = ".lrclip";
    fileExtMask = "LRabbit Clips (*" + fileExtension + ")";

    ui->ListTabs->setVisible(false);
    ui->tabProperty->setVisible(false);

}

void MainWindow::startGLWidget(ClipInfo pInfo)
{
    killGLWidget();

    glWidget = new GLWidget(this, "Main");

    glWidget->setClipInfo(pInfo);
    QGLFormat base_format = glWidget->format();
    base_format.setProfile(QGLFormat::CoreProfile);
    glWidget->setFormat(base_format);
    glWidget->setMinimumWidth(400);
    glWidget->setMinimumHeight(240);

    ui->gridLayout->addWidget(glWidget);

    ui->ListTabs->setVisible(true);
    ui->tabProperty->setVisible(true);
    ui->actionBackgroundColor->setEnabled(true);

    ui->actionNew->setEnabled(false);
    ui->actionOpen->setEnabled(false);

    this->statusBar()->showMessage("Started GLWidget", 2000);

    on_ListTabs_currentChanged(ui->ListTabs->currentIndex());
    ui->cb_TextureSelector->clear();
    ui->cb_TextureSelector->addItem("None");
    ui->tabProperty->setVisible(false);
}

void MainWindow::killGLWidget()
{
    if (glWidget != nullptr)
    {
        ui->gridLayout->removeWidget(glWidget);
        delete glWidget;
        glWidget = nullptr;
    }

    ui->ListTabs->setVisible(false);
    ui->tabProperty->setVisible(false);
    ui->actionBackgroundColor->setEnabled(false);

    ui->actionNew->setEnabled(true);
    ui->actionOpen->setEnabled(true);
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
        ui->statusBar->showMessage("Saved " + filename, 2000);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open clip file"), "", fileExtMask, 0);

    if (!filename.isNull())
    {
        ui->statusBar->showMessage("Opened " + filename, 2000);
        //
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

static int EntityCounter = 0;

void MainWindow::on_AddSprite_clicked()
{
    Entity::Sprite *spr = new Entity::Sprite();
    ListWidgetEntity *lwe = new ListWidgetEntity( QString("sprite_") + QString::number(EntityCounter++), ui->EntityListWidget, EntityType::Sprite, spr);
    ui->EntityListWidget->addItem(lwe);
    glWidget->attachToRootScene(spr);
    onEntityListChanged();
}

void MainWindow::on_AddText_clicked()
{
    QFont *font = new QFont("times");
    Entity::Text *text = new Entity::Text(font);
    ListWidgetEntity *lwe = new ListWidgetEntity( QString("text_") + QString::number(EntityCounter++), ui->EntityListWidget, EntityType::Text, text);
    ui->EntityListWidget->addItem(lwe);
    glWidget->attachToRootScene(text);
    onEntityListChanged();
}

void MainWindow::on_AddSound_clicked()
{
    Entity::Sound* snd = new Entity::Sound();
    ListWidgetEntity *lwe = new ListWidgetEntity( QString("sound_") + QString::number(EntityCounter++), ui->EntityListWidget, EntityType::Sound, snd);
    ui->EntityListWidget->addItem(lwe);
    onEntityListChanged();
}

void MainWindow::showEntityProperties(ListWidgetEntity *lwe)
{
    if(lwe != 0)
    {
         ui->tabProperty->setVisible(true);

        switch(lwe->type)
        {
        case EntityType::Undefined: break;

        case EntityType::Sprite:
        {
            ui->tabProperty->setCurrentIndex(0);
            ui->tab_EditSprite->show();
            ui->tab_EditText->hide();
            ui->tab_EditSound->hide();

            ui->editSpriteName->setText(lwe->text());
            break;
        }

        case EntityType::Text:
        {
            ui->tabProperty->setCurrentIndex(1);
            ui->tab_EditSprite->hide();
            ui->tab_EditText->show();
            ui->tab_EditSound->hide();
            break;
        }

        case EntityType::Sound:
        {
            ui->tabProperty->setCurrentIndex(2);
            ui->tab_EditSprite->hide();
            ui->tab_EditText->hide();
            ui->tab_EditSound->show();
            break;
        }

        }
    }
    else
    {
        ui->tabProperty->setVisible(false);
    }

}

void MainWindow::grabEntityProperties(ListWidgetEntity *arg)
{

}

void MainWindow::onEntityListChanged()
{
    ListWidgetEntity *lwe = (ListWidgetEntity *)getSelectedItem(ui->EntityListWidget);
    showEntityProperties(lwe);
}


void MainWindow::on_RemoveEntity_clicked()
{
    ListWidgetEntity *lwe = (ListWidgetEntity *)getSelectedItem(ui->EntityListWidget);

    if(lwe != 0)
    {
        switch(lwe->type)
        {
        case EntityType::Undefined:
            qDebug() << "Remove undefined entity!";
            break;

        case EntityType::Sprite:
        {
            Entity::Sprite *spr = (Entity::Sprite*)lwe->data;
            glWidget->detachFromRootScene(spr);
            delete spr;
            break;
        }

        case EntityType::Text:
        {
            Entity::Text* text = (Entity::Text*)lwe->data;
            glWidget->detachFromRootScene(text);
            delete text;
            break;
        }

        case EntityType::Sound:
            delete (Entity::Sound*)lwe->data;
            break;
        }

        delete lwe;
    }
    onEntityListChanged();
}


void MainWindow::on_EntityListWidget_clicked(const QModelIndex &index)
{
    ListWidgetEntity *lwe = (ListWidgetEntity *)ui->EntityListWidget->item(index.row());
    showEntityProperties(lwe);
}

void MainWindow::on_button_SaveProperties_clicked()
{
    ListWidgetEntity *lwe = ((ListWidgetEntity *)getSelectedItem(ui->EntityListWidget));
    if (lwe != 0)
    {
        lwe->setText(ui->editSpriteName->text());
        Entity::Sprite *spr = (Entity::Sprite *)lwe->data;
        spritePropertiesFromEditPanel(spr);
    }
}


// TEXTURES CODE

void MainWindow::on_pushButton_AddTexture_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image File"), "", tr("Images (*.png *.jpg *jpeg *.bmp)"));

    if (!filename.isNull())
    {
        ListWidgetTextureAtlas *item = new ListWidgetTextureAtlas(filename, ui->TextureListWidget);
        ui->TextureListWidget->addItem(item);
        ui->TextureListWidget->setCurrentItem(item);

        on_listWidgetTextures_itemSelectionChanged();
    }
}

void MainWindow::on_pushButton_RemoveTexture_clicked()
{
    QList<QListWidgetItem *> items = ui->TextureListWidget->selectedItems();
    if (items.size() > 0)
    {
        glWidget->showTextureSprite(0);
        delete items.at(0);
        on_listWidgetTextures_itemSelectionChanged();
    }
}

void MainWindow::on_listWidgetTextures_clicked(const QModelIndex &index)
{
    on_listWidgetTextures_itemSelectionChanged();
}

void MainWindow::on_listWidgetTextures_itemSelectionChanged()
{
    ui->cb_TextureSelector->clear();
    ui->cb_TextureSelector->addItem("None");
    for(int i=0; i<ui->TextureListWidget->count(); i++)
    {
        ui->cb_TextureSelector->addItem(ui->TextureListWidget->item(i)->text());
    }

    QListWidgetItem *lwe = getSelectedItem(ui->TextureListWidget);

    if (lwe != 0)
    {
        TextureAtlas *texture = ((ListWidgetTextureAtlas *)lwe)->getAtlas();
        glWidget->showTextureSprite(texture);
    }
    else
    {
        glWidget->showTextureSprite(0);
    }

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
    ListWidgetEntity *lwe = ((ListWidgetEntity *)getSelectedItem(ui->EntityListWidget));
    ListWidgetTextureAtlas *lita = (ListWidgetTextureAtlas *)ui->TextureListWidget->item(index);

    if (lwe != 0)
    {
        Entity::Sprite *spr = (Entity::Sprite *)lwe->data;
        TextureAtlas *atlas = (TextureAtlas *)lita->getAtlas();
        spr->setAtlas(atlas);
    }
}


void MainWindow::on_ListTabs_currentChanged(int index)
{
    qDebug() << "Switched tab:" << QString::number(index);

    if(index == 0)
    {
        glWidget->mode = GLWidgetMode::ClipEdit;
        return;
    }

    if(index == 1)
    {
        glWidget->centerTexCamera();
        glWidget->mode = GLWidgetMode::TextureList;
        return;
    }

    if(index == 2)
    {
        glWidget->centerTexCamera();
        glWidget->mode = GLWidgetMode::SoundList;
        return;
    }
}

void MainWindow::on_actionBackgroundColor_triggered()
{
    if(glWidget != 0 && glWidget != nullptr)
    {
        QColor c = QColorDialog::getColor(glWidget->getBackgroundColor(), this);
        if(c.isValid())
        {
            glWidget->setBackgroundColor(c);
        }
    }
}
