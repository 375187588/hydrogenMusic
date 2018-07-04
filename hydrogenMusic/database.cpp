#include "database.h"
#include <sstream>

Database::Database()
{
    char cs1[] = "hydrogenMusic_db";
    QString s = cs1;
    QSqlDatabase db = connect(s);
    m_query = QSqlQuery(db);
    m_query.exec("USE hydrogenMusic_db");
    QString a = "CREATE TABLE IF NOT EXISTS songList(nameAr CHAR(60) primary key,address TEXT);";
    changeDatabase(a);
    a = "CREATE TABLE IF NOT EXISTS downLoad(nameAr CHAR(20) primary key,address TEXT);";
    changeDatabase(a);



}

QSqlDatabase Database::connect(const QString &dbName)
{
    QSqlDatabase db /*= QSqlDatabase::addDatabase("QMYSQL")*/;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("chakra");
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


void Database::usedb(QString m)
{
    std::istringstream record(m.toStdString());
    std::string head;
    record >> head;
    if(head == "songListShow") songListShow();
    else if(head == "download") {
        std::string nameAr;
        std::string addr;
        record >> nameAr;
        while (record >> head) {
                addr += head;
        }
        std::string c = "INSERT INTO downLoad VALUES('" + nameAr + "','" + addr + "');";
        QString cmd = QString::fromStdString(c);
        if(changeDatabase(cmd)) emit downloadOk();
    }else if(head == "upload") {
        std::string nameAr;
        std::string addr;
        record >> nameAr;
        while (record >> head) {
                addr += head;
        }
        std::string c = "INSERT INTO songList VALUES('" + nameAr + "','" + addr + "');";
        QString cmd = QString::fromStdString(c);
        if(changeDatabase(cmd)) {
            emit uploadOk();
            songListShow();
        }
    }else if(head == "search") {
        std::string searchContent;
        std::string searchforWhat;
        std::string cmd;
        record >> searchContent >> searchforWhat;
        if(searchforWhat == "nameAr") cmd = "select * from songList where nameAr = '"+ searchContent +"'";
//        if(searchContent == "nameAr") std::string cmd = "select * from songList where nameAr = '"+ searchContent +"'";

        QList<QString> vec = returnSelect(cmd);
        emit searchOk(vec);

    }
}

void Database::songListShow()
{
    std::string cmd = "select * from songList;";
    QList<QString> vec = returnSelect(cmd);

    emit songList(vec);
}

QList<QString> Database::returnSelect(std::string c)
{
    QString cmd = QString::fromStdString(c);
    QList<QString> vec;
    std::string ret = selectDatabase(cmd,2);
    if(ret.empty()) {
        ret = "******";
        vec.append(QString::fromStdString(ret));
        return vec;
    }
    std::istringstream rec(ret);
    std::string head;
    bool ishead = true;
    std::string head1;
    while (rec >> head) {
        if(head != "|||" && !ishead) {
            head1 += head;
        }else if(head == "|||"){
            vec.append(QString::fromStdString(head1));
            head1.clear();
            ishead = true;
        }else if(ishead) {
            vec.append(QString::fromStdString(head));
            ishead = false;
        }
    }
    return vec;

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
    if(m_query.lastError().text().toStdString() == " ") {
        return true;
    }else return false;
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
