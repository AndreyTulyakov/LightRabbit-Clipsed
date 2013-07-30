#ifndef FORMTEXTURELIST_H
#define FORMTEXTURELIST_H

#include <QDialog>

namespace Ui {
class FormTextureList;
}

class FormTextureList : public QDialog
{
    Q_OBJECT
    
public:
    explicit FormTextureList(QWidget *parent = 0);
    ~FormTextureList();
    
private:
    Ui::FormTextureList *ui;
};

#endif // FORMTEXTURELIST_H
