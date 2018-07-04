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
#include <QObject>
#include <QVariant>

class Database:public QObject
{
    Q_OBJECT
public:
    Database();
    Q_INVOKABLE std::string selectDatabase(QString s, int i);
    Q_INVOKABLE bool changeDatabase(QString s);
    Q_INVOKABLE std::string output_database(int i);
    QSqlDatabase connect(const QString &dbName);
    QSqlQuery query() const;
    Q_INVOKABLE void usedb(QString m);
    void songListShow();
    QList<QString> returnSelect(std::string c);
signals:
    void songList(QList<QString> vec);
    void downloadOk();
    void uploadOk();
    void searchOk(QList<QString> vec);
private:
    QSqlQuery m_query;
};

#endif // DATABASE_H
