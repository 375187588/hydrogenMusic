#ifndef DATABASE_H
#define DATABASE_H

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <iostream>
#include <string>
#include <stdio.h>
class Database
{
public:
    Database();
    std::string selectDatabase(QString s, int i);
    bool changeDatabase(QString s);
    std::string output_database(int i);
    QSqlDatabase connect(const QString &dbName);
    QSqlQuery query() const;

private:
    QSqlQuery m_query;
};

#endif // DATABASE_H
