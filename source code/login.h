#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <qsqltablemodel.h>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_login_admin_clicked();

    void on_login_libraryadmin_clicked();

    void on_login_reader_clicked();

private:
    Ui::Login *ui;
    int key;
    QSqlTableModel* model;

};

#endif // LOGIN_H
