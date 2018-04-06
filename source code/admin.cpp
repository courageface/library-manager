#include "admin.h"
#include "ui_admin.h"
#include "database.h"
#include "operationwindow_1.h"
#include "operationwindow_2.h"
#include "login.h"
#include <QDebug>
#include <QMessageBox>


admin::admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);


    database db;
    QSqlDatabase qdb = QSqlDatabase::database("dbc"); //建立数据库连接

    //数据成员赋值
    this->model_1=new QSqlTableModel(Q_NULLPTR, qdb);
    this-> model_2=new QSqlTableModel(Q_NULLPTR, qdb);
    db.show_libraryadmin(model_1);
    db.show_reader(model_2);


    //Model与TableView链接 显示model指针
    ui->tableView_1->resizeColumnsToContents();
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_1->setModel(model_1);
    ui->tableView_1->show();
    ui->tableView_2->setModel(model_2);
    ui->tableView_2->show();
    ui->tableView_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

admin::~admin()
{
    delete ui;
    delete model_1;
    delete model_2;
}


//添加admin记录按钮
void admin::on_add_1_clicked()
{
    operationwindow_1* ow1=new operationwindow_1(1,-1,model_1);
    ow1->show();
}


//修改admin记录按钮
void admin::on_change_1_clicked()
{

    if(ui->tableView_1->currentIndex().row()==-1) //未选中合法行
    {QMessageBox message(QMessageBox::Warning,"提示",tr("请选中一条记录!"),QMessageBox::Ok,NULL);
    message.exec();}
    else
    {
    operationwindow_1* ow1=new operationwindow_1(2,ui->tableView_1->currentIndex().row(),model_1);
    ow1->show();
    }
}


//删除admin记录按钮
void admin::on_delete_1_clicked()
{
    if(ui->tableView_1->currentIndex().row()==-1) //未选中合法行
    {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请选中一条记录!"),QMessageBox::Ok,NULL);
    message.exec();}
    else
    {
        {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("确定要删除这位图书管理员吗?"),QMessageBox::Ok,NULL);
            message.addButton(QMessageBox::Cancel);
        if(message.exec()==QMessageBox::Ok)
        {
            database db;
            db.deleteRecord(model_1,ui->tableView_1->currentIndex().row());
        }

    }
}
}


//退出登录按钮
void admin::on_exit_1_clicked()
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

//添加reader记录按钮
void admin::on_add_2_clicked()
{
    operationwindow_2* ow2=new operationwindow_2(1,-1,model_2);
    ow2->show();
}

//修改reader记录按钮
void admin::on_change_2_clicked()
{
    if(ui->tableView_2->currentIndex().row()==-1) //未选中合法行
    {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请选中一条记录!"),QMessageBox::Ok,NULL);
    message.exec();}
    else
    {
    operationwindow_2* ow2=new operationwindow_2(2,ui->tableView_2->currentIndex().row(),model_2);
    ow2->show();
    }
}

//删除reader记录按钮
void admin::on_delete_2_clicked()
{
    if(ui->tableView_2->currentIndex().row()==-1) //未选中合法行
    {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请选中一条记录!"),QMessageBox::Ok,NULL);
    message.exec();}
    else
    {
        {QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("确定要删除这位读者吗?"),QMessageBox::Ok,NULL);
            message.addButton(QMessageBox::Cancel);
        if(message.exec()==QMessageBox::Ok)
        {
            database db;
            db.deleteRecord(model_2,ui->tableView_2->currentIndex().row());
        }

    }
}
}

//退出登录按钮
void admin::on_exit_2_clicked()
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
