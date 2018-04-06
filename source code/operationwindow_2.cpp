#include "operationwindow_2.h"
#include "ui_operationwindow_2.h"
#include"database.h"
#include<qsqlrecord.h>
#include<QMessageBox>

operationwindow_2::operationwindow_2(int key,int rowNum,QSqlTableModel* m,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::operationwindow_2)
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
        ui->id_3->setText(rec.value(0).toString());
        ui->name_3->setText(rec.value(1).toString());
        ui->comboBox_3->setCurrentIndex((rec.value(2).toString()=="Male")?0:1);
        ui->pw_3->setText(rec.value(3).toString());
        break;
    }
}

operationwindow_2::~operationwindow_2()
{
    delete ui;
}

void operationwindow_2::on_pushButton_5_clicked()
{
    database db;
    QString id;
    QString name;
    int sex;
    QString password;


    id=this->ui->id_3->text();
    name=this->ui->name_3->text();
    sex=this->ui->comboBox_3->currentIndex();
    password=this->ui->pw_3->text();

    if(id!=""&&name!=""&&password!="")
    {
        if(db.insert_reader(this->rowNum,this->model,id,name,sex,password))
            this->close();
    }
    else {
        QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请正确填写信息 "),QMessageBox::Ok,NULL);
        message.exec();
    }
}

void operationwindow_2::on_pushButton_6_clicked()
{
    this->close();
}
