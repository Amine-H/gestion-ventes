#ifndef ACHATSWINDOW_H
#define ACHATSWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class AchatsWindow;
}

class AchatsWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit AchatsWindow(QWidget *parent = 0);
    ~AchatsWindow();
    
private slots:
    void on_b_ajouter_clicked();

private:
    Ui::AchatsWindow *ui;
    MainWindow *parent;
};

#endif // ACHATSWINDOW_H
