#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include<qsqltablemodel.h>

namespace Ui {
class admin;
}

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = 0);
    ~admin();

private slots:
    void on_add_1_clicked();

    void on_change_1_clicked();

    void on_delete_1_clicked();

    void on_exit_1_clicked();

    void on_add_2_clicked();

    void on_change_2_clicked();

    void on_delete_2_clicked();

    void on_exit_2_clicked();

private:
    Ui::admin *ui;
    QSqlTableModel* model_1;
    QSqlTableModel* model_2;

};

#endif // ADMIN_H
