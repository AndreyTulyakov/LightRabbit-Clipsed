#include "FormTextureList.h"
#include "ui_FormTextureList.h"
#include <QFileDialog>

FormTextureList::FormTextureList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormTextureList)
{
    ui->setupUi(this);
}

FormTextureList::~FormTextureList()
{
    delete ui;
}

void FormTextureList::on_pushButtonAdd_clicked()
{
    QString selfilter = tr("JPEG (*.jpg *.jpeg)");
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image File"),"",tr("Images (*.png *.jpg *jpeg *.bmp)"),&selfilter,0);

    if(!filename.isNull())
    {
        QImage* image = new QImage(filename);
        QListWidgetImageItem *item = new QListWidgetImageItem(filename,ui->listWidget);
        item->data = image;
        ui->listWidget->addItem(item);
    }
}

void FormTextureList::on_listWidget_clicked(const QModelIndex &index)
{
    QImage* image = ((QListWidgetImageItem*)ui->listWidget->item(index.row()))->data;
    ui->label->setPixmap(QPixmap::fromImage(*image));



    if(image->width() < cw && image->height() < ch)
    {
         ui->label->setFixedSize(image->width(),image->height());
    }
    else
    {
        ui->label->setFixedSize(cw, ch);
    }
}

void FormTextureList::on_pushButtonDelete_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.size()>0)
    {
        delete ((QListWidgetImageItem*)items.at(0))->data;
        delete items.at(0);

        ui->label->setText("NONE");
        ui->label->setFixedSize(cw, ch);
    }
}
