#include "mainwindowlogin.h"
#include <QMessageBox>
#include "connexion.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
      MainWindowLogin w;
       Connection c;
       bool test=c.createconnect();

       if(test)
       {w.show();
           QMessageBox::information(nullptr, QObject::tr("database is open"),
                       QObject::tr("connection successful.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
       else
           QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                       QObject::tr("connection failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);


w.show();
       return a.exec();
}
