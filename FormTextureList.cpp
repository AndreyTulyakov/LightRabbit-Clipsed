#include "FormTextureList.h"
#include "ui_FormTextureList.h"

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
