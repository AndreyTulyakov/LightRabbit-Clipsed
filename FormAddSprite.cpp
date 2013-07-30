#include "FormAddSprite.h"
#include "ui_FormAddSprite.h"

FormAddSprite::FormAddSprite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormAddSprite)
{
    ui->setupUi(this);

}

FormAddSprite::~FormAddSprite()
{
    delete ui;
}
