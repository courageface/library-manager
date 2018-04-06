#ifndef OPERATIONWINDOW_2_H
#define OPERATIONWINDOW_2_H

#include <QWidget>
#include<qsqltablemodel.h>
#include"admin.h"

namespace Ui {
class operationwindow_2;
}

class operationwindow_2 : public QWidget
{
    Q_OBJECT

public:
    explicit operationwindow_2(int key,int rowNum,QSqlTableModel*,QWidget *parent = 0);
    ~operationwindow_2();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::operationwindow_2 *ui;
    int rowNum;
    QSqlTableModel* model;
};

#endif // OPERATIONWINDOW_2_H
