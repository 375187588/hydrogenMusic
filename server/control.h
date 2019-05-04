#ifndef CONTROL_H
#define CONTROL_H

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <iostream>
#include <string>
#include <stdio.h>
class Control
{
public:
    Control();
    std::string selectDatabase(QString s, int i,int begin =0);
    bool changeDatabase(QString s);
    std::string output_database(int end,int begin = 0);
    QSqlDatabase connect(const QString &dbName);
    QSqlQuery query() const;

private:
    QSqlQuery m_query;
};

#endif // CONTROL_H
