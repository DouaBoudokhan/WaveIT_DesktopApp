#ifndef MAINWINDOWLOGIN_H
#define MAINWINDOWLOGIN_H
#include "mainwindow.h"
#include <QMainWindow>
#include "user.h"
namespace Ui {
class MainWindowLogin;
}

class MainWindowLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowLogin(QWidget *parent = nullptr);
    ~MainWindowLogin();

private:
    Ui::MainWindowLogin *ui;
    MainWindow *mainwindow;
    user emp;
private slots:
     void on_login_clicked();
};

#endif // MAINWINDOWLOGIN_H
