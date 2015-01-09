#ifndef PRODUITSWINDOW_H
#define PRODUITSWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class ProduitsWindow;
}

class ProduitsWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProduitsWindow(QWidget *parent = 0);
    ~ProduitsWindow();
    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ProduitsWindow *ui;
    MainWindow* parent;
};

#endif // PRODUITSWINDOW_H
