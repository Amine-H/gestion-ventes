#include "produitswindow.h"
#include "ui_produitswindow.h"
#include <QMessageBox>

ProduitsWindow::ProduitsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProduitsWindow)
{
    ui->setupUi(this);
    this->parent=(MainWindow*)parent;
    this->setWindowTitle("Produits");

    QSqlQuery query=this->parent->getDatabase()->getDB().exec("select nom from categories");

    while(query.next())
    {
        ui->i_cat->addItem(query.value(0).toString());
    }
}

ProduitsWindow::~ProduitsWindow()
{
    delete ui;
}

void ProduitsWindow::on_pushButton_2_clicked()
{
    QString query="select produits.nom as produit,categories.nom as categories,prix from produits,categories where idCat=categories.id";
    QueryDialog *dialog =new QueryDialog(this);
    dialog->setQuery(query,parent->getDatabase()->getDB());
    dialog->show();
}

void ProduitsWindow::on_pushButton_clicked()
{
    QString catText=ui->i_cat->currentText().toLower();
    if(ui->i_nom->text().isEmpty() || ui->i_prix->text().isEmpty())
    {
        return;
    }
    int CatID=1;
    QSqlQuery query=this->parent->getDatabase()->getDB().exec("select id,nom from categories where nom='"+catText+"'");
    if(query.next())
    {
        CatID=query.value(0).toInt();
    }
    else
    {
        query=this->parent->getDatabase()->getDB().exec("select max(id) from categories");
        if(query.next())
        {
            CatID=query.value(0).toInt()+1;
        }
        else
        {
            CatID=1;
        }

        query=this->parent->getDatabase()->getDB().exec("insert into categories(nom) values('"+catText+"')");
    }

    query=this->parent->getDatabase()->getDB().exec("insert into produits(nom,prix,idCat) values('"+
                                                    ui->i_nom->text()+"','"+
                                                    ui->i_prix->text()+"','"+
                                                    QString::number(CatID)+"')");
    parent->setLastDateModified();
    QMessageBox::information(this,"Produits","Produit Ajouté!");
}
