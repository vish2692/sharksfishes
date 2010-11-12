#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include <QDialog>
#include "ui_options.h"
#include "mainwindow.h"

class optionWindow : public QDialog
{
    Q_OBJECT
public:
    explicit optionWindow(MainWindow *parent = 0);

signals:

public slots:
    void on_buttonBox_accepted();

private:
    Ui::optionWindow *ui;
    MainWindow *parW;

};

#endif // OPTIONWINDOW_H
