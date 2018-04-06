#ifndef OPERATIONWINDOW_1_H
#define OPERATIONWINDOW_1_H

#include <QWidget>
#include<qsqltablemodel.h>
#include"admin.h"

namespace Ui {
class operationwindow_1;
}

class operationwindow_1 : public QWidget
{
    Q_OBJECT

public:
    explicit operationwindow_1(int key,int rowNum,QSqlTableModel*,QWidget *parent = 0);
    ~operationwindow_1();


private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    int rowNum;
    QSqlTableModel* model;
    Ui::operationwindow_1 *ui;

};

#endif // OPERATIONWINDOW_1_H
