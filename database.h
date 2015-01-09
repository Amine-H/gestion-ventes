#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QString>

class Database
{
public:
    Database(QString DBName);
    int isDBOpen();
    QSqlQuery execute(QString);
    QSqlDatabase getDB();
private:
    QString m_DBName;
    QSqlDatabase m_db;
};

#endif // DATABASE_H
