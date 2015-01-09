#include "querydialog.h"
#include "ui_querydialog.h"
#include <QSortFilterProxyModel>

QueryDialog::QueryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryDialog)
{
    ui->setupUi(this);
    m_model = new QSqlQueryModel();
    ui->tableView->setModel(m_model);
    this->setWindowTitle("List");
}

QueryDialog::~QueryDialog()
{
    delete ui;
}

void QueryDialog::setQuery(QString query,QSqlDatabase db)
{
    m_model->setQuery(query,db);
}
