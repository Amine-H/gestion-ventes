#ifndef STOCKWINDOW_H
#define STOCKWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class StockWindow;
}

class StockWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit StockWindow(QWidget *parent = 0);
    ~StockWindow();
    
private slots:
    void on_b_showStock_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::StockWindow *ui;
    MainWindow *parent;
};

#endif // STOCKWINDOW_H
