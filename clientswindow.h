#ifndef CLIENTSWINDOW_H
#define CLIENTSWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class ClientsWindow;
}

class ClientsWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit ClientsWindow(QWidget *parent = 0);
    ~ClientsWindow();
    
private slots:
    void on_b_ajouter_clicked();

    void on_pushButton_clicked();

private:
    Ui::ClientsWindow *ui;
    MainWindow* parent;
};

#endif // CLIENTSWINDOW_H
