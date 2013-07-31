#ifndef FORMTEXTURELIST_H
#define FORMTEXTURELIST_H

#include <QDialog>
#include <QImage>
#include <QListWidgetItem>

class QListWidgetImageItem : public QListWidgetItem
{
public:
    QListWidgetImageItem(QString name, QListWidget* view)  : QListWidgetItem(name, view)
    {
        data = 0;
    }

    QImage* data;
};

namespace Ui {
class FormTextureList;
}

class FormTextureList : public QDialog
{
    Q_OBJECT
    
public:
    explicit FormTextureList(QWidget *parent = 0);
    ~FormTextureList();
    
private slots:
    void on_pushButtonAdd_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButtonDelete_clicked();

private:
    Ui::FormTextureList *ui;

    const int cw = 400, ch = 400;
};

#endif // FORMTEXTURELIST_H
