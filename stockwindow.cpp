#include "stockwindow.h"
#include "ui_stockwindow.h"

StockWindow::StockWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockWindow)
{
    ui->setupUi(this);
    this->parent=(MainWindow*)parent;
    this->setWindowTitle("Stock");
}

StockWindow::~StockWindow()
{
    delete ui;
}

void StockWindow::on_b_showStock_clicked()
{
    QString query="select produits.nom as produit,categories.nom as categorie,prix,quantite from stock,produits,categories where idProduit=produits.id and produits.idCat=categories.id";
    QueryDialog *dialog =new QueryDialog(this);
    dialog->setQuery(query,parent->getDatabase()->getDB());
    dialog->show();
}

void StockWindow::on_pushButton_clicked()
{
    QString query="select produits.nom as produit,categories.nom as categorie,prix from stock,produits,categories where stock.idProduit=produits.id and produits.idCat=categories.id and quantite='0'";
    QueryDialog *dialog =new QueryDialog(this);
    dialog->setQuery(query,parent->getDatabase()->getDB());
    dialog->show();
}

void StockWindow::on_pushButton_2_clicked()
{
    QString query="select produits.nom as produit,categories.nom as categorie,prix,quantite from produits,categories,(select idProduit,sum(quantite) as quantite from ventes group by idProduit) where idProduit=produits.id and produits.idCat=categories.id";
    QueryDialog *dialog =new QueryDialog(this);
    dialog->setQuery(query,parent->getDatabase()->getDB());
    dialog->show();
}
