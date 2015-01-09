#ifndef VENTESWINDOW_H
#define VENTESWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class VentesWindow;
}

class VentesWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit VentesWindow(QWidget *parent = 0);
    ~VentesWindow();
    
private slots:
    void on_i_produit_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_b_vente_clicked();

    void on_pushButton_2_clicked();
private:
    Ui::VentesWindow *ui;
    MainWindow *parent;
};

#endif // VENTESWINDOW_H
