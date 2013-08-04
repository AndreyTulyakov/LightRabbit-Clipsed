#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

#include <QFileDialog>

#include "Sprite.h"


void MainWindow::on_pushButton_AddTexture_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image File"),"",tr("Images (*.png *.jpg *jpeg *.bmp)"));

    if(!filename.isNull())
    {
        QFileInfo fileInfo(filename);
        TextureAtlas* image = new TextureAtlas(filename, this->glWidget->context());
        ListWidgetTextureAtlas *item = new ListWidgetTextureAtlas(fileInfo.fileName(),ui->TextureListWidget);
        item->data = image;
        ui->TextureListWidget->addItem(item);
        on_listWidgetTextures_itemSelectionChanged();

        textureListWidgetChanged();
    }
}

void MainWindow::on_pushButton_RemoveTexture_clicked()
{
    QList<QListWidgetItem*> items = ui->TextureListWidget->selectedItems();
    if(items.size()>0)
    {
        delete ((ListWidgetTextureAtlas*)items.at(0))->data;
        delete items.at(0);
        glWidget->showTextureSprite( 0 );
        textureListWidgetChanged();
    }
    on_listWidgetTextures_itemSelectionChanged();
}

void MainWindow::on_listWidgetTextures_clicked(const QModelIndex &index)
{
    on_listWidgetTextures_itemSelectionChanged();
}

void MainWindow::on_listWidgetTextures_itemSelectionChanged()
{
    QListWidgetItem* lwe = getSelectedItem(ui->TextureListWidget);

    if(lwe != 0)
    {
        TextureAtlas* texture = ((ListWidgetTextureAtlas*)lwe)->data;
        glWidget->showTextureSprite( texture );
    }

}

QListWidgetItem *MainWindow::getSelectedItem(QListWidget *wList)
{
    QList<QListWidgetItem*> list = wList->selectedItems();
    if(list.size()>0)
    {
        return list.at(0);
    }
    return 0;
}

void MainWindow::on_comboBoxTextures_currentIndexChanged(int index)
{
    ListWidgetEntity* lwe = ((ListWidgetEntity*)getSelectedItem(ui->EntityListWidget));
    ListWidgetTextureAtlas* lita = (ListWidgetTextureAtlas*)ui->TextureListWidget->item(index);

    if(lwe != 0)
    {
        Entity::Sprite* spr = (Entity::Sprite*)lwe->data;
        TextureAtlas* atlas = (TextureAtlas*)lita->data;
        spr->setAtlas(atlas);
    }
}

void MainWindow::textureListWidgetChanged()
{
    ui->cb_RegionTexture->clear();
    for(int i = 0; i < ui->TextureListWidget->count(); i++)
    {
        ui->cb_RegionTexture->addItem(ui->TextureListWidget->item(i)->text());
    }
}
