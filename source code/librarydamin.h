#ifndef LIBRARYDAMIN_H
#define LIBRARYDAMIN_H

#include <QWidget>
#include <qsqltablemodel.h>

namespace Ui {
class librarydamin;
}

class librarydamin : public QWidget
{
    Q_OBJECT

public:
    explicit librarydamin(QString username,QWidget *parent = 0);
    ~librarydamin();

private slots:
    void on_add_3_clicked();

    void on_change_3_clicked();

    void on_delete_3_clicked();

    void on_exit_3_clicked();

private:
    Ui::librarydamin *ui;
    QSqlTableModel* model;
    QString username;
};

#endif // LIBRARYDAMIN_H
