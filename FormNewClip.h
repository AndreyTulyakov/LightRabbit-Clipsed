#ifndef FORMNEWCLIP_H
#define FORMNEWCLIP_H

#include <QDialog>
#include <QVector4D>

struct ClipInfo
{
    ClipInfo()
    {
        Width = 400;
        Height = 300;
        Color = QVector4D(0.5f, 0.5f, 0.5f ,1);
        EnabledColor = false;
    }

    int Width;
    int Height;
    bool EnabledColor;
    QVector4D Color;
};

namespace Ui {
class FormNewClip;
}

class FormNewClip : public QDialog
{
    Q_OBJECT
    
public:
    explicit FormNewClip(QWidget *parent = 0);
    ~FormNewClip();

    ClipInfo getInfo();
    
private slots:
    void on_buttonSetColor_clicked();

    void on_checkColor_toggled(bool checked);

private:
    Ui::FormNewClip *ui;

    QColor color;
};

#endif // FORMNEWCLIP_H
