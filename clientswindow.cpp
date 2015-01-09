#include "clientswindow.h"
#include "ui_clientswindow.h"
#include <QMessageBox>
#include "querydialog.h"

ClientsWindow::ClientsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientsWindow)
{
    ui->setupUi(this);
    this->parent=(MainWindow*)parent;
    this->setWindowTitle("Clients");
}

ClientsWindow::~ClientsWindow()
{
    delete ui;
}

void ClientsWindow::on_b_ajouter_clicked()
{
    if(!ui->i_nom->text().isEmpty() || !ui->i_prenom->text().isEmpty())
    {
        parent->getDatabase()->getDB().exec("insert into clients(nom,prenom,tel) values('"+
                                           ui->i_nom->text()+"','"+ui->i_prenom->text()+
                                           "','"+ui->i_tel->text()+"')");
        parent->setLastDateModified();
        this->parent->setLastDateModified();
        QMessageBox::information(this,"Clients","Client ajouté!");
    }
}

void ClientsWindow::on_pushButton_clicked()
{
    QString query="select nom,prenom,tel from clients";
    QueryDialog *dialog =new QueryDialog(this);
    dialog->setQuery(query,parent->getDatabase()->getDB());
    dialog->show();
}
