#include "operationwindow_3.h"
#include "ui_operationwindow_3.h"
#include<qsqlrecord.h>
#include"database.h"
#include<QMessageBox>

operationwindow_3::operationwindow_3(int key,int rowNum,QSqlTableModel* m,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::operationwindow_3)
{
    ui->setupUi(this);
    this->rowNum=rowNum;
    this->model=m;

    switch(key)//key==1为添加 key=2为修改
    {
    case 1:
        break;
    case 2:
        QSqlRecord rec=m->record(rowNum);
        ui->id_4->setText(rec.value(0).toString());
        ui->name_4->setText(rec.value(1).toString());
        ui->author->setText(rec.value(2).toString());
        ui->leftnumber->setText(rec.value(3).toString());
        ui->number->setText(rec.value(4).toString());
        break;
    }
}

operationwindow_3::~operationwindow_3()
{
    delete ui;
}

void operationwindow_3::on_pushButton_2_clicked()
{
    this->close();
}

void operationwindow_3::on_pushButton_clicked()
{
    database db;
    QString id;
    QString name;
    QString author;
    QString availablenumber;
    QString number;


    id=this->ui->id_4->text();
    name=this->ui->name_4->text();
    author=this->ui->author->text();
    availablenumber=this->ui->leftnumber->text();
    number=this->ui->number->text();

    if(id!=""&&name!=""&&author!=""&&availablenumber!=""&&number!=""&&availablenumber.toInt()<=number.toInt())
    {
        if(db.insert_book(this->rowNum,this->model,id,name,author,availablenumber,number))
        this->close();
    }
    else {
        QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请正确填写信息 "),QMessageBox::Ok,NULL);
        message.exec();
    }
}
