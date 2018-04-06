#include "form.h"
#include "ui_form.h"
#include "login.h"
#include "database.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    database db;
    if(db.createConnection(ui->pw->text(),ui->lineEdit_2->text()))
    {
    this->close();
    Login* log=new Login;
    log->show();
    }

}

void Form::on_pushButton_2_clicked()
{
    this->close();
}
