#include "operationwindow_1.h"
#include "ui_operationwindow_1.h"
#include"database.h"
#include<QDebug>
#include<qsqlrecord.h>
#include<QMessageBox>

operationwindow_1::operationwindow_1(int key,int rowNum,QSqlTableModel* m,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::operationwindow_1)
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
        ui->id_2->setText(rec.value(0).toString());
        ui->name_2->setText(rec.value(1).toString());
        ui->comboBox_2->setCurrentIndex((rec.value(2).toString()=="Male")?0:1);
        ui->pw_2->setText(rec.value(3).toString());
        break;
    }
}

operationwindow_1::~operationwindow_1()
{
    delete ui;

}

void operationwindow_1::on_pushButton_3_clicked()
{
    this->close();
}

void operationwindow_1::on_pushButton_4_clicked()
{
    database db;
    QString id;
    QString name;
    int sex;
    QString password;


    id=this->ui->id_2->text();
    name=this->ui->name_2->text();
    sex=this->ui->comboBox_2->currentIndex();
    password=this->ui->pw_2->text();

    if(id!=""&&name!=""&&password!="")
    {
    if(db.insert_libraryadmin(this->rowNum,this->model,id,name,sex,password))
        this->close();
    }
    else {
        QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请正确填写信息 "),QMessageBox::Ok,NULL);
        message.exec();
    }

}
