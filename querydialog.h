#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class QueryDialog;
}

class QueryDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QueryDialog(QWidget *parent = 0);
    ~QueryDialog();
    void setQuery(QString,QSqlDatabase);
    
private:
    Ui::QueryDialog *ui;
    QSqlQueryModel *m_model;
};

#endif // QUERYDIALOG_H
