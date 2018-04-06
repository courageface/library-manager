#ifndef READER_H
#define READER_H

#include <QWidget>
#include<qsqltablemodel.h>

namespace Ui {
class reader;
}

class reader : public QWidget
{
    Q_OBJECT

public:
    explicit reader(QString username,QWidget *parent = 0);
    ~reader();

private slots:
    void on_query_clicked();

    void on_borrow_clicked();

    void on_exit_1_clicked();

    void on_exit_2_clicked();

    void on_add_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::reader *ui;
    QSqlTableModel* model_1;
    QSqlTableModel* model_2;
    QString username;
};

#endif // READER_H
