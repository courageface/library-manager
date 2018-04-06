#ifndef DATABASE_H
#define DATABASE_H
#include<QString>
#include<QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include<QTableWidget>
#include"admin.h"
#include"operationwindow_1.h"

class database
{
public:
    database();
    bool createConnection(QString pw,QString databasename);//创建数据库连接
    bool createTable();//建立初始表

    //For admin
    void show_libraryadmin(QSqlTableModel *model);
    void show_reader(QSqlTableModel *model);

    bool commit_current_table(QSqlTableModel *model,int key);
    void insertRecord(QSqlTableModel *model,int row);
    bool insert_libraryadmin(int rowNum,QSqlTableModel* model,QString,QString,int,QString);
    bool insert_reader(int rowNum,QSqlTableModel* model,QString id,QString name,int sex,QString pw);
    void deleteRecord(QSqlTableModel *model,int curNum);

    //For login
    bool query_username_libraryadmin(QSqlTableModel *model,QString username);
    bool query_password_libraryadmin(QSqlTableModel *model,QString password);
    bool query_username_reader(QSqlTableModel *model,QString username);
    bool query_password_reader(QSqlTableModel *model,QString password);

    //For library admin
    void show_book(QSqlTableModel *model);
    bool insert_book(int,QSqlTableModel*,QString,QString,QString,QString,QString);

    //For reader
    void show_bookborrowing(QSqlTableModel *model);
    void query_book(QSqlTableModel *model,QString id,QString name,QString author);
    void borrow(QSqlTableModel *model,int rowNum,QString username);
    void returnbook(QSqlTableModel *model,int rowNum,QSqlTableModel *model_1);



};
#endif
