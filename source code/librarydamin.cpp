#include "librarydamin.h"
#include "ui_librarydamin.h"
#include"operationwindow_3.h"
#include<QMessageBox>
#include"database.h"
#include"login.h"

librarydamin::librarydamin(QString username,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::librarydamin)
{
    ui->setupUi(this);
    this->username=username;
    this->setWindowTitle("Library administrator - "+this->username);
    database db;
    QSqlDatabase qdb = QSqlDatabase::database("dbc"); //建立数据库连接

    //数据成员赋值
    this->model=new QSqlTableModel(Q_NULLPTR, qdb);
    db.show_book(model);


    //Model与TableView链接 显示model指针
    ui->tableView_3->resizeColumnsToContents();
    ui->tableView_3->setModel(model);
    ui->tableView_3->show();
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

librarydamin::~librarydamin()
{
    delete ui;
    delete model;
}

void librarydamin::on_add_3_clicked()
{
    operationwindow_3* ow3=new operationwindow_3(1,-1,model);
    ow3->show();
}

void librarydamin::on_change_3_clicked()
{
    if(ui->tableView_3->currentIndex().row()==-1) //未选中合法行
    {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请选中一条记录!"),QMessageBox::Ok,NULL);
    message.exec();}
    else
    {
    operationwindow_3* ow3=new operationwindow_3(2,ui->tableView_3->currentIndex().row(),model);
    ow3->show();
    }
}

void librarydamin::on_delete_3_clicked()
{
    if(ui->tableView_3->currentIndex().row()==-1) //未选中合法行
    {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请选中一条记录!"),QMessageBox::Ok,NULL);
    message.exec();}
    else
    {
        {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("确定要删除这本图书吗?"),QMessageBox::Ok,NULL);
            message.addButton(QMessageBox::Cancel);
        if(message.exec()==QMessageBox::Ok)
        {
            database db;
            db.deleteRecord(model,ui->tableView_3->currentIndex().row());
        }

    }
}
}

void librarydamin::on_exit_3_clicked()
{
    {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("确定要退出吗?"),QMessageBox::Ok,NULL);
        message.addButton(QMessageBox::Cancel);
    if(message.exec()==QMessageBox::Ok)
    {
        this->close();
        Login* login=new Login;
        login->show();
    }
    else message.close();
    }
}
