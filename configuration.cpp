#include "configuration.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Configuration::Configuration()
{
    QFile file("config.conf");
    QList<QString> listdesParams = QList<QString>();
    QString ligne;

    if(file.exists())
    {
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        m_confFileExists=1;
        while(!stream.atEnd())
        {
            ligne = stream.readLine();
            listdesParams << ligne;
        }

        m_dbPath=listdesParams[0];//chemin vers la base de données

        file.close();
    }
    else
    {
        m_confFileExists=0;
    }
}

int Configuration::confFileExists()
{
    return m_confFileExists;
}

void Configuration::setDBPath(QString dbPath)
{
    m_dbPath=dbPath;
}

QString Configuration::getDBPath()
{
    return m_dbPath;
}

void Configuration::writeConfigFile()
{
    QFile file("config.conf");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << m_dbPath << endl;
    }
}
