#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QString>

class Configuration
{
public:
    Configuration();
    int confFileExists();
    void setDBPath(QString);
    QString getDBPath();
    void writeConfigFile();
private:
    QString m_dbPath;
    int m_confFileExists;
};

#endif // CONFIGURATION_H
