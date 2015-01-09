#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT
    
public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    QString getUsername();
    QString getPassword();
    
private slots:
    void on_b_cancel_clicked();

    void on_b_login_clicked();

private:
    Ui::Login *ui;
    QString m_username,m_password;
};

#endif // LOGIN_H
