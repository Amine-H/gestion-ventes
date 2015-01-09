#include "ventescrediteditwindow.h"
#include "ui_ventescrediteditwindow.h"
#include <QMessageBox>
#include <QSqlQuery>

VentesCreditEditWindow::VentesCreditEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentesCreditEditWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Modifier Credits");
    this->parent=(MainWindow*)parent->parent();

    QSqlQuery query=this->parent->getDatabase()->getDB().exec("select nom,prenom from clients");
    while(query.next())
    {
        ui->i_client->addItem(query.value(0).toString()+" "+query.value(1).toString());
    }
}

VentesCreditEditWindow::~VentesCreditEditWindow()
{
    delete ui;
}

void VentesCreditEditWindow::on_pushButton_2_clicked()
{
    this->close();
}

void VentesCreditEditWindow::on_i_client_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query=this->parent->getDatabase()->getDB().exec("select id from clients where (nom || ' ' || prenom)='"+arg1+"'");
    if(query.next())
    {
        m_clientID=query.value(0).toInt();
        query=this->parent->getDatabase()->getDB().exec("select nom from produits,ventes where idClient='"+QString::number(m_clientID)+"' and idProduit=produits.id");
        while(query.next())
        {
            ui->i_produit->addItem(query.value(0).toString());
        }
    }
}

void VentesCreditEditWindow::on_i_produit_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query=this->parent->getDatabase()->getDB().exec("select id from produits where nom='"+arg1+"'");
    if(query.next())
    {
        m_produitID=query.value(0).toInt();
        query=this->parent->getDatabase()->getDB().exec("select quantite,paye from ventes where idProduit='"+QString::number(m_produitID)+"' and idClient='"+QString::number(m_clientID)+"'");
        if(query.next())
        {
            m_quantite=query.value(0).toInt();
            m_paye=query.value(1).toFloat();
            ui->i_quantite->setText(QString::number(m_quantite));
            ui->i_paye->setText(QString::number(m_paye));
        }
    }
}

void VentesCreditEditWindow::on_pushButton_clicked()
{
    QSqlQuery query=this->parent->getDatabase()->getDB().exec("update ventes set paye='"+QString::number(m_paye)+"',quantite='"+QString::number(m_quantite)+"' where idProduit='"+QString::number(m_produitID)+"' and idClient='"+QString::number(m_clientID)+"'");
    QMessageBox::information(this,"Credit","Modifié!");
    this->parent->setLastDateModified();
    this->close();
}

void VentesCreditEditWindow::on_i_paye_textChanged(const QString &arg1)
{
    m_paye=arg1.toInt();
}

void VentesCreditEditWindow::on_i_quantite_textChanged(const QString &arg1)
{
    m_quantite=arg1.toInt();
}
