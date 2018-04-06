#ifndef OPERATIONWINDOW_3_H
#define OPERATIONWINDOW_3_H

#include <QWidget>
#include<qsqltablemodel.h>

namespace Ui {
class operationwindow_3;
}

class operationwindow_3 : public QWidget
{
    Q_OBJECT

public:
    explicit operationwindow_3(int key,int rowNum,QSqlTableModel*,QWidget *parent = 0);
    ~operationwindow_3();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::operationwindow_3 *ui;
    int rowNum;
    QSqlTableModel* model;
};

#endif // OPERATIONWINDOW_3_H
