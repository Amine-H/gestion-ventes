#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setModal(true);
    ui->l_password->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}

void Login::on_b_cancel_clicked()
{
    exit(0);
}

void Login::on_b_login_clicked()
{
    if(!ui->l_username->text().isEmpty() && !ui->l_password->text().isEmpty())
    {
        this->m_username=ui->l_username->text();
        this->m_password=ui->l_password->text();
        this->close();
    }
}

QString Login::getUsername()
{
    return m_username;
}

QString Login::getPassword()
{
    return m_password;
}
