#include "FormNewClip.h"
#include "ui_FormNewClip.h"


#include <QColorDialog>

FormNewClip::FormNewClip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormNewClip)
{
    ui->setupUi(this);

    color.setRgbF(0.75,0.75,0.75);
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

    info.Color.setX(color.redF());
    info.Color.setY(color.greenF());
    info.Color.setZ(color.blueF());
    info.Color.setW(color.alphaF());

    return info;
}

void FormNewClip::on_buttonSetColor_clicked()
{
    QColor c = QColorDialog::getColor(Qt::white, this);
    if(c.isValid())
        color = c;
    else
        color.setRgbF(0.75,0.75,0.75);
}
