#include "database.h"
#include <QSqlError>
#include<QMessageBox>
#include<QSqlDatabase>
#include<QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>
#include<QTableView>
#include<QObject>
#include<QTableWidget>
#include"admin.h"
#include"operationwindow_1.h"
#include <QDateTime>

using namespace std;

database::database()
{
}

//建立一个数据库连接
bool database::createConnection(QString pw,QString databasename)
{
    //以后就可以用"dbc"与数据库进行连接了
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","dbc");

    db.setHostName("127.0.0.1");
    db.setUserName("root");
    //db.setPassword("181203y");
    db.setPassword(pw);
    db.setPort(3306);
    db.setDatabaseName(databasename);
    //db.setDatabaseName("db");//数据库名

    if( !db.open("root",pw))
    {
        qDebug() << "Can't connect to the database!";
         QMessageBox message(QMessageBox::Warning,"Connection is failed","Can't connect to the database!",QMessageBox::Ok,NULL);

         if(message.exec() == QMessageBox::Ok)
         {
            return false;
         }
        return false;
    }
    else{
        qDebug() << "Connected to database!";
       QMessageBox message(QMessageBox::Warning,"Notification","\tConnection is successful!\n\t HostName: "+db.hostName()+"\n\tDatabase: "+db.databaseName()+".db",QMessageBox::Ok,NULL);
      message.exec();
        return true;
    }
}

//创建数据库表
bool database::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("dbc"); //建立数据库连接
    QSqlQuery query(db);
    bool success1 = query.exec(" CREATE TABLE LibraryAdmin ("
                              " AdminID varchar(10) NOT NULL ,"
                              " Name varchar(10) NOT NULL,"
                               "Sex varchar(6) NOT NULL,"
                               "Passcode varchar(10) NOT NULL,"
                               "primary key(AdminID)"
                           ")default charset=utf8;");

    bool success2=query.exec("create table Reader("
                            " ReaderID varchar(20) NOT NULL,"
                             "Name varchar(10) NOT NULL,"
                             "Sex varchar(6) NOT NULL,"
                             "Passcode varchar(10) NOT NULL,"
                             "primary key(ReaderID)"
                        " )default charset=utf8;");


    bool success3=query.exec("create table Book("
                             "BookID varchar(20) NOT NULL,"
                             "Name varchar(20) NOT NULL,"
                             "Author varchar(15) NOT NULL,"
                             "AvailableNumber int NOT NULL,"
                             "Number int NOT NULL,"
                             "CHECK(Number>=0),"
                             "CHECK(AvailableNumber>=0),"
                             "primary key(BookID)"
                         ")default charset=utf8;");


     bool success4=query.exec("create table BookBorrowing("
                               "   ReaderID varchar(20) NOT NULL,"
                                "  BookID varchar(20) NOT NULL,"
                                 " BorrowMode varchar(10) NOT NULL,"
                              "Borrowtime varchar(60),"
                              "Returntime varchar(60),"
                                  "foreign key(ReaderID) references Reader(ReaderID) ON DELETE CASCADE ON UPDATE CASCADE,"
                                  "foreign key(BookID) references Book(BookID) ON DELETE CASCADE ON UPDATE CASCADE"

                              ")default charset=utf8;"
);

    if(success1)
    {qDebug() << QObject::tr("Table LibraryAdmin created!\n");}
    else
    { qDebug() << QObject::tr("Table LibraryAdmin wasn't created!\n");
    qDebug() << db.lastError();}
    if(success2)
    {qDebug() << QObject::tr("Table Reader created!\n");}
    else
    {qDebug() << QObject::tr("Table Reader wasn't created!\n");}
    if(success3)
    {qDebug() << QObject::tr("Table Book created!\n");}
    else
    {qDebug() << QObject::tr("Table Book wasn't created!\n");}
    if(success4)
    {qDebug() << QObject::tr("Table BookBorrowing created!\n");}
    else
    {qDebug() << QObject::tr("Table BookBorrowing wasn't created!\n");
    qDebug() << db.lastError();}
    if(success1 && success2 && success3 && success4){
        return true;
    }
    else return false;

}

void database::show_libraryadmin(QSqlTableModel *model)
{
    model->setTable("libraryadmin");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}

void database::show_reader(QSqlTableModel *model)
{
    model->setTable("reader");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}

bool database::query_username_libraryadmin(QSqlTableModel *model,QString username)
{
    model->setTable("libraryadmin");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setFilter("adminid='"+username+"'");
    qDebug()<<model->rowCount();
    if(model->rowCount()==0)
        return false;
    return true;
}


bool database::query_password_libraryadmin(QSqlTableModel *model,QString password)
{
    model->select();
    model->setFilter("passcode='"+password+"'");
    qDebug()<<model->rowCount();
    if(model->rowCount()==0)
        return false;
    return true;
}

bool database::query_username_reader(QSqlTableModel *model,QString username)
{
    model->setTable("reader");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setFilter("readerid='"+username+"'");
    qDebug()<<model->rowCount();
    if(model->rowCount()==0)
        return false;
    return true;
}

bool database::query_password_reader(QSqlTableModel *model,QString password)
{
    model->select();
    model->setFilter("passcode='"+password+"'");
    qDebug()<<model->rowCount();
    if(model->rowCount()==0)
        return false;
    return true;
}

bool database::commit_current_table(QSqlTableModel *model,int key)
{
    qDebug()<<"key value is: "<<key;
    model->database().transaction(); //开始事务操作
    if (model->submitAll()) // 提交所有被修改的数据到数据库中
    {
    model->database().commit(); //提交成功，事务将真正修改数据库数据
    qDebug()<<"Commit success!";
    if(key==1)
    {
    QMessageBox message(QMessageBox::Information,"提示",QString::fromUtf8("借书成功!"),QMessageBox::Ok,NULL);
    message.exec();}
    else if(key==2)
    {
    QMessageBox message(QMessageBox::Information,"提示",QString::fromUtf8("修改图书管理员成功!"),QMessageBox::Ok,NULL);
    message.exec();}
    else if(key==3)
    {
    QMessageBox message(QMessageBox::Information,"提示",QString::fromUtf8("创建图书管理员成功!"),QMessageBox::Ok,NULL);
    message.exec();}
    else if(key==4)
    {
    QMessageBox message(QMessageBox::Information,"提示",QString::fromUtf8("删除成功!"),QMessageBox::Ok,NULL);
    message.exec();}
    else if(key==5)
    {
    QMessageBox message(QMessageBox::Information,"提示",QString::fromUtf8("修改读者成功!"),QMessageBox::Ok,NULL);
    message.exec();}
    else if(key==6)
    {
    QMessageBox message(QMessageBox::Information,"提示",QString::fromUtf8("创建读者成功!"),QMessageBox::Ok,NULL);
    message.exec();}
    else if(key==7)
    {
    QMessageBox message(QMessageBox::Information,"提示",QString::fromUtf8("修改书籍成功!"),QMessageBox::Ok,NULL);
    message.exec();}
    else if(key==8)
    {
    QMessageBox message(QMessageBox::Information,"提示",QString::fromUtf8("创建书籍成功!"),QMessageBox::Ok,NULL);
    message.exec();}
    else if(key==9)
    {
    QMessageBox message(QMessageBox::Information,"提示",QString::fromUtf8("归还书籍成功!"),QMessageBox::Ok,NULL);
    message.exec();}

    return true;
    }
    else
    {
    model->database().rollback(); //提交失败，事务回滚
    qDebug()<<"Invalid value!";
    QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("请正确填写信息!"),QMessageBox::Ok,NULL);
    message.exec();
    return false;
    }
    model->revertAll(); //撤销修改

}


bool database::insert_libraryadmin(int rowNum,QSqlTableModel* model,QString id,QString name,int sex,QString pw)
{
    database db;

     if(rowNum!=-1)
    {
        QSqlRecord rec= model->record();

        rec.setValue("AdminID",id);
        rec.setValue("Name",name);
        rec.setValue("Sex",sex==0?"Male":(sex==1?"Female":"eeeeeee"));
        rec.setValue("Passcode",pw);
        model->setRecord(rowNum,rec);
        return db.commit_current_table(model,2);
    }
    else
    {
        rowNum = model->rowCount(); //获得表的行数
        qDebug()<<rowNum;
        QSqlRecord rec= model->record();

        rec.setValue("AdminID",id);
        rec.setValue("Name",name);
        rec.setValue("Sex",sex==0?"Male":(sex==1?"Female":"eeeeeee"));
        rec.setValue("Passcode",pw);
        qDebug()<<rec.value(0)<<" "<<rec.value(1)<<" "<<rec.value(2)<<" "<<rec.value(3);

        model->insertRecord(rowNum,rec);
        return db.commit_current_table(model,3);
     }

}

void database::deleteRecord(QSqlTableModel *model,int curRow)
{
    model->removeRow(curRow); //删除该行
    qDebug()<<curRow;
    database db;
    db.commit_current_table(model,4);
}

bool database::insert_reader(int rowNum,QSqlTableModel* model,QString id,QString name,int sex,QString pw)
{
    database db;
    if(rowNum!=-1)
    {
        QSqlRecord rec= model->record();

        rec.setValue("ReaderID",id);
        rec.setValue("Name",name);
        rec.setValue("Sex",sex==0?"Male":(sex==1?"Female":"eeeeeee"));
        rec.setValue("Passcode",pw);
        qDebug()<<rec.value(0)<<" "<<rec.value(1)<<" "<<rec.value(2)<<" "<<rec.value(3);

        model->setRecord(rowNum,rec);
        return db.commit_current_table(model,5);
    }
    else
    {
        rowNum = model->rowCount(); //获得表的行数
        qDebug()<<rowNum;
        QSqlRecord rec= model->record();

        rec.setValue("ReaderID",id);
        rec.setValue("Name",name);
        rec.setValue("Sex",sex==0?"Male":(sex==1?"Female":"eeeeeee"));
        rec.setValue("Passcode",pw);
        qDebug()<<rec.value(0)<<" "<<rec.value(1)<<" "<<rec.value(2)<<" "<<rec.value(3);

        model->insertRecord(rowNum,rec);
        return db.commit_current_table(model,6);
     }

}

bool database::insert_book(int rowNum,QSqlTableModel* model,QString id,QString name,QString author,QString availablenumber,QString number)
{
    database db;
    if(rowNum!=-1)
    {
        QSqlRecord rec= model->record();

        rec.setValue("BookID",id);
        rec.setValue("Name",name);
        rec.setValue("Author",author);
        rec.setValue("Availablenumber",availablenumber);
        rec.setValue("Number",number);

        model->setRecord(rowNum,rec);
        return db.commit_current_table(model,7);
    }
    else
    {
        rowNum = model->rowCount(); //获得表的行数
        qDebug()<<rowNum;
        QSqlRecord rec= model->record();

        rec.setValue("BookID",id);
        rec.setValue("Name",name);
        rec.setValue("Author",author);
        rec.setValue("Availablenumber",availablenumber);
        rec.setValue("Number",number);
        qDebug()<<rec.value(0)<<" "<<rec.value(1)<<" "<<rec.value(2)<<" "<<rec.value(3);

        model->insertRecord(rowNum,rec);
        return db.commit_current_table(model,8);
     }

}

void database::show_book(QSqlTableModel *model)
{
    model->setTable("Book");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}

void database::show_bookborrowing(QSqlTableModel *model)
{
    model->setTable("bookborrowing");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}

void database::query_book(QSqlTableModel *model,QString id,QString name,QString author)
{
    database db;
    db.show_book(model);
    if(!(id==""&&name==""&&author==""))
    model->setFilter("BookID like '%"+id+"%' and Name like '%"+name+"%' and Author like '%"+author+"%'");
}

void database::borrow(QSqlTableModel *model,int rowNum,QString username)
{
    database db;
    QSqlDatabase qdb = QSqlDatabase::database("dbc"); //建立数据库连接
    QSqlTableModel* model_temp = new QSqlTableModel(Q_NULLPTR, qdb);
    db.show_bookborrowing(model_temp);

    QSqlRecord record=model_temp->record();

    QSqlRecord rec=model->record(rowNum);

    if(rec.value(3).toInt()>0)
    {
        qDebug()<<QDateTime::currentDateTime().toString();
        record.setValue("ReaderID",username);
        record.setValue("BookID",rec.value(0).toString());
        record.setValue("BorrowMode","borrowed");
        record.setValue("Borrowtime",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
        record.setValue("Returntime","");
        int row=model_temp->rowCount();
        model_temp->insertRecord(row,record);
        if(db.commit_current_table(model_temp,0))
        {
        int k=rec.value(3).toInt()-1;
        rec.setValue("AvailableNumber",k);
        model->setRecord(rowNum,rec);
        db.commit_current_table(model,1);
        }

    }
    else{
        QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("书目数量不足!"),QMessageBox::Ok,NULL);
        message.exec();
    }
}

void database::returnbook(QSqlTableModel *model,int rowNum,QSqlTableModel *model_1)
{
    database db;
    QSqlDatabase qdb = QSqlDatabase::database("dbc"); //建立数据库连接
    QSqlTableModel* model_temp = new QSqlTableModel(Q_NULLPTR, qdb);
    db.show_book(model_temp);

    QSqlRecord rec=model->record(rowNum);
    QString bookid=rec.value(1).toString();
    model_temp->setFilter("BookID='"+bookid+"'");


    QSqlRecord record=model_temp->record(0);


    if(rec.value(2).toString()=="borrowed")
    {
        rec.setValue("BorrowMode","returned");
        rec.setValue("returntime",QDateTime::currentDateTime().toString("yyyy-MM-dd ddd"));
        model->setRecord(rowNum,rec);
        if(db.commit_current_table(model,0))
        {
        int k=record.value(3).toInt()+1;
        record.setValue("AvailableNumber",k);
        model_temp->setRecord(0,record);

        db.commit_current_table(model_temp,9);
        db.show_book(model_1);
        }
    }
    else{
        QMessageBox message(QMessageBox::Warning,"提示",QString::fromUtf8("该书已归还!"),QMessageBox::Ok,NULL);
        message.exec();
    }
}
