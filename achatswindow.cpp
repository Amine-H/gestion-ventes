#include "achatswindow.h"
#include "ui_achatswindow.h"
#include <QMessageBox>

AchatsWindow::AchatsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AchatsWindow)
{
    ui->setupUi(this);
    this->parent=(MainWindow*)parent;
    this->setWindowTitle("Achats");
    QSqlQuery query=this->parent->getDatabase()->getDB().exec("select nom from produits");
    while(query.next())
    {
        ui->i_produit->addItem(query.value(0).toString());
    }
}

AchatsWindow::~AchatsWindow()
{
    delete ui;
}

void AchatsWindow::on_b_ajouter_clicked()
{
    QString produit=ui->i_produit->currentText();
    int quantite=ui->i_quantite->text().toInt();
    int produitID=0;
    if(quantite<=0)
    {
        return;
    }
    else
    {
        QSqlQuery query=this->parent->getDatabase()->getDB().exec("select id from produits where nom='"+produit+"'");
        if(query.next())
        {
            produitID=query.value(0).toInt();
            query=parent->getDatabase()->getDB().exec("select * from stock where idProduit='"+QString::number(produitID)+"'");
            if(query.next())//already exists we need only update value
            {
                query=parent->getDatabase()->getDB().exec("update stock set quantite=quantite+"+QString::number(quantite)+" where idProduit='"+produitID+"'");
            }
            else//doesn't exist we need to add it
            {
                query=parent->getDatabase()->getDB().exec("insert into stock(idProduit,quantite) values('"+QString::number(produitID)+"','"+QString::number(quantite)+"')");
            }
            this->parent->setLastDateModified();
            QMessageBox::information(this,"Achat","Produit ajouté!");
        }
        else
        {
            return;
        }
    }
}
