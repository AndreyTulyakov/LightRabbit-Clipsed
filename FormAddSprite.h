#ifndef FORMADDSPRITE_H
#define FORMADDSPRITE_H

#include <QDialog>

namespace Ui {
class FormAddSprite;
}

class FormAddSprite : public QDialog
{
    Q_OBJECT
    
public:
    explicit FormAddSprite(QWidget *parent = 0);
    ~FormAddSprite();
    
private:
    Ui::FormAddSprite *ui;
};

#endif // FORMADDSPRITE_H
