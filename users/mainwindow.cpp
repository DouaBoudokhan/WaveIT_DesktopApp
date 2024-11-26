#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QSqlQueryModel>
#include <iostream>
#include <QCoreApplication>
#include <QDebug>
#include <QCompleter>
#include <QSqlError>
#include <QStringListModel>
#include <QRegExp>
#include <QSortFilterProxyModel>
#include <QCameraInfo>


#include "sportif.h"
#include <QTextDocument>
#include <QTextCursor>
#include <QPrinter>
#include <QTextTable>
#include <QPieSeries>
#include <QPair>
#include <iostream>

//doua//////////////////////////
#include "equipement.h"
#include <QPixmap>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QLabel>
#include "use.h"
#include <QFileDialog>
#include <QDir>

//
//ahmed////////////////////////
#include <QtQuick>




using namespace std;
//mohha
bool image_detect_res =false;
QString filename;
int nb_sportifs = 0;
int nb_actifs = 0;
QPair<int,QString>dummyPair(0,"") ;
//

user MainWindow::connected;
MainWindow::MainWindow(const QString& username,const QString& userpos, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),m_username(username),m_userpos(userpos)
{
    ui->setupUi(this);
    ui->Module_image->setIcon(QIcon("C:/Users/DOUA/Desktop/staff_pic.png"));
    ui->Module_image->setIconSize(QSize(105, 105)); // Set the size of the icon (optional)
      ui->inputArea->setText(m_username);
      ui->posit->setText(m_userpos);
    ui->table->setModel(user_all.display());
    QSortFilterProxyModel *proxyModel=new QSortFilterProxyModel(this);
          proxyModel->setDynamicSortFilter(true);
          proxyModel->setSourceModel(user_all.display());
          ui->table->setModel(proxyModel);
          ui->table->setSortingEnabled(true);
if (m_userpos=="Agent"){
    ui->Modules->setCurrentIndex(3);
    ui->employees->setHidden(true);
    ui->athletes->setHidden(true);
     ui->des->setText("this user is charged with the the managment of the materials, sports and event");
     //ui->user_image->setPixmap(QPixmap("C:/Users/DOUA/Desktop/staff_pic.png").scaled(200, 200));


}
if (m_userpos=="HR"){
     ui->Modules->setCurrentIndex(0);
    ui->pushButton_7->setHidden(true);
    ui->event->setHidden(true);
    ui->equipement->setHidden(true);
    ui->des->setText("this user is charged with the the managment of the human recourses ");
    //ui->user_image->setPixmap(QPixmap("C:/Users/DOUA/Desktop/staff_pic.png").scaled(60, 60));

}
if (m_userpos=="Admin"){
      ui->Modules->setCurrentIndex(1);
            ui->des->setText("this user is able to check everything  ");
            //ui->user_image->setPixmap(QPixmap("C:/Users/DOUA/Desktop/staff_pic.png").scaled(60, 60));

}




     //doua/////////////////
          ui->tableView_equip->setModel(Etmp.afficher());
          button();
          //Etmp.metiers();
          //Etmp.check();

          //use
          ui->tableView_use->setModel(utmp.afficher());
          button_use();
      //arduino_doua///////////////
          int ret=A.connect_arduino("COM3"); // lancer la connexion à arduino
          switch(ret){
          case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
              break;
          case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
             break;
          case(-1):qDebug() << "arduino is not available";
          }
           QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(output())); // permet de lancer
           int ret1=A1.connect_arduino("COM7"); // lancer la connexion à arduino
           switch(ret1){
           case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
               break;
           case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
              break;
           case(-1):qDebug() << "arduino is not available";
           }
           QObject::connect(A1.getserial(),SIGNAL(readyRead()),this,SLOT(update())); // permet de lancer


      //ala/////////
      ui->tableView_Sport->setModel(cstmp.afficher());
      button_ala();

          //ahmed////////
          ui->tableView_event->setModel(atmp.afficher());
          button_ahmed();


          //mohha
          QTimer *timer = new QTimer(this);
              connect(timer, SIGNAL(timeout()), this, SLOT(refreshActiveAthletesDataPeriodically()));
              timer->start(3000);

             reloadMainWindow(dummyPair);

}

MainWindow::~MainWindow()
{
    delete ui;

}

user currentUser;


void MainWindow::on_next_clicked() {
    int id = ui->del->text().toInt();


    bool found = currentUser.findUser(id);

    if (!found) {
       QMessageBox::critical(this, "Error", "User with this ID doesn't exist!");
    } else {
        ui->stackedWidget->setCurrentIndex(1);
        ui->namem->setText(currentUser.getFirstName());
        ui->prenm->setText(currentUser.getLastName());
        ui->mailm->setText(currentUser.getEmail());
        ui->motm->setText(currentUser.getPw());
        ui->userm->setText(currentUser.getUsername());
        ui->cinm->setText(currentUser.getCin());
        ui->phonem->setText(currentUser.getPhone());
    }
}

void MainWindow::on_modify_clicked() {

    QString first_name = ui->namem->text();
    QString last_name = ui->prenm->text();
    QString email = ui->mailm->text();
    QString pw = ui->motm->text();
    QString username = ui->userm->text();
    QString position = ui->pos->currentText();
    QString cin= ui->cinm->text();
    QString phone = ui->phonem->text();
    QDate bdate = ui->birth->date();


    if (first_name.isEmpty() || last_name.isEmpty() || username.isEmpty() || email.isEmpty() ||
        pw.isEmpty() || position.isEmpty()){
            QMessageBox::information(this, QObject::tr("ok"),
                                    QObject::tr("Fill all the data .\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
            return;
}
           if(phone<=10000000 && phone>=99999999)
           {
               QMessageBox::information(this, QObject::tr("ok"),
                                       QObject::tr("invalid phone number.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
               return;
           }
           if(  cin<=10000000 && cin>=99999999) {
        QMessageBox::information(this, QObject::tr("ok"),
                                QObject::tr("invalid cin.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }


    QRegExp emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
    if (!emailRegex.exactMatch(email)) {
        QMessageBox::information(this, QObject::tr("ok"),
                                QObject::tr("Incorrect email address.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }
    if (!user_all.unique(username)) {
           QMessageBox::information(this, QObject::tr("Error"),
                                   QObject::tr("Username already exists. Please choose a different username."));
           return ;
      }
    currentUser.setFirstName(first_name);
    currentUser.setLastName(last_name);
    currentUser.setEmail(email);
    currentUser.setPw(pw);
    currentUser.setUsername(username);
    currentUser.setCin(cin);
    currentUser.setPhone(phone);
    currentUser.setBDate(bdate);
    currentUser.setPosition(position);
    // Call the update function to update the data in the database
    bool success = currentUser.update();

    if (success) {
        // Show success message
        QMessageBox::information(this, "Success", "User data has been updated successfully!");
        ui->table->setModel(user_all.display());
         ui->stackedWidget->setCurrentIndex(2);
    } else {
        // Show error message
        QMessageBox::critical(this, "Error", "Failed to update user data!");
    }
}



void MainWindow::on_pushButton_3_clicked()
{
    user use;
    int iddel = ui->del->text().toInt();

    // Input validation
    if (iddel <= 0) {
        QMessageBox::information(this, QObject::tr("ok"),
                                QObject::tr("please enter a valid user.\n"
                                            "Click Cancel to exit."));

    }

    bool success = use.del(iddel);

    if (success)
    {
        ui->table->setModel(user_all.display());
        QMessageBox::information(this, QObject::tr("ok"),
                                QObject::tr("deleted successfully.\n"
                                            "Click Cancel to exit."));
    }
    else
    {
        QMessageBox::information(this, QObject::tr("ok"),
                                QObject::tr("can not delete user.\n"
                                            "Click Cancel to exit."));

    }
}

void MainWindow::on_add1_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_add_2_clicked()
{
    QString first_name = ui->name->text();
    QString last_name = ui->pren->text();
    QString username = ui->user->text();
    QString email = ui->mail->text();
    QString pw = ui->mot->text();
    QString position = ui->pos->currentText();
    QString phone = ui->phone->text();
    QDate bdate = ui->birth->date();
    QString cin = ui->cin->text();

    if (first_name.isEmpty() || last_name.isEmpty() || username.isEmpty() || email.isEmpty() ||
        pw.isEmpty() || position.isEmpty()){
            QMessageBox::information(this, QObject::tr("ok"),
                                    QObject::tr("Fill all the data .\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
            return;
}
           if( phone <= 0 ||
        ui->phone->text().length() != 8)
           {
               QMessageBox::information(this, QObject::tr("ok"),
                                       QObject::tr("invalid phone number.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
               return;
           }
           if(cin <= 0 || ui->cin->text().length() != 8) {
        QMessageBox::information(this, QObject::tr("ok"),
                                QObject::tr("invalid cin.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }


    QRegExp emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}\\b");
    if (!emailRegex.exactMatch(email)) {
        QMessageBox::information(this, QObject::tr("ok"),
                                QObject::tr("Incorrect email address.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
        return;
    }
    if (!user_all.unique(username)) {
           QMessageBox::information(this, QObject::tr("Error"),
                                   QObject::tr("Username already exists. Please choose a different username."));
           return ;
      }

   user user(first_name, last_name, email, username, pw, position, cin, phone, bdate);

    if (user.add()) {
        ui->table->setModel(user_all.display());
        qDebug() << "Utilisateur ajouté avec succès";
        QMessageBox::information(this, QObject::tr("OK"),
                                QObject::tr("Success"));
        ui->stackedWidget->setCurrentIndex(2);
    } else {
        qDebug() << "Erreur lors de l'ajout de l'utilisateur";
    }
}

void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_back_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_back_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_persp_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}

void MainWindow::on_acc_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString searchTerm = ui->search->text();
    QSqlQueryModel *searchResults = user_all.search(searchTerm);


        ui->table->setModel(searchResults);
}


//mohha///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void MainWindow::on_athletes_clicked()
{
    ui->Modules->setCurrentIndex(0);
    ui->crud_stack->setCurrentIndex(0);
    ui->Module_image->setIcon(QIcon("C:/Users/kamou/Desktop/doua/ic_sportifs.jpg"));
    ui->Module_image->setIconSize(QSize(110, 110)); // Set the size of the icon (optional)
}


void MainWindow::onDeleteButtonClicked(int id )
{
    // Handle button click for the given index
    bool test = Stmp.supprimer(id);
    if (test){
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Deleted"),QMessageBox::Cancel
                                 );
    reloadMainWindow(dummyPair);


    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                 QObject::tr("Error"),QMessageBox::Cancel
                                 );
    }
}


void MainWindow::onUpdateButtonClicked( Sportif sp )
{
    // Handle button click for the given index
          QStackedWidget *stack = ui->crud_stack;
          stack->setCurrentIndex(3);

          QLineEdit *ID = ui->update_id;
          QLineEdit* Name = ui->update_name;
          QLineEdit* Lastname = ui->update_lastname;
          QLineEdit* Age = ui->update_age;
          QLineEdit *Adress = ui->update_adress;
          QLineEdit* Mail = ui->update_mail;
          QComboBox *SportType = ui->update_typeSport;
          QLineEdit* PhoneNum = ui->update_phone;
          QComboBox *Level = ui->update_level;

           qDebug() <<"sportifid = "<< sp.getId();
           ID->setText(QString::number(sp.getId()));
           Name->setText(sp.getNom());
           Lastname->setText(sp.getPrenom());
           Age->setText(QString::number(sp.getAge()));
           Adress->setText(sp.getAdresse());
           Mail->setText(sp.getMail());
           SportType->setCurrentText(sp.getTypeSport());
           PhoneNum->setText(sp.getNumTel());
           Level->setCurrentText(sp.getNiveau());
}


void MainWindow::on_addBTN_clicked()
{
      QStackedWidget *stack = ui->crud_stack;
            stack->setCurrentIndex(2);

}


void MainWindow::on_add_addBTN_clicked()
{
   //auto generate id
    int id = nb_sportifs+1;
   //get text fields
   QLineEdit* name = ui->add_name;
   QLineEdit* lastname = ui->add_lastname;
   QLineEdit* age = ui->add_age;
   QLineEdit *adress = ui->add_adress;
    QLineEdit* mail = ui->add_mail;
   QComboBox *sportType = ui->add_typeSport;
    QLineEdit* phoneNum = ui->add_phone;
    QComboBox *level = ui->add_level;

    QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Error: Couldn't open the image file";
        }

      QVariant imageData = QVariant(file.readAll());



    //validation
    bool form_test=true;

    if (name->text().isEmpty() || lastname->text().isEmpty() || age->text().isEmpty() ||
           adress->text().isEmpty() || mail->text().isEmpty() || phoneNum->text().isEmpty() ) {
            form_test=false;
           QMessageBox::warning(this, "Validation Error", "Please fill in all required fields.");
       }

        if (image_detect_res==false){
            QMessageBox::warning(this, "Validation Error", "Please add a valid image.");
              form_test=false;
        }


    int ageValue = age->text().toInt();
        if (ageValue <= 3 || ageValue > 80) {
            form_test=false;
           age->setStyleSheet("border-radius: 5px ;"
                              "background-color: rgb(242, 247, 255);"
                              "border-bottom-color: rgb(255, 0, 0);");
        }else
            age->setStyleSheet("border-radius: 5px ;"
                               "background-color: rgb(242, 247, 255);");


    QRegularExpression emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
       if (!emailRegex.match(mail->text()).hasMatch()) {
           form_test=false;
          mail->setStyleSheet("border-radius: 5px ;"
                              "background-color: rgb(242, 247, 255);"
                              "border-bottom-color: rgb(255, 0, 0);");
       }else
           mail->setStyleSheet("border-radius: 5px ;"
                              "background-color: rgb(242, 247, 255);");
    phoneNum->text().toInt();
      if (phoneNum->text().length() != 8) {
          form_test=false;
           phoneNum->setStyleSheet("border-radius: 5px ;"
                                   "background-color: rgb(242, 247, 255);"
                                   "border-bottom-color: rgb(255, 0, 0);");
      }else
          phoneNum->setStyleSheet("border-radius: 5px ;"
                             "background-color: rgb(242, 247, 255);");

    if(form_test==true){
        Sportif sp(id , name->text(), lastname->text(), age->text().toInt(), adress->text(),mail->text(),phoneNum->text(), level->currentText(), sportType->currentText(),imageData);
        bool test = sp.ajouter();

        if (test){
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Add successful\n click cancel to exit."),QMessageBox::Cancel
                                     );
        reloadMainWindow(dummyPair);
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                     QObject::tr("add not successful\n click cancel to exit."),QMessageBox::Cancel
                                     );
        }
    }
}
void MainWindow::on_update_updateBTN_clicked()
{

    //get text fields
    QLineEdit *ID = ui->update_id;
     QLineEdit* name = ui->update_name;
     QLineEdit* lastname = ui->update_lastname;
     QLineEdit* age = ui->update_age;
     QLineEdit *adress = ui->update_adress;
      QLineEdit*mail = ui->update_mail;
     QComboBox *sportType = ui->update_typeSport;
      QLineEdit* phoneNum = ui->update_phone;
      QComboBox *level = ui->update_level;


     //validation
     bool form_test=true;

     if (name->text().isEmpty() || lastname->text().isEmpty() || age->text().isEmpty() ||
            adress->text().isEmpty() || mail->text().isEmpty() || phoneNum->text().isEmpty()) {
             form_test=false;
            QMessageBox::warning(this, "Validation Error", "Please fill in all required fields.");
        }
     int ageValue = age->text().toInt();
         if (ageValue <= 3 || ageValue > 80) {
             form_test=false;
            age->setStyleSheet("border-radius: 5px ;"
                               "background-color: rgb(242, 247, 255);"
                               "border-bottom-color: rgb(255, 0, 0);");
         }else
             age->setStyleSheet("border-radius: 5px ;"
                                "background-color: rgb(242, 247, 255);");


     QRegularExpression emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        if (!emailRegex.match(mail->text()).hasMatch()) {
            form_test=false;
           mail->setStyleSheet("border-radius: 5px ;"
                               "background-color: rgb(242, 247, 255);"
                               "border-bottom-color: rgb(255, 0, 0);");
        }else
            mail->setStyleSheet("border-radius: 5px ;"
                               "background-color: rgb(242, 247, 255);");


     phoneNum->text().toInt();
       if (phoneNum->text().length() != 8 || phoneNum->text().toLong()==0) {
           form_test=false;
            phoneNum->setStyleSheet("border-radius: 5px ;"
                                    "background-color: rgb(242, 247, 255);"
                                    "border-bottom-color: rgb(255, 0, 0);");
       }else
           phoneNum->setStyleSheet("border-radius: 5px ;"
                              "background-color: rgb(242, 247, 255);");




     if(form_test==true){

         Sportif sp(ID->text().toInt() , name->text(), lastname->text(), age->text().toInt(), adress->text(),mail->text(),phoneNum->text(), level->currentText(), sportType->currentText());
         qDebug() <<"sportifid = "<< sp.getId();
         bool test = sp.modifier(sp);

         if (test){
             QMessageBox::information(nullptr, QObject::tr("ok"),
                                      QObject::tr("modification successful"),QMessageBox::Cancel
                                      );
         reloadMainWindow(dummyPair);


         }
         else {
             QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                      QObject::tr("modification not successful"),QMessageBox::Cancel
                                      );
         }

     }

}


void MainWindow::getDistanceApi(QString init_pos , QString curr_pos){

    QStringList init_coordinates =  init_pos.split(',');
    QStringList curr_coordinates =  curr_pos.split(',');

    for (int i = 0 ; i<2 ; i++){
        init_coordinates[i]=init_coordinates[i].trimmed();
        curr_coordinates[i] = curr_coordinates[i].trimmed();
    }


        qDebug() << " init_coordinates : " <<init_coordinates;
        qDebug() << "curr_coordinates: " << curr_coordinates;

    float distance = acos(sin( init_coordinates[0].toFloat())*sin(curr_coordinates[0].toFloat())+cos(init_coordinates[0].toFloat())*cos(curr_coordinates[0].toFloat())*cos(curr_coordinates[1].toFloat()-init_coordinates[1].toFloat()))*6371;

    qDebug() << "distance " << distance;

           if (distance >5 ){
               char data = '1';
                //A.write_to_arduino(QByteArray::fromRawData(&data,1));
               qDebug()<< "mohha arduino returned 1";
           }
}

void MainWindow::refreshActiveAthletesDataPeriodically(){

    // FOR alaaa : baddel l current position mtaa l athlete lenna fl tab mteii;
    // fl ui 7ell l "active athletes" hawka bouton lfouk fl athletes tab
    //deja aamatlek fl class mteei 2 fct "sendInitPos" w "SendCurrentPos" bech t updati fihom l sportif
    // l "sendCurrentPos" Lenna aamalha bech ttrefresha koll 3s
    // l "sendinitPos" dabber rasek win thottha

    //exp   Stmp.sendCurrentPos(1, "36.659710, 9.810880");
    //exp   Stmp.sendInitPos(1, "36.659710, 9.810880");


    qDebug()<< "this code is refreshed every 3s ";


    QSortFilterProxyModel *proxyModel_active=new QSortFilterProxyModel(this);
    proxyModel_active->setDynamicSortFilter(true);
    proxyModel_active->setSourceModel(Stmp.afficherActifs());
    ui->sportif_actif_tableview->setModel(proxyModel_active);
    ui->sportif_actif_tableview->setSortingEnabled(true);

      nb_actifs = ui->sportif_actif_tableview->model()->rowCount();

      //code of putting button to each
      for (int row = 0; row < nb_actifs; ++row)
      {
          QPushButton *pos_button = new QPushButton("Get Position", this);
         pos_button->setStyleSheet("QPushButton {"
                                "background-color:#437FF7;border-radius :5px; "
                                "color : #fff;"
                                            "}");



         connect(pos_button, &QPushButton::clicked, [this, row]() {
             QString init_pos = ui->sportif_actif_tableview->model()->index(row,6).data().toString();
             QString curr_pos= ui->sportif_actif_tableview->model()->index(row,7).data().toString();
             getDistanceApi(init_pos, curr_pos);
         });

          ui->sportif_actif_tableview->setIndexWidget(ui->sportif_actif_tableview->model()->index(row, 8), pos_button);


      }

}
void MainWindow::reloadMainWindow(QPair <int,QString> filter)
{

    QStackedWidget *stack = ui->crud_stack;
      stack->setCurrentIndex(0);

      QSortFilterProxyModel *proxyModel=new QSortFilterProxyModel(this);
      proxyModel->setDynamicSortFilter(true);
      proxyModel->setSourceModel(Stmp.afficher(filter));
      ui->tableView->setModel(proxyModel);
      ui->tableView->setSortingEnabled(true);


nb_sportifs = ui->tableView->model()->rowCount();

    // Create a QPushButton for each cell in the specified column
    for (int row = 0; row < nb_sportifs; ++row)
    {

        QLabel * label_img = new QLabel();
        QByteArray image_data =ui->tableView->model()->data(ui->tableView->model()->index(row, 12)).toByteArray();
        QPixmap *pixmap= new  QPixmap();
        pixmap->loadFromData(image_data);
        label_img->setPixmap(*pixmap);



        QPushButton *update_button = new QPushButton("Update", this);
        update_button->setStyleSheet("QPushButton {"
                              "background-color:#437FF7;border-radius :5px; "
                              "color : #fff;"
                                          "}");
        QPushButton *delete_button = new QPushButton("Delete", this);
        delete_button->setStyleSheet("QPushButton {"
                              "background-color:#F74343;border-radius :5px; "
                              "color : #fff;"
                                          "}");
        connect(update_button, &QPushButton::clicked, [this, row]() {
            //params
            Sportif sp ;

            sp.setId(ui->tableView->model()->index(row,0).data().toInt());
            sp.setNom(ui->tableView->model()->index(row,1).data().toString());
            sp.setPrenom(ui->tableView->model()->index(row,2).data().toString());
            sp.setAdresse(ui->tableView->model()->index(row,3).data().toString());
            sp.setMail( ui->tableView->model()->index(row,4).data().toString());
            sp.setTypeSport(ui->tableView->model()->index(row,5).data().toString());
            sp.setNumTel(ui->tableView->model()->index(row,6).data().toString());
            sp.setFrequency( ui->tableView->model()->index(row,7).data().toInt());
            sp.setNiveau(ui->tableView->model()->index(row,8).data().toString());
            sp.setAge( ui->tableView->model()->index(row,9).data().toInt());
            onUpdateButtonClicked(sp);
        });
        connect(delete_button, &QPushButton::clicked, [this, row]() {
            onDeleteButtonClicked(ui->tableView->model()->index(row , 0).data().toInt());
        });

        ui->tableView->setIndexWidget(ui->tableView->model()->index(row, 10), update_button);
        ui->tableView->setIndexWidget(ui->tableView->model()->index(row, 11), delete_button);
        ui->tableView->setIndexWidget(ui->tableView->model()->index(row, 12), label_img);
}


    ui->add_name->clear();
    ui->add_lastname->clear();
    ui->add_age->clear();
    ui->add_adress->clear();
    ui->add_mail->clear();
    ui->add_phone->clear();



    QSqlQuery eventQuery;
    eventQuery.prepare("SELECT * FROM event where done = 0");
    eventQuery.exec();

    while (eventQuery.next()){
        qDebug()<<eventQuery.value("winner") ;
        if(eventQuery.value("winner") != ""){
            Event *event = new Event(eventQuery.value("id_event").toInt() ,eventQuery.value("nom").toString() ,eventQuery.value("age").toInt(),eventQuery.value("lieu").toString(),eventQuery.value("DATE_EVENT").toDate(),eventQuery.value("duree").toInt(),eventQuery.value("type").toString(),eventQuery.value("niveau").toString(),eventQuery.value("PRIX_INSCRIT").toInt());
            event->set_winner(eventQuery.value("winner").toInt());
            bool res  = event->UpdateAthlete();
            event->set_done(1);
            event->modifier_done();
            if (res==true){
                reloadMainWindow(dummyPair);
            }
            delete event;
        }
    }
}

void MainWindow::on_sportifs_back_clicked()
{
    QStackedWidget *stack = ui->crud_stack;
          stack->setCurrentIndex(0);
}

void MainWindow::on_sportifs_back2_clicked()
{
    QStackedWidget *stack = ui->crud_stack;
          stack->setCurrentIndex(0);
}

void MainWindow::on_add_deleteAll_clicked()
{


        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete all Athletes?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            bool test = Stmp.supprimerTous();
            reloadMainWindow(dummyPair);

            if (test){
                QMessageBox::information(nullptr, QObject::tr("DONE"),
                            QObject::tr("Everything has been deleted.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            } else {
                QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                            QObject::tr("Error.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
}

void MainWindow::on_sorting_box_currentTextChanged(const QString &arg1)
{
    qDebug()<< arg1;
    if (arg1=="ID") ui->tableView->sortByColumn(0,Qt::AscendingOrder);
    if (arg1=="NAME") ui->tableView->sortByColumn(1,Qt::AscendingOrder);
    if (arg1=="AGE") ui->tableView->sortByColumn(9,Qt::AscendingOrder);
    if (arg1=="FREQUENCY") ui->tableView->sortByColumn(7,Qt::AscendingOrder);

}

void MainWindow::on_search_btn_clicked()
{
    int search_crit = ui->search_crit->currentIndex();
    QPair<int ,QString> search_param =qMakePair(search_crit,ui->searchBox->text());
   reloadMainWindow(search_param);
}

void MainWindow::on_searchBox_textChanged(const QString &arg1)
{
    int search_crit = ui->search_crit->currentIndex();
    QPair<int ,QString> search_param =qMakePair(search_crit,arg1);
    qDebug()<<search_param.first<<search_param.second;
   reloadMainWindow(search_param);
}

void MainWindow::on_pdf_sportifs_clicked()
{

        // Create a QTextDocument
        QTextDocument doc;

        // Create HTML content with styling
        QString html = "<html><head><style>"
                       "body { background-color: #f5faff; border: 2px solid black; }"
                       "table { width: 100%; }"
                       "th, td { border: 1px solid black; padding: 8px; }"
                       "th { background-color: #e3f7fc; text-transform: uppercase; font-size: 20px; color: #1f3a93; }"
                       "td { text-align: left; }"
                       "h1 { text-align: center; margin-bottom: 20px; margin-top: 20px; font-size: 28px; color: #1f3a93; }"
                       "h2 { text-align: center; margin-bottom: 40px; font-size: 24px; color: #1f3a93; }"
                       "tr:nth-child(even) { background-color: #dcf3fa; }"
                       "tr:nth-child(odd) { background-color: #b3d9e6; }"
                       "</style></head><body>"
                       "<h1>Athletes</h1>"
                       "<h2>Here you can find all the necessary information about the athletes</h2>"
                       "<br />"
                       "<table>"
                       "<tr>"
                       "<th>ID</th>"
                       "<th>Name</th>"
                       "<th>LastName</th>"
                       "<th>Age</th>"
                       "<th>Adress</th>"
                       "<th>Phone</th>"
                       "<th>Level</th>"
                       "<th>Email</th>"
                       "<th>Sport type</th>"
                       "</tr>";

        // Fetch data from the database
        QSqlQuery query("SELECT id , name, lastname, age , adress , phone , lvl , email , sport_type  FROM sportifs");
        while (query.next()) {
            html += "<tr>";
            for (int i = 0; i < query.record().count(); ++i) {
                html += "<td>" + query.value(i).toString() + "</td>";
            }
            html += "</tr>";
        }
        html += "</table></body></html>";

        doc.setHtml(html);
        // Create a printer
            QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);



            //douaa please set the path of ur pc
            printer.setOutputFileName("C:/Users/Mohamed/Desktop/sportifs.pdf");
            //************************************************************************





            // Print the QTextDocument to the PDF
            doc.print(&printer);

            // Check if the document is empty
            if (doc.isEmpty()) {

                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                         QObject::tr("PDF didn't export successfully"),QMessageBox::Cancel
                                         );

            }

            else{
                qDebug() << "PDF exported successfully.";
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("PDF exported successfully"),QMessageBox::Cancel
                                     );
        reloadMainWindow(dummyPair);
            }


}
void MainWindow::on_commandLinkButton_clicked()
{

    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.15);
    QSqlQuery query =Stmp.getStatsQuery()  ;
    int max;
    while(query.next()){
       QPieSlice *slice =  series->append(query.value(0).toString(),query.value(1).toInt());
       slice->setLabelVisible(true);
       if (query.at()==0 || query.value(1).toInt()==max){
           slice->setExploded(true) ;
           max= query.value(1).toInt();
       }
    }
    QChart *chart= new QChart();
    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setTitle("statistics");
    chart->setVisible(true);
    chart->setTheme(QChart::ChartTheme::ChartThemeBlueNcs);
    QChartView *chartview=new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setWindowTitle("athletes number / level");
    chartview->resize(1600,1000);
    chartview->setVisible(true);
}



void MainWindow::on_add_sportif_upload_image_clicked()
{
     filename=QFileDialog::getOpenFileName(this,tr("Upload photo"),"",tr("Images(*.png *.jpg *.jpeg)"));
    if (QString::compare(filename,QString())!=0){
        QImage image ;
        bool valid = image.load(filename);

        QFile file(filename);
            if (!file.open(QIODevice::ReadOnly)) {
                qDebug() << "Error: Couldn't open the image file";
            }

          QByteArray imageData = file.readAll();
          QNetworkAccessManager* manager = new QNetworkAccessManager();
              QUrl url("https://faceanalyzer-ai.p.rapidapi.com/faceanalysis");
              QNetworkRequest request(url);

              request.setRawHeader("X-RapidAPI-Key", "64c0494030msh6a5799bba8d7ab9p128210jsnd3ea3164b1a5"); // Replace YOUR_API_KEY_HERE with your actual API key

              QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

              QHttpPart imagePart;
              imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg")); // Assuming the image is JPEG
              imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));


              imagePart.setBody(imageData);
              multiPart->append(imagePart);

              QNetworkReply *reply = manager->post(request, multiPart);
              multiPart->setParent(reply); // Ensure multiPart is deleted when reply is deleted

              // Wait for the reply to finish
                 QEventLoop loop;
                 QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
                 loop.exec();

                 QString outputText;
                 if (reply->error() == QNetworkReply::NoError) {
                     QByteArray responseData = reply->readAll();
                     qDebug() << "Response: " << responseData;

                     // Parse the JSON response
                     QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
                     QJsonObject jsonObject = jsonResponse.object();


                     // Check if faces are detected
                     QJsonArray facesArray = jsonObject["body"].toObject()["faces"].toArray();
                      qDebug()<<facesArray.size();
                     if (facesArray.isEmpty() ) {
                         qDebug()<<"no face detected";
                         image_detect_res = false;

                     }
                     else{
                         qDebug()<< "face detected";
                         image_detect_res =true;
                     }
        if (valid){
            qDebug()<<filename;
            image=image.scaledToWidth(ui->add_sportif_img->width(),Qt::SmoothTransformation);
            ui->add_sportif_img->setPixmap(QPixmap::fromImage(image));
        }
        else{
            ui->add_sportif_img->setText("error uploading the photo ...");
        }
    }
}}

void MainWindow::on_reload_data_clicked()
{
    reloadMainWindow(dummyPair);
}

void MainWindow::on_active_sportifs_clicked()
{
    QStackedWidget *stack = ui->crud_stack;
    stack->setCurrentIndex(1);

}


//mohha///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//doua///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_valider_equip_clicked()
{
    int id = ui->l_id->text().toInt();
    QString nom = ui->l_nom->text();
    QString imagepath = ui->l_image->text();
    int quantite = ui->l_quatite->text().toInt();
    QString etat = ui->l_etat->currentText();
    int nb = 0;
    QString type = ui->l_type->currentText();
    int prix = ui->l_prix->text().toInt();
    QString date = ui->l_date->text();

    equipement equi = Etmp.getEquipementById(id);
    if (equi.get_id() != -1) {
        QMessageBox::critical(this, "Error", "This ID exists already!");
        ui->l_id->clear();
    } else if (id < 0) {
        QMessageBox::critical(this, "Error", "The ID cannot be negative!");
    } else if (nom.isEmpty()) {
        QMessageBox::critical(this, "Error", "The name cannot be empty!");
    } else if (imagepath.isEmpty()) {
        QMessageBox::critical(this, "Error", "The image path is missing!");
    } else if (quantite <= 0) {
        QMessageBox::critical(this, "Error", "The quantity must be greater than 0.");
        ui->l_quatite->clear();

    } else if (prix <= 0) {
        QMessageBox::critical(this, "Error", "The price must be greater than 0.");
        ui->l_prix->clear();
    } else {
        equipement e(id, nom, imagepath, quantite, etat, nb, type, prix, date);
        bool test = e.ajouter();
        if (test) {
            ui->tableView_equip->setModel(Etmp.afficher());
            button();



            QMessageBox::information(nullptr, QObject::tr("DONE"),
                QObject::tr("An equipment has been added.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
            ui->l_id->clear();
            ui->l_nom->clear();
            ui->l_image->clear();
            ui->l_quatite->clear();

            ui->l_nb->clear();

            ui->l_prix->clear();
            ui->equipement_integ->setCurrentIndex(1);

        } else {
            QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                QObject::tr("Error.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
}



void MainWindow::on_image_ajouter_equi_clicked()
{
    QString selectedImagePath = QFileDialog::getOpenFileName(this, tr("Select Image"), QDir::homePath(), tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (!selectedImagePath.isEmpty()) {
        ui->l_image->setText(selectedImagePath);
    } else {
        QMessageBox::critical(this, "Error", "No image selected!");
    }
}

void MainWindow::on_quitter_equip_clicked()
{
   close();
}



void MainWindow::on_modifier_equip_clicked(equipement e)
{

    if (e.get_id()==-1){
       QMessageBox::critical(this, "Error", "This ID doesn't exist!");
    }else{
    ui->equipement_integ->setCurrentIndex(4);
    ui->id->setText(QString::number(e.get_id()));
    ui->nom->setText(e.get_nom());
    ui->image->setText(e.get_imagepath());
    ui->quantite->setText(QString::number(e.get_quantite()));
    ui->etat->setCurrentText(e.get_etat());
    ui->nb->setText(QString::number(e.get_nb()));
    ui->type->setCurrentText(e.get_type());
    ui->prix->setText(QString::number(e.get_prix()));
    ui->date->setDate(QDate::fromString(e.get_date(), "yyyy-MM-dd"));}
}




void MainWindow::on_delete_equip_clicked(int id)
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete all equipment?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
    bool test=Etmp.supprimer(id);

    if (test){
        ui->tableView_equip->setModel(Etmp.afficher());
        button();

        QMessageBox::information(nullptr, QObject::tr("DONE"),
                    QObject::tr("An equipement's been deleted.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }else
        QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                    QObject::tr("Error.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->equipement_integ->setCurrentIndex(1);}
}

void MainWindow::on_delete_all_equip_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete all equipment?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        bool test = Etmp.supprimer_all();

        if (test){
            ui->tableView_equip->setModel(Etmp.afficher());
            button();
            QMessageBox::information(nullptr, QObject::tr("DONE"),
                        QObject::tr("Everything has been deleted.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                        QObject::tr("Error.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
}




void MainWindow::on_modify_equip_clicked()
{
    int id=ui->id->text().toInt();
    QString nom=ui->nom->text();
    QString imagepath=ui->image->text();
    int quantite=ui->quantite->text().toInt();
    QString etat=ui->etat->currentText();
    int nb=ui->nb->text().toInt();
    QString type=ui->type->currentText();
    int prix=ui->prix->text().toInt();
    QString date=ui->date->text();
    equipement equi=Etmp.getEquipementById(id);
    if (nom.isEmpty()) {
        QMessageBox::critical(this, "Error", "The name cannot be empty!");
    } else if (imagepath.isEmpty()) {
        QMessageBox::critical(this, "Error", "The image path is missing!");
    } else if (quantite <= 0) {
        QMessageBox::critical(this, "Error", "The quantity must be greater than 0.");
    } else if (prix <= 0) {
        QMessageBox::critical(this, "Error", "The price must be greater than 0.");
    } else {
        qDebug()<<etat;

        if (etat=="recondionned"){
            Etmp.update_nb(id);
            nb=0;
        }
    equipement e(id,nom,imagepath,quantite,etat,nb,type,prix,date);
    bool test=e.update();

    if (test){
        ui->tableView_equip->setModel(Etmp.afficher());
        button();
        QMessageBox::information(nullptr, QObject::tr("DONE"),
                    QObject::tr("An equipement's been modified.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }else
        QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                    QObject::tr("Error.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->equipement_integ->setCurrentIndex(1);}
}

void MainWindow::on_image_modifier_equi_clicked()
{
    QString selectedImagePath = QFileDialog::getOpenFileName(this, tr("Select Image"), QDir::homePath(), tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (!selectedImagePath.isEmpty()) {
        ui->image->setText(selectedImagePath);
    } else {
        QMessageBox::critical(this, "Error", "No image selected!");
    }
}


void MainWindow::on_equipement_clicked()
{
    ui->Modules->setCurrentIndex(4);
    ui->tableView_equip->setModel(Etmp.afficher());
    button();
    ui->Module_image->setIcon(QIcon("C:/Users/kamou/Desktop/doua/equi.png"));
    ui->Module_image->setIconSize(QSize(110, 110)); // Set the size of the icon (optional)
}



void MainWindow::on_sort_button_equip_clicked()
{
    QString term = ui->sort_equip->currentText();
    if (term=="date of purchase"){
        ui->tableView_equip->setModel(Etmp.sort("date_e"));
        button();
    }
    if (term=="number of users"){
        ui->tableView_equip->setModel(Etmp.sort("nb"));
        button();
    }
    if (term=="ID"){
        ui->tableView_equip->setModel(Etmp.sort("id"));
        button();
    }

}


void MainWindow::on_pdf_equip_clicked()
{

    if (Etmp.exportToPdf()==true) {
        QMessageBox::information(this, "Done", "PDF exported successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to export PDF!");
    }
}



void MainWindow::on_back3_equip_clicked()
{
    ui->equipement_integ->setCurrentIndex(1);

}

void MainWindow::on_back1_equip_clicked()
{
    ui->equipement_integ->setCurrentIndex(1);
}





void MainWindow::button(){
for (int row = 0; row < ui->tableView_equip->model()->rowCount(); ++row){
        QPushButton *update_button = new QPushButton("Update", this);
        update_button->setStyleSheet("QPushButton {"
                              "background-color:#437FF7;border-radius :5px; "
                              "color : #fff;"
                                          "}");
        update_button->setFixedSize(90, 35);
        QPushButton *delete_button = new QPushButton("Delete", this);
        delete_button->setStyleSheet("QPushButton {"
                              "background-color:#ef1f22;border-radius :5px; "
                              "color : #fff;"
                                          "}");
        delete_button->setFixedSize(90, 35);
        connect(update_button, &QPushButton::clicked, [this, row]() {
            equipement e ;

            e.setid(ui->tableView_equip->model()->index(row,0).data().toInt());
            e.setnom(ui->tableView_equip->model()->index(row,1).data().toString());
            e.setimagepath(ui->tableView_equip->model()->index(row,2).data().toString());
            e.setquantite(ui->tableView_equip->model()->index(row,3).data().toInt());
            e.setetat( ui->tableView_equip->model()->index(row,4).data().toString());
            e.setnb(ui->tableView_equip->model()->index(row,5).data().toInt());
            e.settype(ui->tableView_equip->model()->index(row,6).data().toString());
            e.setprix( ui->tableView_equip->model()->index(row,7).data().toInt());
            e.setdate(ui->tableView_equip->model()->index(row,8).data().toString());


            on_modifier_equip_clicked(e);
        });
        connect(delete_button, &QPushButton::clicked, [this, row]() {
            on_delete_equip_clicked(ui->tableView_equip->model()->index(row , 0).data().toInt());
        });

        ui->tableView_equip->setIndexWidget(ui->tableView_equip->model()->index(row, 9), update_button);
        ui->tableView_equip->setIndexWidget(ui->tableView_equip->model()->index(row, 10), delete_button);

        //affichage image//

                QString imagePath = ui->tableView_equip->model()->index(row , 2).data().toString();
                QLabel *label= new QLabel(this);
                QPixmap image(imagePath);
                label->setPixmap(image);
                ui->tableView_equip->setIndexWidget(ui->tableView_equip->model()->index(row,2), label);


}

}





void MainWindow::on_sort_equip_currentTextChanged(const QString &arg)
{
    QString term = ui->sort_equip->currentText();
    if (arg=="Date of purchase"){
        ui->tableView_equip->setModel(Etmp.sort("date_e"));
        button();

    }else if (arg=="Number of users"){
        ui->tableView_equip->setModel(Etmp.sort("nb"));
        button();

    }else if (term=="ID"){
        ui->tableView_equip->setModel(Etmp.sort("id"));
        button();
    }
}


void MainWindow::on_search_equip_textChanged(const QString &arg1) {
    if (arg1.isEmpty()) {
        // If the search box is empty, show all entries again
        ui->tableView_equip->setModel(Etmp.afficher());
        button(); // Call the button function to show images
    } else {
        // If the search box has text, filter the data based on the text
        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(Etmp.afficher()); // Set the original model as the source
        proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive); // Set case-insensitive filter
        proxyModel->setFilterKeyColumn(1); // Set the column to filter

        // Set the proxy model as the model for the table view
        ui->tableView_equip->setModel(proxyModel);

        // Apply filtering based on the text
        proxyModel->setFilterFixedString(arg1);

        button(); // Call the button function to show images
    }
}





void MainWindow::on_stat_equip_clicked()
{
    Etmp.stat();

}



void MainWindow::on_ajouter_equip_clicked()
{
    ui->equipement_integ->setCurrentIndex(0);
    ui->l_nb->setText(QString::number(0));


}

void MainWindow::on_send_clicked()
{
    QString message = ui->question->toPlainText();

    message = message.trimmed();
    if (message.isEmpty())
    {
        ui->question->clear();
        return;
    }
    ui->answer->append("<font color=\"grey\">User:</font> " + message);
    ui->question->clear();

    QString reply =  Etmp.generateChatbotReply(message);
    if (!reply.isEmpty())
    {
        ui->answer->append("<font color=\"grey\">Chatbot:</font> " + reply);
    }
}


void MainWindow::on_chatbot_clicked()
{
    ui->equipement_integ->setCurrentIndex(2);

}

void MainWindow::on_back_chatbot_clicked()
{
    ui->equipement_integ->setCurrentIndex(1);

}

//crud table use//////

void MainWindow::on_valider_use_clicked()
{
    QString both=ui->id_sportif_use->currentText();
    QString nom=(both.split(" ")).first();
    QString nom_equip=ui->id_equip_use->currentText();
    int id_e = utmp.chercherIDE(nom_equip);
    //qDebug()<<id_e;
    int id_s = utmp.chercherIDS(nom);
    //qDebug()<<id_s;

    QString date = ui->date_use->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    //qDebug()<<date;
    QString image = ui->image_use->text();
    QString verif = ui->verif_use->text();



        use u(id_e, id_s, date, image,verif);
        bool test = u.ajouter();
        if (test) {
            ui->tableView_use->setModel(utmp.afficher());
            button_use();


            QMessageBox::information(nullptr, QObject::tr("DONE"),
                QObject::tr("successfully added.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
            ui->id_equip_use->clear();
            ui->id_sportif_use->clear();
            ui->date_use->clear();
            ui->image_use->clear();

            ui->equipement_integ->setCurrentIndex(5);

        } else {
            QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                QObject::tr("Error.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
        }

}

void MainWindow::on_add_use_clicked()
{
    QVector<QString> equipmentIDs = utmp.retrieve_id_equip();
    QVector<QString> sportifIDs = utmp.retrieve_id_sportif();


    ui->id_equip_use->clear();
    ui->id_sportif_use->clear();

    for (int i = 0; i < equipmentIDs.size(); ++i) {
        ui->id_equip_use->addItem(equipmentIDs[i]);
    }

    for (int i = 0; i < sportifIDs.size(); ++i) {
        ui->id_sportif_use->addItem(sportifIDs[i]);
    }

    ui->verif_use->setText("No");
    ui->equipement_integ->setCurrentIndex(3);
}

void MainWindow::button_use(){
for (int row = 0; row < ui->tableView_use->model()->rowCount(); ++row){
        QPushButton *update_button = new QPushButton("Update", this);
        update_button->setStyleSheet("QPushButton {"
                              "background-color:#437FF7;border-radius :5px; "
                              "color : #fff;"
                                          "}");
        update_button->setFixedSize(110, 45);
        QPushButton *delete_button = new QPushButton("Delete", this);
        delete_button->setStyleSheet("QPushButton {"
                              "background-color:#ef1f22;border-radius :5px; "
                              "color : #fff;"
                                          "}");
        delete_button->setFixedSize(110, 45);
        connect(update_button, &QPushButton::clicked, [this, row]() {
            use u ;

            u.setid_equip(ui->tableView_use->model()->index(row,0).data().toInt());
            u.setid_sportif(ui->tableView_use->model()->index(row,1).data().toInt());
            u.setdate(ui->tableView_use->model()->index(row,2).data().toString());
            u.setimage(ui->tableView_use->model()->index(row,3).data().toString());
            u.setverif(ui->tableView_use->model()->index(row,4).data().toString());

            on_modifier_use_clicked(u);
        });
        connect(delete_button, &QPushButton::clicked, [this, row]() {
            on_delete_use_clicked(ui->tableView_use->model()->index(row , 0).data().toInt());
        });

        ui->tableView_use->setIndexWidget(ui->tableView_use->model()->index(row, 5), update_button);
        ui->tableView_use->setIndexWidget(ui->tableView_use->model()->index(row, 6), delete_button);

        //affichage image//

                QString imagePath = ui->tableView_use->model()->index(row , 3).data().toString();
                QLabel *label= new QLabel(this);
                QPixmap image(imagePath);
                label->setPixmap(image);
                ui->tableView_use->setIndexWidget(ui->tableView_use->model()->index(row,3), label);


}

}

void MainWindow::on_modifier_use_clicked(use u)
{
    ui->id_equip_usem->addItem(utmp.chercherNOME(u.getid_equip()));
    ui->id_sportif_usem->addItem(utmp.chercherNOMS(u.getid_sportif()));

    ui->id_equip_usem->setCurrentText(utmp.chercherNOME(u.getid_equip()));
    ui->id_sportif_usem->setCurrentText(utmp.chercherNOMS(u.getid_sportif()));
    ui->date_usem->setDateTime(QDateTime::fromString(u.getdate(), "yyyy-MM-dd hh:mm"));
    ui->image_usem->setText(u.getimage());
    ui->verif_usem->setText(u.getverif());
    ui->equipement_integ->setCurrentIndex(6);

}

void MainWindow::on_modify_use_clicked()
{
    QString both=ui->id_sportif_usem->currentText();
    QString nom=(both.split(" ")).first();
    QString nom_equip=ui->id_equip_usem->currentText();
    int id_e = utmp.chercherIDE(nom_equip);
    int id_s = utmp.chercherIDS(nom);

    QString date = ui->date_usem->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString image=ui->image_usem->text();
    QString verif=ui->verif_usem->text();



    use u(id_e,id_s,date,image,verif);
    bool test=u.update();

    if (test){
        ui->tableView_use->setModel(utmp.afficher());
        button_use();
        QMessageBox::information(nullptr, QObject::tr("DONE"),
                    QObject::tr("Successfull modification\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->equipement_integ->setCurrentIndex(5);

    }else{
        QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                    QObject::tr("Error.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

void MainWindow::on_delete_use_clicked(int id)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete all equipment?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
    bool test=utmp.supprimer(id);

    if (test){
        ui->tableView_use->setModel(utmp.afficher());
        button_use();

        QMessageBox::information(nullptr, QObject::tr("DONE"),
                    QObject::tr("Deleted successfully.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }else
        QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                    QObject::tr("Error.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->equipement_integ->setCurrentIndex(5);}
}

void MainWindow::on_delete_all_use_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete all equipment?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        bool test = utmp.supprimer_all();

        if (test){
            ui->tableView_use->setModel(utmp.afficher());
            button_use();
            QMessageBox::information(nullptr, QObject::tr("DONE"),
                        QObject::tr("Everything has been deleted.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                        QObject::tr("Error.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
}



void MainWindow::on_back_add_use_clicked()
{
    ui->equipement_integ->setCurrentIndex(5);
}

void MainWindow::on_back_modify_use_clicked()
{
    ui->equipement_integ->setCurrentIndex(5);
}

void MainWindow::on_pushButton_clicked()
{
    ui->equipement_integ->setCurrentIndex(5);

}

void MainWindow::on_back_to_list_clicked()
{
    ui->equipement_integ->setCurrentIndex(1);

}





void MainWindow::on_image_ajouter_use_clicked()
{
    QString selectedImagePath = QFileDialog::getOpenFileName(this, tr("Select Image"), QDir::homePath(), tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (!selectedImagePath.isEmpty()) {
        ui->image_use->setText(selectedImagePath);
    } else {
        QMessageBox::critical(this, "Error", "No image selected!");
    }
}

void MainWindow::on_image_modifier_use_clicked()
{
    QString selectedImagePath = QFileDialog::getOpenFileName(this, tr("Select Image"), QDir::homePath(), tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (!selectedImagePath.isEmpty()) {
        ui->image_usem->setText(selectedImagePath);
    } else {
        QMessageBox::critical(this, "Error", "No image selected!");
    }
}

void MainWindow::update()
{
    data += A1.read_from_arduino(); // Append the newly received data to the existing data
    // Check if the data ends with a newline character
    if (data.endsWith("\r\n")) {
        // Remove the newline characters and update the label
        data.remove(data.length() - 2, 2);
        Stmp.sendCurrentPos(data);
        qDebug() << data;
        data.clear(); // Clear the data for the next reading
    }
}
//arduino_doua///////////////////
void MainWindow::output()
{
    data = A.read_from_arduino();
    VAR_o = QString::fromUtf8(data);
    qDebug() << VAR_o;
    bool test = A.check(VAR_o, &nom, &prenom);
    if (test) {
        QStringList dataToSend;

        dataToSend << "1" << nom << prenom;
        qDebug() << "Data to send:" << dataToSend;
        A.write_to_arduino(dataToSend);
    } else {
        A.write_to_arduino_old("0");
    }
}

void MainWindow::on_digital_clicked()
{
    int id = ui->del->text().toInt();

    bool test = A.check(VAR_o, &nom, &prenom);
    if (test==false){
        A.inserer(VAR_o, id);
        QMessageBox::critical(this, "Ok", "This fingerprint's been successfully added!");
    }else{
        QMessageBox::critical(this, "Error", "This fingerprint belongs to another user!");
    }
}



//doua//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


















//ahmed//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_event_clicked()
{
    ui->Modules->setCurrentIndex(2);
    ui->eventInteg->setCurrentIndex(0);
    ui->tableView_event->setModel(atmp.afficher());
    button_ahmed();
    ui->Module_image->setIcon(QIcon("C:/Users/kamou/Desktop/doua/ic_events.jpg"));
    ui->Module_image->setIconSize(QSize(110, 110)); // Set the size of the icon (optional)
}



void MainWindow::on_ajouter_event_clicked()
{
    ui->eventInteg->setCurrentIndex(1);
}

void MainWindow::on_back1_event_clicked()
{
    ui->eventInteg->setCurrentIndex(0);
}

void MainWindow::on_valider_event_clicked()
{
    QRegExp rx("^[a-zA-Z]+$");
    QDate currentDate = QDate::currentDate();

    ui->l_date_event->setDate(QDate::currentDate());

    int id=ui->l_id_event->text().toInt();
    int age=ui->l_age_event->text().toInt();
    int dure=ui->l_dure_event->text().toInt();
    int prix=ui->l_prix_event->text().toInt();
    QString nom=ui->l_nom_event->text();
    QString lieu=ui->l_lieu_event->text();
    QString type=ui->l_type_event->text();
    QDate date=ui->l_date_event->date();
    QString niveau=ui->niveau->currentText();

    Event even = atmp.getEventById(id);
    if (id < 0) {
        QMessageBox::critical(this, "Error", "The ID cannot be negative!");
        ui->l_id_event->clear();
    }else if (age <= 0) {
        QMessageBox::critical(this, "Error", "The age cannot be negative!");
        ui->l_age_event->clear();
    }else if (dure <= 0){
        QMessageBox::critical(this, "Error", "The time cannot be negative!");
        ui->l_dure_event->clear();
    }else if (prix <= 0){
        QMessageBox::critical(this, "Error", "The price must be greater than 0!");
        ui->l_prix_event->clear();
    }else if (nom.isEmpty() || !rx.exactMatch(nom)){
        QMessageBox::critical(this, "Error", "The name cannot be empty or contain numbers!");
        ui->l_nom_event->clear();
    }else if (lieu.isEmpty()){
        QMessageBox::critical(this, "Error", "The place cannot be empty!");
        ui->l_lieu_event->clear();
    }else if (type.isEmpty()|| !rx.exactMatch(type)){
        QMessageBox::critical(this, "Error", "The type cannot be empty or contain numbers!");
        ui->l_type_event->clear();

    }else if (date < currentDate){
        QMessageBox::critical(this, "Error", "The date cannot be in the past.");
        ui->l_date_event->setDate(QDate::currentDate());
    }
   else {
        Event E(id,nom,age,lieu,date,dure,type,niveau,prix);
        bool test=E.ajouter();
        if (test)
        {
            E.generatePoster(ui->l_id_event,ui->l_nom_event,date,ui->l_lieu_event,ui->l_type_event,ui->l_prix_event,ui->l_age_event);
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("ajout effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->l_id_event->clear();
            ui->l_age_event->clear();
            ui->l_nom_event->clear();
            ui->l_lieu_event->clear();
            ui->l_date_event->clear();
            ui->l_dure_event->clear();
            ui->l_type_event->clear();
            ui->l_prix_event->clear();
            ui->eventInteg->setCurrentIndex(0);
            ui->tableView_event->setModel(E.afficher());
            button_ahmed();
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("ajout non effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_delete_all_event_clicked()
{
    bool test=atmp.supprimer_all();

        if (test){
            ui->tableView_event->setModel(atmp.afficher());
            button_ahmed();
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("Eveything's been deleted.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("Error.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pdf_event_clicked()
{
    if (atmp.exportToPdf()==true) {
           QMessageBox::information(this, "Done", "PDF exported successfully!");
       } else {
           QMessageBox::critical(this, "Error", "Failed to export PDF!");
       }
}

void MainWindow::on_stat_event_clicked()
{
    ui->eventInteg->setCurrentIndex(3);
    Event myEvent;
       QSqlQueryModel *model = myEvent.getEventStatistics();
       qreal tot = 0;
       QMap<QString, qreal> typeCounts;
       QMapIterator<QString, qreal> it(typeCounts);

       if (model) {
           // Calculate totals and populate typeCounts
              for (int i = 0; i < model->rowCount(); ++i) {
                  QString gouvernorat = model->data(model->index(i, 0)).toString();
                  qreal count = model->data(model->index(i, 1)).toDouble();
                  typeCounts.insert(gouvernorat, count);
                  tot += count; // Accumulate total count
              }

              // Create series based on typeCounts
              QPieSeries *seriesC = new QPieSeries();
              QMapIterator<QString, qreal> it(typeCounts);
              while (it.hasNext()) {
                  it.next();
                  qreal percentage = (it.value() / tot) * 100;
                  QString label = it.key() + " (" + QString::number(percentage, 'f', 2) + "%)";
                  seriesC->append(label, it.value());

              }

           QChart *chartC = new QChart();
           chartC->addSeries(seriesC);
           chartC->setTitle("Statistique des Event");
           chartC->setTheme(QChart::ChartThemeLight);
           chartC->legend()->setVisible(true);
           chartC->legend()->setAlignment(Qt::AlignRight);

           QChartView *chartViewC = new QChartView(chartC);
           chartC->setBackgroundBrush(QBrush(QColor(87, 169, 209)));

           QGraphicsScene *scene = new QGraphicsScene();
           scene->addWidget(chartViewC);

           QColor colors(87, 169, 209);
           QBrush brush(colors);
           scene->setBackgroundBrush(brush);

           chartViewC->setFixedSize(700, 700);
           scene->setSceneRect(QRectF(chartViewC->rect()));

           QPixmap pixmap(scene->sceneRect().size().toSize());
           pixmap.fill(Qt::transparent);
           QPainter painter(&pixmap);
           chartViewC->render(&painter);


           ui->label_stat_event->setPixmap(pixmap);

           delete model;
       }
}

void MainWindow::on_back3_event_clicked()
{
    ui->eventInteg->setCurrentIndex(0);

}

void MainWindow::on_sort_event_currentTextChanged(const QString &arg1)
{
    if (arg1=="id"){
        ui->tableView_event->setModel(atmp.sort("id_event"));
        button_ahmed();
    }else if (arg1=="nom"){
        ui->tableView_event->setModel(atmp.sort("nom"));
        button_ahmed();
    }else if (arg1=="lieu"){
        ui->tableView_event->setModel(atmp.sort("lieu"));
        button_ahmed();
    }else if (arg1=="age"){
        ui->tableView_event->setModel(atmp.sort("age"));
        button_ahmed();
    }else if (arg1=="date"){
        ui->tableView_event->setModel(atmp.sort("date_event"));
        button_ahmed();
    }else if (arg1=="dure"){
        ui->tableView_event->setModel(atmp.sort("dure"));
        button_ahmed();
    }else if (arg1=="type"){
        ui->tableView_event->setModel(atmp.sort("type"));
        button_ahmed();
    }else if (arg1=="prix"){
        ui->tableView_event->setModel(atmp.sort("prix_inscrit"));
        button_ahmed();
    }
}

void MainWindow::on_search_event_textChanged(const QString &arg1)
{
    QSqlQueryModel *searchModel = atmp.search(arg1);

    if (searchModel!=nullptr) {
        ui->tableView_event->setModel(searchModel);
        button_ahmed();
    } else{
        QMessageBox::critical(this, "Error", "Search failed. No results found.");
    }
}

void MainWindow::on_back2_event_clicked()
{
    ui->eventInteg->setCurrentIndex(0);
    ui->tableView_event->setModel(atmp.afficher());
    button_ahmed();
}

void MainWindow::on_validerm_event_clicked()
{
    QDate currentDate = QDate::currentDate();
    int id=ui->l_idm_event->text().toInt();
    int age=ui->l_agem_event->text().toInt();
    int dure=ui->l_durem_event->text().toInt();
    int prix=ui->l_prixm_event->text().toInt();
    QString nom=ui->l_nomm_event->text();
    QString lieu=ui->l_lieum_event->text();
    QString type=ui->l_typem_event->text();
    QDate date=ui->l_datem_event->date();
    QString niveau=ui->niveaum->currentText();

    if (age <= 0) {
        QMessageBox::critical(this, "Error", "The age cannot be negative!");
    }else if (dure <= 0){
        QMessageBox::critical(this, "Error", "The time cannot be negative!");
    }else if (prix <= 0){
        QMessageBox::critical(this, "Error", "The price must be greater than 0!");
    }else if (nom.isEmpty()){
        QMessageBox::critical(this, "Error", "The name cannot be empty!");
    }else if (lieu.isEmpty()){
        QMessageBox::critical(this, "Error", "The place cannot be empty!");
    }else if (type.isEmpty()){
        QMessageBox::critical(this, "Error", "The type cannot be empty!");
    }else if (date < currentDate){
        QMessageBox::critical(this, "Error", "The date cannot be in the past.");
    }else {
        bool test=atmp.modifier(id,nom,age,lieu,date,dure,type,niveau,prix);
        if (test)
        {
            ui->tableView_event->setModel(atmp.afficher());
            button_ahmed();
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("modification effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("modification non effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        ui->eventInteg->setCurrentIndex(0);
    }
}
void MainWindow::button_ahmed()
{
    for (int row = 0; row < ui->tableView_event->model()->rowCount(); ++row) {
        QPushButton *update_button = new QPushButton("Update", this);
        update_button->setStyleSheet("QPushButton {"
                                     "background-color:#437FF7;border-radius :5px; "
                                     "color : #fff;"
                                     "}");
        QPushButton *delete_button = new QPushButton("Delete", this);
        delete_button->setStyleSheet("QPushButton {"
                                     "background-color:#ef1f22;border-radius :5px; "
                                     "color : #fff;"
                                     "}");
        connect(update_button, &QPushButton::clicked, [this, row]() {
            Event e;

            e.set_id(ui->tableView_event->model()->index(row, 0).data().toInt());
            e.set_nom(ui->tableView_event->model()->index(row, 1).data().toString());
            e.set_age(ui->tableView_event->model()->index(row, 2).data().toInt());
            e.set_lieu(ui->tableView_event->model()->index(row, 3).data().toString());

            QString dateString = ui->tableView_event->model()->index(row, 4).data().toString();
            QStringList parts = dateString.split("T"); // Split at "T" to separate date and time parts
            QString datePart = parts[0]; // Extract the date part
            QDate date = QDate::fromString(datePart, "yyyy-MM-dd");
            if (date.isValid()) {
                qDebug() << "Parsed date:" << date;
                e.set_date(date);
            } else {
                qDebug() << "Error: Invalid date format!";
                // You may need to handle this error case appropriately
            }

            e.set_dure(ui->tableView_event->model()->index(row, 5).data().toInt());
            e.set_type(ui->tableView_event->model()->index(row, 6).data().toString());
            e.set_prix(ui->tableView_event->model()->index(row, 7).data().toInt());
            e.set_niveau(ui->tableView_event->model()->index(row, 8).data().toString());

            on_modifier_event_clicked(e);
        });
        connect(delete_button, &QPushButton::clicked, [this, row]() {
            on_delete_event_clicked(ui->tableView_event->model()->index(row, 0).data().toInt());
        });
        ui->tableView_event->setIndexWidget(ui->tableView_event->model()->index(row, 9), update_button);
        ui->tableView_event->setIndexWidget(ui->tableView_event->model()->index(row, 10), delete_button);
    }
}

void MainWindow::on_modifier_event_clicked(Event e)
{
    if (e.get_id()==-1){
       QMessageBox::critical(this, "Error", "This ID doesn't exist!");
    }else{
    ui->eventInteg->setCurrentIndex(2);
    ui->l_idm_event->setText(QString::number(e.get_id()));
    ui->l_nomm_event->setText(e.get_nom());
    ui->l_agem_event->setText(QString::number(e.get_age()));
    ui->l_lieum_event->setText(e.get_lieu());
    ui->l_durem_event->setText(QString::number(e.get_dure()));
    ui->l_typem_event->setText(e.get_type());
    ui->l_prixm_event->setText(QString::number(e.get_prix()));
    QDate date = e.get_date(); // Assuming e.get_date() returns a QDate object

    QString dateString = date.toString("yyyy-MM-dd");

    ui->l_datem_event->setDate(QDate::fromString(dateString, "yyyy-MM-dd"));
    ui->niveaum->setCurrentText(e.get_niveau());


    }
}

void MainWindow::on_delete_event_clicked(int id)
{
    Event e=atmp.getEventById(id);
    if (e.get_id()==-1){
       QMessageBox::critical(this, "Error", "This ID doesn't exist!");
    }else{
    bool test=atmp.supprimer(id);

    if (test){
        ui->tableView_event->setModel(atmp.afficher());
        button_ahmed();

        QMessageBox::information(nullptr, QObject::tr("DONE"),
                    QObject::tr("An event's been deleted.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }else
        QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                    QObject::tr("Error.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->eventInteg->setCurrentIndex(0);}
}

void MainWindow::on_Module_image_clicked()
{
    ui->eventInteg->setCurrentIndex(4);
    atmp.highlightEventDates(ui->calendarWidget);

}

void MainWindow::on_back3_event_2_clicked()
{
    ui->eventInteg->setCurrentIndex(0);
}
void MainWindow::on_calendarWidget_selectionChanged()
{
    ui->lineEdit_calendar_affichage->setText(ui->calendarWidget->selectedDate().toString());
    ui->tableView_calendar->setModel(atmp.afficher_calendar(ui->calendarWidget->selectedDate()));
}
void MainWindow::on_map_event_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableView_event->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_event->model());

    if (model) {
        QSet<int> selectedRows;

        foreach(const QModelIndex &selectedIndex, selectedIndexes) {
            int row = selectedIndex.row();
            if (!selectedRows.contains(row)) {
                // Access data from the fifth column of the selected row
                QModelIndex fifthColumnIndex = model->index(row, 3);
                QVariant cellData = model->data(fifthColumnIndex);

                // Split the data by comma and trim any whitespace
                QStringList parties = cellData.toString().split(",", QString::SkipEmptyParts);
                if (parties.size() >= 2) {
                    ui->quickWidget_Map_View->setSource(QUrl(QStringLiteral("qrc:/img/QmlMap.qml")));
                    ui->quickWidget_Map_View->show();

                    auto obje = ui->quickWidget_Map_View->rootObject();
                    connect(this, SIGNAL(setCenterPosition(QVariant, QVariant)), obje, SLOT(setCenterPosition(QVariant, QVariant)));
                    connect(this, SIGNAL(setLocationMarking(QVariant, QVariant)), obje, SLOT(setLocationMarking(QVariant, QVariant)));

                    QString premierePartie = parties[0].trimmed();
                    QString deuxiemePartie = parties[1].trimmed();
                    qDebug() << "Première partie:" << premierePartie.toDouble();
                    qDebug() << "Deuxième partie:" << deuxiemePartie.toDouble();
                    emit setCenterPosition(premierePartie.toDouble(), deuxiemePartie.toDouble());
                    emit setLocationMarking(premierePartie.toDouble(), deuxiemePartie.toDouble());
                } else {
                    qDebug() << "La chaîne ne contient pas suffisamment de parties séparées par des virgules.";
                }
                selectedRows.insert(row);
            }
        }
    }

    ui->eventInteg->setCurrentIndex(5);
}
void MainWindow::on_back3_event_4_clicked()
{
    ui->eventInteg->setCurrentIndex(0);

}

#include <QDir>

void MainWindow::on_tableView_event_doubleClicked(const QModelIndex &index)
{
    // Define the index of the column containing the event title
        int titleColumnIndex = 1; // Replace <index_of_title_column> with the actual index

        // Get the model associated with the table view
        QAbstractItemModel *model = ui->tableView->model();

        // Retrieve the title from the selected row
        QModelIndex titleIndex = model->index(index.row(), titleColumnIndex);
        QString title = model->data(titleIndex).toString();

        // Retrieve other UI elements
        QLineEdit *IDEdit = ui->l_id_event; // Replace with the actual pointer to your QLineEdit
        QLineEdit *titleEdit = ui->l_nom_event;
        QDateEdit *dateEdit = ui->l_date_event;
        QLineEdit *locationEdit = ui->l_lieu_event;
        QLineEdit *typeEdit = ui->l_type_event;
        QLineEdit *prixEdit = ui->l_prix_event;
        QLineEdit *ageEdit = ui->l_age_event;

    // Construct the file path for the poster image
    QString filePath = "C:/Users/LENOVO/Pictures/Desktop/finalprojet/2a19-smart-nautical-sports-club/users/events/" + title + ".png";

    // Check if the poster image exists
    QFile file(filePath);
    if (!file.exists()) {
        // If the poster image doesn't exist, generate it
        Event event;
        //ui->l_id_event,ui->l_nom_event,date,ui->l_lieu_event,ui->l_type_event,ui->l_prix_event,ui->l_age_event
        // Check if the poster generation was successful
        if (!file.exists()) {
            QMessageBox::warning(this, "Error", "Failed to generate the poster image.");
            return;
        }
    }

    // Load the poster image
    QImage posterImage(filePath);

    // Display the poster image in a dialog or separate window
    QDialog dialog(this);
    QLabel label(&dialog);
    label.setPixmap(QPixmap::fromImage(posterImage));
    dialog.exec();
}


QString MainWindow::findImagePathByTitle(const QString& title) {
    // Specify the directory containing the images
    QString directoryPath = "C:/Users/LENOVO/Pictures/Desktop/finalprojet/2a19-smart-nautical-sports-club/users/events/";

    // Create a QDir object to search for files in the directory
    QDir directory(directoryPath);

    // Filter the files to only include image files
    QStringList filters;
    filters << "*.png" ; // Add more image extensions if necessary
    directory.setNameFilters(filters);

    // Search for files matching the event title
    QStringList fileList = directory.entryList(QDir::Files);
    for (const QString& fileName : fileList) {
        if (fileName.contains(title, Qt::CaseInsensitive)) {
            return directory.filePath(fileName);
        }
    }

    return QString(); // Return an empty string if no matching image file is found
}


void MainWindow::displayPoster(const QImage& posterImage) {
    // Clear the central widget
    if (centralWidget()) {
        QWidget* oldCentralWidget = centralWidget();
        setCentralWidget(nullptr);
        delete oldCentralWidget;
    }

    // Create a QLabel to display the poster image
    QLabel *posterLabel = new QLabel(this);
    posterLabel->setPixmap(QPixmap::fromImage(posterImage));

    // Optionally, set the size policy and alignment of the QLabel
    posterLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    posterLabel->setAlignment(Qt::AlignCenter);

    // Create a layout to hold the poster label
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(posterLabel);

    // Create a widget to hold the layout and set it as the central widget of the main window
    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);

    // Show the main window
    show();
}

//ala///////////////////////
void MainWindow::button_ala()
{
    for (int row = 0; row < ui->tableView_Sport->model()->rowCount(); ++row) {
        QPushButton *update_button = new QPushButton("Update", this);
        update_button->setStyleSheet("QPushButton {"
                                     "background-color:#437FF7;border-radius :5px; "
                                     "color : #fff;"
                                     "}");
        QPushButton *delete_button = new QPushButton("Delete", this);
        delete_button->setStyleSheet("QPushButton {"
                                     "background-color:#ef1f22;border-radius :5px; "
                                     "color : #fff;"
                                     "}");
        connect(update_button, &QPushButton::clicked, [this, row]() {
            csports e;

            e.set_id(ui->tableView_Sport->model()->index(row, 0).data().toInt());
            e.set_nom(ui->tableView_Sport->model()->index(row, 1).data().toString());
            e.set_description(ui->tableView_Sport->model()->index(row, 2).data().toString());

            e.set_age_min(ui->tableView_Sport->model()->index(row, 3).data().toInt());
            e.set_nb_sportif(ui->tableView_Sport->model()->index(row, 4).data().toInt());



            e.set_frequence(ui->tableView_Sport->model()->index(row, 5).data().toString());

            on_modifier_Sport_clicked(e);
        });
        connect(delete_button, &QPushButton::clicked, [this, row]() {
            on_delete_Sport_clicked(ui->tableView_Sport->model()->index(row, 0).data().toInt());
        });
        ui->tableView_Sport->setIndexWidget(ui->tableView_Sport->model()->index(row, 6), update_button);
        ui->tableView_Sport->setIndexWidget(ui->tableView_Sport->model()->index(row, 7), delete_button);
    }
}
void MainWindow::on_modifier_Sport_clicked(csports e)
{
    if (e.get_Id_sport()==-1){
       QMessageBox::critical(this, "Error", "This ID doesn't exist!");
    }else{
    ui->sportInteg->setCurrentIndex(2);
    ui->l_idm_Sport->setText(QString::number(e.get_Id_sport()));
    ui->l_nomm_Sport->setText(e.get_nom());
    ui->l_descriptionm_Sport->setText(e.get_description());
    ui->l_nbsportifm_Sport->setText(QString::number(e.get_nb_sportif()));
    ui->l_age_minm_Sport->setText(QString::number(e.get_age_min()));
    ui->l_frequencem_Sport->setText(e.get_frequence());
    }
}

void MainWindow::on_delete_Sport_clicked(int id)
{
    csports e=cstmp.getsportsById(id);
    if (e.get_Id_sport()==-1){
       QMessageBox::critical(this, "Error", "This ID doesn't exist!");
    }else{
    bool test=cstmp.supprimer(id);

    if (test){
        ui->tableView_Sport->setModel(cstmp.afficher());
        button_ala();

        QMessageBox::information(nullptr, QObject::tr("DONE"),
                    QObject::tr("A sport has been deleted.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }else
        QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                    QObject::tr("Error.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->sportInteg->setCurrentIndex(0);}
}

void MainWindow::on_pdf_Sport_clicked()
{
    if (cstmp.exportToPdf()==true) {
        QMessageBox::information(this, "Done", "PDF exported successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to export PDF!");
    }
}

void MainWindow::on_delete_all_Sport_clicked()
{
    bool test=cstmp.supprimer_all();

    if (test){
        ui->tableView_Sport->setModel(cstmp.afficher());
        button_ala();
        QMessageBox::information(nullptr, QObject::tr("DONE"),
                    QObject::tr("Eveything's been deleted.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }else
        QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                    QObject::tr("Error.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_sort_Sport_currentTextChanged(const QString &arg1)
{
    if (arg1=="id"){
        ui->tableView_Sport->setModel(cstmp.sort("id_sport"));
        button_ala();
    }else if (arg1=="nom"){
        ui->tableView_Sport->setModel(cstmp.sort("nom"));
        button_ala();
    }else if (arg1=="description"){
        ui->tableView_Sport->setModel(cstmp.sort("description"));
        button_ala();
    }else if (arg1=="frequence"){
        ui->tableView_Sport->setModel(cstmp.sort("frequence"));
        button_ala();
    }else if (arg1=="age"){
        ui->tableView_Sport->setModel(cstmp.sort("age_min"));
        button_ala();
    }else if (arg1=="nb_sportif"){
        ui->tableView_Sport->setModel(cstmp.sort("nb_sportif"));
        button_ala();
    }
}

void MainWindow::on_search_Sport_textChanged(const QString &arg1)
{
    QSqlQueryModel *searchModel = cstmp.search(arg1);

       if (searchModel!=nullptr) {
           ui->tableView_Sport->setModel(searchModel);
           button_ala();

       } else{
           QMessageBox::critical(this, "Error", "Search failed. No results found.");
       }
}

void MainWindow::on_ajouter_Sport_clicked()
{
    ui->sportInteg->setCurrentIndex(1);
}

void MainWindow::on_back1_Sport_clicked()
{
    ui->sportInteg->setCurrentIndex(0);

}

void MainWindow::on_valider_Sport_clicked()
{
    int Id_sport = ui->l_id_Sport->text().toInt();
    QString nom = ui->l_nom_Sport->text();
    QString description = ui->l_description_Sport->text();
    int age_min = ui->l_age_min_Sport->text().toInt();
    int nb_sportif = ui->l_nbsportif_Sport->text().toInt();
    QString frequence = ui->l_frequence_Sport->text();
    QRegExp rx("^[a-zA-Z]+$");
    QRegExp dx("\\d*");

    if (ui->l_id_Sport->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "The ID cannot be empty!");
        }
    else if (ui->l_age_min_Sport->text().isEmpty()){
        QMessageBox::critical(this, "Error", "The age cannot be empty!");
        }
    else if (ui->l_nbsportif_Sport->text().isEmpty()){
        QMessageBox::critical(this, "Error", "The number of sportifs  cannot be empty!");
        }
     else {
        // Check if the ID already exists
        csports s = cstmp.getsportsById(Id_sport);
        if ((s.get_Id_sport() == Id_sport) && (Id_sport !=0)) {
            QMessageBox::critical(this, "Error", "This ID already exists!");
                } else if (Id_sport < 0) {
            QMessageBox::critical(this, "Error", "The ID cannot be negative!");
               } else if (nom.isEmpty()) {
            QMessageBox::critical(this, "Error", "The name cannot be empty!");
        } else if (!rx.exactMatch(nom)) {
            QMessageBox::critical(this, "Error", "The name must contain only characters.");
             } else if (age_min < 0) {
            QMessageBox::critical(this, "Error", "The age must be greater than 0.");
                   }
        else if (!dx.exactMatch(QString ::number(age_min))){
            QMessageBox::critical(this, "Error", "The age must not contain characters .");
            ui->l_id_Sport->clear();
            ui->l_nom_Sport->clear();
            ui->l_description_Sport->clear();
            ui->l_age_min_Sport->clear();
            ui->l_nbsportif_Sport->clear();
            ui->l_frequence_Sport->clear();
        }
        else if (nb_sportif < 0) {
            QMessageBox::critical(this, "Error", "The number of sportifs must be greater than 0.");
              }
        else if (frequence.isEmpty()){
            QMessageBox::critical(this, "Error", "The frequence cannot be empty!");
                } else if (description.isEmpty()){
            QMessageBox::critical(this, "Error", "The description cannot be empty!");
             } else {
            // Add the new entry
            csports E(Id_sport, nom, description, age_min, nb_sportif, frequence);
            bool test = E.ajouter();
            if (test) {
                // Refresh the table view to display the updated data
                ui->tableView_Sport->setModel(cstmp.afficher());
                button_ala();
                QMessageBox::information(nullptr, QObject::tr("Success"),
                                         QObject::tr("Addition successful."),
                                         QMessageBox::Cancel);
                // Clear the input fields after successful addition
                ui->l_id_Sport->clear();
                ui->l_nom_Sport->clear();
                ui->l_description_Sport->clear();
                ui->l_frequence_Sport->clear();
                ui->l_age_min_Sport->clear();
                ui->l_nbsportif_Sport->clear();
            } else {
                QMessageBox::critical(nullptr, QObject::tr("Error"),
                                      QObject::tr("Addition unsuccessful."),
                                      QMessageBox::Cancel);
            }
             ui->sportInteg->setCurrentIndex(0);
        }

    }
}

void MainWindow::on_back2_Sport_clicked()
{
    ui->sportInteg->setCurrentIndex(0);
}

void MainWindow::on_validerm_Sport_clicked()
{
    QRegExp rx("^[a-zA-Z]+$");
    ui->l_idm_Sport->setReadOnly(true);
    int id=ui->l_idm_Sport->text().toInt();
    QString nom=ui->l_nomm_Sport->text();
    QString description=ui->l_descriptionm_Sport->text();
    int age_min=ui->l_age_minm_Sport->text().toInt();
    int nb_sportif=ui->l_nbsportifm_Sport->text().toInt();
    QString frequence=ui->l_frequencem_Sport->text();
    csports s=cstmp.getsportsById(id);
    if (nom.isEmpty()){
        QMessageBox::critical(this, "Error", "The name cannot be empty!");
    }
    else if (!rx.exactMatch(nom)) {
            QMessageBox::critical(this,"Error","the name must contain only caracters.");}
    else if (age_min<=0){
        QMessageBox::critical(this, "Error", "The age must be greater than 0!");
    }
    else if (nb_sportif<=0){
        QMessageBox::critical(this, "Error", "The number of sportifs must be greater than 0!");

    }
    else if (description.isEmpty()){
        QMessageBox::critical(this, "Error", "The description cannot be empty!");
    }
    else if (frequence.isEmpty()){
        QMessageBox::critical(this, "Error", "The frequence cannot be empty!");

    }
    else if (ui->l_age_minm_Sport->text().isEmpty()){
        QMessageBox::critical(this, "Error", "The age cannot be empty!");}
    else if (ui->l_nbsportifm_Sport->text().isEmpty()){
        QMessageBox::critical(this, "Error", "The age cannot be empty!");}
    else{
    bool test=cstmp.modifier(id,nom,description,age_min,nb_sportif,frequence);
    if (test)
    {
        ui->tableView_Sport->setModel(cstmp.afficher());
        button_ala();
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("modification effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("modification non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->sportInteg->setCurrentIndex(0);}

}

void MainWindow::on_pushButton_7_clicked()
{
    ui->Modules->setCurrentIndex(3);
    ui->sportInteg->setCurrentIndex(0);
    ui->tableView_Sport->setModel(cstmp.afficher());
    button_ala();
    ui->Module_image->setIcon(QIcon("C:/Users/kamou/Desktop/doua/ic_sports.jpg"));
    ui->Module_image->setIconSize(QSize(110, 110)); // Set the size of the icon (optional)

}



void MainWindow::on_stat_Sport_2_clicked()
{
    ui->sportInteg->setCurrentIndex(3);
    csports mysport;
       QSqlQueryModel *model = mysport.getSportStatistics();
       qreal tot = 0;
       QMap<QString, qreal> typeCounts;
       QMapIterator<QString, qreal> it(typeCounts);

       if (model) {
           // Calculate totals and populate typeCounts
              for (int i = 0; i < model->rowCount(); ++i) {
                  QString gouvernorat = model->data(model->index(i, 0)).toString();
                  qreal count = model->data(model->index(i, 1)).toDouble();
                  typeCounts.insert(gouvernorat, count);
                  tot += count; // Accumulate total count
              }

              // Create series based on typeCounts
              QPieSeries *seriesC = new QPieSeries();
              QMapIterator<QString, qreal> it(typeCounts);
              while (it.hasNext()) {
                  it.next();
                  qreal percentage = (it.value() / tot) * 100;
                  QString label = it.key() + " (" + QString::number(percentage, 'f', 2) + "%)";
                  seriesC->append(label, it.value());

              }

           QChart *chartC = new QChart();
           chartC->addSeries(seriesC);
           chartC->setTitle("Statistique des sports");
           chartC->setTheme(QChart::ChartThemeLight);
           chartC->legend()->setVisible(true);
           chartC->legend()->setAlignment(Qt::AlignRight);

           QChartView *chartViewC = new QChartView(chartC);
           chartC->setBackgroundBrush(QBrush(QColor(87, 169, 209)));

           QGraphicsScene *scene = new QGraphicsScene();
           scene->addWidget(chartViewC);

           QColor colors(87, 169, 209);
           QBrush brush(colors);
           scene->setBackgroundBrush(brush);

           chartViewC->setFixedSize(700, 700);
           scene->setSceneRect(QRectF(chartViewC->rect()));

           QPixmap pixmap(scene->sceneRect().size().toSize());
           pixmap.fill(Qt::transparent);
           QPainter painter(&pixmap);
           chartViewC->render(&painter);


           ui->label_stat_Sport->setPixmap(pixmap);

           delete model;
       }
}

void MainWindow::on_back3_Sport_clicked()
{
    ui->sportInteg->setCurrentIndex(0);

}

void MainWindow::on_add1_5_clicked()
{
    user user;
        QMap<QString, double> stats = user.getStatsByPositionPercentage();

        // Create data series for the chart
        QPieSeries *series = new QPieSeries();
        for (auto it = stats.begin(); it != stats.end(); ++it) {
            QString label = QString("%1 (%2%)").arg(it.key()).arg(it.value(), 0, 'f', 1);
            series->append(label, it.value());
        }

        // Create and display the chart
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("User Position Statistics");
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(400, 300);
        chartView->show();
}

void MainWindow::on_add1_6_clicked()
{
    QSqlQueryModel* sortedUsers = user_all.TrieParPrenom();
   ui->table->setModel(sortedUsers);
}

void MainWindow::on_pushButton_15_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", QDir::homePath(), "PDF Files (*.pdf)");

   if (!filePath.isEmpty()) {
       if (user_all.exportToPdf(filePath)) {
           QMessageBox::information(this, "Success", "PDF exported successfully!");
       } else {
           QMessageBox::critical(this, "Error", "Failed to export PDF.");
       }
   }
}


void MainWindow::on_scan_Sporrt_clicked()
{
    QProcess *process = new QProcess(this);
     QString program = "python";
     QStringList arguments;
     arguments << "C:\\Users\\kamou\\Desktop\\ala\\ala.py";
     process->start(program, arguments);
}

void MainWindow::on_employees_clicked()
{
    ui->Modules->setCurrentIndex(1);
    ui->Module_image->setIcon(QIcon("C:/Users/kamou/Desktop/doua/ic_staff.jpg"));
    ui->Module_image->setIconSize(QSize(110, 110)); // Set the size of the icon (optional)
}

bool isUpdateInProgress = false;

void MainWindow::on_sp_clicked()
{
    // Vérifiez si une mise à jour est déjà en cours
    if (isUpdateInProgress) {
        qDebug() << "Une mise à jour est déjà en cours...";
        return;
    }

    // Marquez que la mise à jour est en cours
    isUpdateInProgress = true;

    // Appel à la fonction qui récupère les données météorologiques
    QString appId = "3c60660061ffbffe095cf5d55a7accdd"; // Remplacez par votre ID d'application OpenWeatherMap
    QString location = "Tunis"; // Remplacez par l'emplacement désiré
    quint8 maxForecasts = 1; // Maximum de prévisions à récupérer, par exemple 1 pour la prochaine prévision

    // Initialisation de l'objet OpenWeatherMapForecast
    o = new OpenWeatherMapForecast();

    // Connexion du signal forecastsUpdated à la fonction handleWeatherData
    connect(o, &OpenWeatherMapForecast::forecastsUpdated, this, &MainWindow::handleWeatherData);

    // Récupération des données météorologiques
    o->updateForecasts(appId, location, maxForecasts);
    ui->te->setText("Piscine"); // Assurez-vous de remplacer "textEdit" par le nom de votre widget QTextEdit
}
void MainWindow::handleWeatherData(QJsonArray data) {
    // Parcourir les données météorologiques pour extraire les informations pertinentes
    QString sportsText;
    for (const QJsonValue& forecastValue : data) {
        QJsonObject forecastObject = forecastValue.toObject();

        // Extraire les informations météorologiques telles que la température et la vitesse du vent
        double temperature = forecastObject["main"].toObject()["temp"].toDouble();
        //double windSpeed = forecastObject["wind"].toObject()["speed"].toDouble();

        // Déterminer les sports favorisés en fonction des conditions météorologiques
        QStringList favoredSports;
        if (temperature >= 25) {
            favoredSports<< "Sea";
        } else if (temperature >= 15 ) {
            favoredSports << "Piscine";
        } else if (temperature >= 10) {
            favoredSports << "BeachBall";
        } else {
            favoredSports << "Indoor Sports";
        }

        // Ajouter les sports favorisés au texte
        sportsText += favoredSports.join(", ") + "\n\n";
    }

    // Mettre à jour l'affichage dans le QTextEdit
    ui->te->setText(sportsText); // Assurez-vous de remplacer "textEdit" par le nom de votre widget QTextEdit
    isUpdateInProgress = false;
}

void MainWindow::on_add_deleteAll_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete all sports?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        bool test = cstmp.supprimer_all();
        reloadMainWindow(dummyPair);

        if (test){
            QMessageBox::information(nullptr, QObject::tr("DONE"),
                        QObject::tr("Everything has been deleted.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("FAIL"),
                        QObject::tr("Error.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
    ui->tableView_Sport->setModel(cstmp.afficher());
}
