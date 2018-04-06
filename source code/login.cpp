#include "login.h"
#include "ui_login.h"
#include"database.h"
#include"QMessageBox"
#include"admin.h"
#include"librarydamin.h"
#include"reader.h"


QSqlTableModel *model;

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);



    database db;
    //db.createConnection();//连接数据库
    QSqlDatabase qdb = QSqlDatabase::database("dbc"); //建立数据库连接
    model = new QSqlTableModel(Q_NULLPTR, qdb);
    db.createTable();
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_admin_clicked()
{
    if(ui->username_1->text() == "admin"&& ui->password_1->text() == "1234")//checking the admin account info
    {
        this->close();
        admin* aw=new admin;
        aw->show();
    }
    else QMessageBox::warning(this, tr("失败"), QString(tr("Username or password is wrong.")),QMessageBox::Ok);
}

void Login::on_login_libraryadmin_clicked()
{
    QString username=ui->username_2->text();
    QString password=ui->password_2->text();

    database db;
    if(db.query_username_libraryadmin(this->model,username))
    {
        if(db.query_password_libraryadmin(this->model,password))
        {
        this->close();
        librarydamin* lad=new librarydamin(username);
        lad->show();
        }
        else QMessageBox::warning(this, tr("失败"), QString(tr("Password is wrong.")),QMessageBox::Ok);
    }
   else QMessageBox::warning(this, tr("失败"), QString(tr("Username doesn't exist.")),QMessageBox::Ok);
}


void Login::on_login_reader_clicked()
{
    QString username=ui->username_3->text();
    QString password=ui->password_3->text();

    database db;
    if(db.query_username_reader(this->model,username))
    {
        if(db.query_password_reader(this->model,password))
        {
        this->close();
        reader* r=new reader(username);
        r->show();
        }
        else QMessageBox::warning(this, tr("失败"), QString(tr("Password is wrong.")),QMessageBox::Ok);
    }
   else QMessageBox::warning(this, tr("失败"), QString(tr("Username doesn't exist.")),QMessageBox::Ok);
}
