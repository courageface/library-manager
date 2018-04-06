#include "reader.h"
#include "ui_reader.h"
#include"database.h"
#include<QDebug>
#include<QMessageBox>
#include"login.h"
#include<QSqlRecord>
#include <QTextCodec>

reader::reader(QString username,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reader)
{
    ui->setupUi(this);
    this->username=username;
    this->setWindowTitle("Reader - "+this->username);
    database db;
    QSqlDatabase qdb = QSqlDatabase::database("dbc"); //建立数据库连接

    //数据成员赋值
    this->model_1=new QSqlTableModel(Q_NULLPTR, qdb);
    this-> model_2=new QSqlTableModel(Q_NULLPTR, qdb);
    db.show_book(model_1);
    db.show_bookborrowing(model_2);


    //Model与TableView链接 显示model指针
    ui->tableView_1->resizeColumnToContents(4);
    ui->tableView_2->resizeColumnToContents(4);
    ui->tableView_1->resizeColumnToContents(3);
    ui->tableView_2->resizeColumnToContents(3);
    ui->tableView_1->setModel(model_1);
    ui->tableView_1->show();
    ui->tableView_2->setModel(model_2);
    ui->tableView_2->show();
    ui->tableView_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

reader::~reader()
{
    delete ui;
    delete model_1;
    delete model_2;
}

void reader::on_query_clicked()
{
    QString id=this->ui->id->text();
    QString name=this->ui->name->text();
    QString author=this->ui->author->text();
    database db;
    qDebug()<<id<<" "<<name<<" "<<author;
    db.query_book(this->model_1,id,name,author);
}

void reader::on_borrow_clicked()
{
    qDebug()<<ui->tableView_1->currentIndex().row();
    if(ui->tableView_1->currentIndex().row()==-1) //未选中合法行
    {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请选中一条记录!"),QMessageBox::Ok,NULL);
    message.exec();}
    else
    {     
        QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("确定要借阅该书吗?"),QMessageBox::Ok,NULL);
            message.addButton(QMessageBox::Cancel);
        if(message.exec()==QMessageBox::Ok)
        {
            database db;
            db.borrow(this->model_1,ui->tableView_1->currentIndex().row(),this->username);
            db.show_bookborrowing(model_2);
            model_2->setFilter("ReaderID='"+this->username+"'");
        }
    }
}

void reader::on_exit_1_clicked()
{
    QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("确定要退出吗?"),QMessageBox::Ok,NULL);
        message.addButton(QMessageBox::Cancel);
    if(message.exec()==QMessageBox::Ok)
    {
        this->close();
        Login* login=new Login;
        login->show();
    }
    else message.close();

}

void reader::on_exit_2_clicked()
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

void reader::on_add_4_clicked()
{
    if(ui->tableView_2->currentIndex().row()==-1) //未选中合法行
    {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请选中一条记录!"),QMessageBox::Ok,NULL);
    message.exec();}
    else
        {
        QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("确定要归还该书吗?"),QMessageBox::Ok,NULL);
        message.addButton(QMessageBox::Cancel);
    if(message.exec()==QMessageBox::Ok)
    {
        database db;
        db.returnbook(this->model_2,ui->tableView_2->currentIndex().row(),this->model_1);
        db.show_bookborrowing(model_2);
        model_2->setFilter("ReaderID='"+this->username+"'");
    }
    }
}

void reader::on_pushButton_clicked()
{
    if(ui->tableView_2->currentIndex().row()==-1) //未选中合法行
    {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请选中一条记录!"),QMessageBox::Ok,NULL);
    message.exec();}
    else
    {
        {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("确定要删除这条记录吗?"),QMessageBox::Ok,NULL);
            message.addButton(QMessageBox::Cancel);
        if(message.exec()==QMessageBox::Ok)
        {
            QSqlRecord rec=model_2->record(ui->tableView_2->currentIndex().row());
            if(rec.value(2).toString()=="borrowed")
            {
                QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("书还没还就想删除?"),QMessageBox::Ok,NULL);
                message.exec();
            }
            else
            {
            database db;
            db.deleteRecord(model_2,ui->tableView_2->currentIndex().row());
            }
        }

    }
}
}
