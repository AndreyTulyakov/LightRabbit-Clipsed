/*
 * Copyright (C) 2013 Andrey Tulyakov
 * @mail: mhyhre@gmail.com
 *
 * This work is licensed under a Creative Commons
 * Attribution-NonCommercial-NoDerivs 3.0 Unported License.
 * You may obtain a copy of the License at
 *
 *              http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode
 *
 */

#ifndef FORMABOUT_H
#define FORMABOUT_H

#include <QDialog>

namespace Ui
{
class FormAbout;
}

class FormAbout : public QDialog
{
    Q_OBJECT

public:
    explicit FormAbout(QWidget *parent = 0);
    ~FormAbout();

private slots:
    void on_ButtonClose_clicked();

private:
    Ui::FormAbout *ui;
};

#endif // FORMABOUT_H
