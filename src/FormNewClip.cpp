#include "FormNewClip.h"
#include "ui_FormNewClip.h"


#include <QColorDialog>

FormNewClip::FormNewClip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormNewClip)
{
    ui->setupUi(this);
}

FormNewClip::~FormNewClip()
{
    delete ui;
}

ClipInfo FormNewClip::getInfo()
{
    ClipInfo info;

    info.Width  = ui->spinBoxW->value();
    info.Height = ui->spinBoxH->value();

    if (ui->checkColor->isChecked())
    {
        info.EnabledColor = true;
        info.Color.setX(color.redF());
        info.Color.setY(color.greenF());
        info.Color.setZ(color.blueF());
        info.Color.setW(color.alphaF());
    }

    return info;
}

void FormNewClip::on_buttonSetColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

}

void FormNewClip::on_checkColor_toggled(bool checked)
{
    ui->buttonSetColor->setEnabled(checked);
}
