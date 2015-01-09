#ifndef VENTESCREDITEDITWINDOW_H
#define VENTESCREDITEDITWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class VentesCreditEditWindow;
}

class VentesCreditEditWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit VentesCreditEditWindow(QWidget *parent = 0);
    ~VentesCreditEditWindow();
    
private slots:
    void on_pushButton_2_clicked();

    void on_i_client_currentIndexChanged(const QString &arg1);

    void on_i_produit_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_i_paye_textChanged(const QString &arg1);

    void on_i_quantite_textChanged(const QString &arg1);

private:
    Ui::VentesCreditEditWindow *ui;
    int m_clientID;
    int m_produitID;
    int m_quantite;
    float m_paye;
    MainWindow *parent;
};

#endif // VENTESCREDITEDITWINDOW_H
