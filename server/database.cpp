#include "database.h"

Database::Database()
{
    char cs1[] = "hydrogenMusic_db";
    QString s = cs1;
    QSqlDatabase db = connect(s);
    m_query = QSqlQuery(db);
    m_query.exec("USE hydrogenMusic_db");
}

QSqlDatabase Database::connect(const QString &dbName)
{
    QSqlDatabase db /*= QSqlDatabase::addDatabase("QMYSQL")*/;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName(dbName);
    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
        exit(1);
    }

    return db;
}

QSqlQuery Database::query() const
{
    return m_query;
}

std::string Database::selectDatabase(QString s,int i){
    m_query.exec(s);
    std::string ss = "";
    ss = output_database(i);
    return ss;
}

bool Database::changeDatabase(QString s)
{
    m_query.exec(s);
    std::cout << "change " << m_query.lastError().text().toStdString() << std::endl;
    if(m_query.lastError().text().toStdString() == " ") return true;
    else return false;
}

std::string Database::output_database(int i)
{
    std::string str = "";
    std::cout << "output " << std::endl;
    while(m_query.next()){
        for(int a = 0;a != i;a++) {
            std::cout << m_query.value(a).toString().toStdString() << " ";
            str += m_query.value(a).toString().toStdString() + " ";
        }
        str += " ||| ";
        std::cout << std::endl;
    }
    return str;
}