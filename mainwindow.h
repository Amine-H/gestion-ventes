#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "database.h"
#include "configuration.h"
#include "querydialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString getLastDateModified();
    void setLastDateModified();
    Database* getDatabase();
    
private slots:
    void on_b_clients_clicked();

    void on_b_produits_clicked();

    void on_b_stock_clicked();

    void on_b_achats_clicked();

    void on_b_ventes_clicked();

private:
    Ui::MainWindow *ui;
    Database *m_db;
    Configuration *m_conf;

};

#endif // MAINWINDOW_H
