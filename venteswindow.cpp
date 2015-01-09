#include "venteswindow.h"
#include "ui_venteswindow.h"
#include "ventescrediteditwindow.h"
#include <QMessageBox>

VentesWindow::VentesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentesWindow)
{
    ui->setupUi(this);
    this->parent=(MainWindow*)parent;
    this->setWindowTitle("Ventes");

    QSqlQuery query=this->parent->getDatabase()->getDB().exec("select nom from produits");
    while(query.next())
    {
        ui->i_produit->addItem(query.value(0).toString());
    }

    query=this->parent->getDatabase()->getDB().exec("select nom,prenom from clients");
    while(query.next())
    {
        ui->i_client->addItem(query.value(0).toString()+" "+query.value(1).toString());
    }

    ui->i_quantite->setText("1");
}

VentesWindow::~VentesWindow()
{
    delete ui;
}

void VentesWindow::on_i_produit_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query=this->parent->getDatabase()->getDB().exec("select prix from produits where nom='"+arg1+"'");
    if(query.next())
    {
        ui->i_paye->setText(query.value(0).toString());
    }
    else
    {
        ui->i_paye->setText("0");
    }
}

void VentesWindow::on_pushButton_clicked()
{
    VentesCreditEditWindow *window=new VentesCreditEditWindow(this);
    window->show();
}

void VentesWindow::on_b_vente_clicked()
{
    int clientID=0,produitID=0,quantite=0;
    float paye=0;
    QSqlQuery query=this->parent->getDatabase()->getDB().exec("select id from clients where (nom || ' ' || prenom)='"+ui->i_client->currentText()+"'");
    if(query.next())
    {
        clientID=query.value(0).toInt();
        query=this->parent->getDatabase()->getDB().exec("select id from produits where nom='"+ui->i_produit->currentText()+"'");
        if(query.next())
        {
            produitID=query.value(0).toInt();
            paye=ui->i_paye->text().toInt();
            quantite=ui->i_quantite->text().toInt();

            query=this->parent->getDatabase()->getDB().exec("select quantite from stock where idProduit='"+QString::number(produitID)+"'");
            if(!query.next() || query.value(0).toInt()<quantite)
            {
                QMessageBox::critical(this,"Ventes","le stock ne contient pas le produit ou la quantité est insuffisante!");
                return;
            }
            query=this->parent->getDatabase()->getDB().exec("select * from ventes where idClient='"+QString::number(clientID)+"' and idProduit='"+QString::number(produitID)+"'");
            if(query.next())//exists we need to update
            {
                query=this->parent->getDatabase()->getDB().exec("update ventes set paye=paye+"+QString::number(paye)+",quantite=quantite+"+QString::number(quantite)+" where idClient='"+QString::number(clientID)+"' and idProduit='"+QString::number(produitID)+"'");
            }
            else//cool doesn't exist we need to insert
            {
                query=this->parent->getDatabase()->getDB().exec("insert into ventes(idClient,idProduit,quantite,paye) values('"+QString::number(clientID)+"','"+QString::number(produitID)+"','"+QString::number(quantite)+"','"+QString::number(paye)+"')");
            }
            this->parent->setLastDateModified();
            query=this->parent->getDatabase()->getDB().exec("update stock set quantite=quantite-"+QString::number(quantite)+" where idProduit='"+QString::number(produitID)+"'");
            QMessageBox::information(this,"Ventes","Enregistré!");
        }
    }
}

void VentesWindow::on_pushButton_2_clicked()
{
    QString query="select clients.nom as nom,prenom,produits.nom as produit,prix,paye \"à payé\" from clients,produits,ventes where idClient=clients.id and idProduit=produits.id and ventes.idProduit=produits.id and prix != paye";
    QueryDialog *dialog =new QueryDialog(this);
    dialog->setQuery(query,parent->getDatabase()->getDB());
    dialog->show();
}
