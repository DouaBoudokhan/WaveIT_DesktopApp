#include "mainwindowlogin.h"
#include "ui_mainwindowlogin.h"

MainWindowLogin::MainWindowLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowLogin)
{
    ui->setupUi(this);
      ui->password->setEchoMode(QLineEdit::Password);
}

MainWindowLogin::~MainWindowLogin()
{
    delete ui;
}
void MainWindowLogin::on_login_clicked(){

QString username = ui->username->text();
    QString password = ui->password->text();

    MainWindow::connected.setIdu(username.toInt());
    user myUser;
        int userId = myUser.login(username, password);
        QString userpos=myUser.pos(username,password);

        if (userId != -1) {
            // Login successful
            QMessageBox::information(this, "Login Successful", "Welcome, User id: " + QString::number(userId));
            QMessageBox::information(this, "Login Successful", "Welcome, User pos: " + userpos);
            hide();
            MainWindow *mainwindow = new MainWindow(username,userpos);
            mainwindow->show();
        } else {
            // Login failed
            QMessageBox::critical(this, "Login Failed", "Invalid username or password. Please try again.");
            // Add code here to handle the login failure, such as clearing the password field or displaying an error message
            ui->password->clear();
        }}
