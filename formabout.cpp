#include "formabout.h"
#include "ui_formabout.h"

FormAbout::FormAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormAbout)
{
    ui->setupUi(this);
}

FormAbout::~FormAbout()
{
    delete ui;
}

void FormAbout::on_ButtonClose_clicked()
{
    this->close();
}
