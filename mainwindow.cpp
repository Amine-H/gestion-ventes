#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "login.h"
#include "clientswindow.h"
#include "produitswindow.h"
#include "stockwindow.h"
#include "achatswindow.h"
#include "venteswindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_conf = new Configuration();

    if(!m_conf->confFileExists())
    {
        QString dbPath=QFileDialog::getOpenFileName(this,tr("Ouvrir Fichier"),
                                                    "./",tr("Fichier de données (*.db)"));
        m_conf->setDBPath(dbPath);
        m_conf->writeConfigFile();
    }

    m_db = new Database(m_conf->getDBPath());
    if(!m_db->isDBOpen())
    {
        QMessageBox::critical(this,"Base de Données",
                              "Impossible d'ouvrir la base de données!");
        exit(m_db->isDBOpen());
    }

    Login *loginWindow = new Login(this);
    loginWindow->exec();

    QString username=loginWindow->getUsername(),
            password=loginWindow->getPassword();

    QSqlQuery login_query=m_db->execute("select * from utilisateurs where nom='"+username+"' and motDePasse='"+password+"'");

    if(!login_query.next())
    {
        QMessageBox::critical(this,"Login","Login ou Mot de passe incorrect!");
        exit(0);
    }

    ui->dbStatus->setText(username+" Connecté!");
    ui->dbStatus->setStyleSheet("QLabel{color:green;}");
    ui->lastModification->setText(this->getLastDateModified());
}

QString MainWindow::getLastDateModified()
{
    QSqlQuery query;
    if(query.exec("select value from parametres where parameter='lastModified'") && query.next())
    {
        return query.value(0).toString();
    }
    else
    {
        return "dernière modification";
    }
}

void MainWindow::setLastDateModified()
{
    QDate date = QDate::currentDate();
    QString dateStr = date.toString("dd/MM/yyyy");
    ui->lastModification->setText(dateStr);
    this->m_db->getDB().exec("update parametres set value='"+dateStr+"' where parameter='lastModified'");
}

Database* MainWindow::getDatabase()
{
    return this->m_db;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b_clients_clicked()
{
    ClientsWindow *clientWindow=new ClientsWindow(this);
    clientWindow->show();
}

void MainWindow::on_b_produits_clicked()
{
    ProduitsWindow *produitWindow=new ProduitsWindow(this);
    produitWindow->show();
}

void MainWindow::on_b_stock_clicked()
{
    StockWindow *stockWindow=new StockWindow(this);
    stockWindow->show();
}

void MainWindow::on_b_achats_clicked()
{
    AchatsWindow *window = new AchatsWindow(this);
    window->show();
}

void MainWindow::on_b_ventes_clicked()
{
    VentesWindow *window = new VentesWindow(this);
    window->show();
}
