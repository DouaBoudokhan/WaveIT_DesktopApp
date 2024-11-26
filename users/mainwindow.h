#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "user.h"
#include <QMainWindow>
#include<QComboBox>
#include "arduino.h"

//mohha
#include "sportif.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtCharts>
//

//doua/////////
#include "equipement.h"
#include "use.h"



//ahmed///////
#include "event.h"

//ala/////////
#include "csports.h"
#include "openweathermapforecast.h"
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QDragEnterEvent>
#include <QDropEvent>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <QCamera>
#include <QCameraImageCapture>
#include <QTimer>

#include <QVBoxLayout>
#include <QTextEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString& username,const QString& userpos, QWidget *parent = nullptr);
    ~MainWindow();
 static user connected;
 void updateStatisticsUI(int totalAdmins, int totalEventManagers, int totalAgents);
 void  handleWeatherData(QJsonArray data);

 //mohha
public slots:
void reloadMainWindow(QPair < int , QString> filter);
//

private:
    Ui::MainWindow *ui;
    user user_all;
    Sportif Stmp;
    equipement Etmp;
    use utmp;
    Event atmp;
    csports cstmp,cs;
    OpenWeatherMapForecast *o;
    QString m_username;
    QString m_userpos;

    //arduino doua
    QByteArray data;
    Arduino A,A1;
    QString VAR_o;
    QString nom;
    QString prenom;


private slots:
    //mohha
        void refreshActiveAthletesDataPeriodically();
        void getDistanceApi(QString init_pos , QString curr_pos);
        void on_addBTN_clicked();
        void on_add_addBTN_clicked();
        void on_update_updateBTN_clicked();
        void onUpdateButtonClicked(Sportif sp );
        void onDeleteButtonClicked(int id );
        void on_sportifs_back_clicked();
        void on_sportifs_back2_clicked();
        void on_add_deleteAll_clicked();
        void on_sorting_box_currentTextChanged(const QString &arg1);
        void on_search_btn_clicked();
        void on_searchBox_textChanged(const QString &arg1);
        void on_pdf_sportifs_clicked();
        void on_commandLinkButton_clicked();

        void on_add_sportif_upload_image_clicked();

        void on_reload_data_clicked();

        void on_active_sportifs_clicked();

//


//doua/////////////////////////////////
       //crud
       void on_valider_equip_clicked();
       void on_quitter_equip_clicked();
       void on_modifier_equip_clicked(equipement e);
       void on_delete_equip_clicked(int id);
       void on_delete_all_equip_clicked();
       void on_modify_equip_clicked();
       void on_ajouter_equip_clicked();
       void button();
       void on_image_ajouter_equi_clicked();
       void on_image_modifier_equi_clicked();
       void on_back3_equip_clicked();
       void on_back1_equip_clicked();

       //metiers
       void on_sort_button_equip_clicked();
       void on_pdf_equip_clicked();
       void on_sort_equip_currentTextChanged(const QString &arg1);
       void on_search_equip_textChanged(const QString &arg1);
       void on_stat_equip_clicked();

       //metiers avances
       void on_send_clicked();
       void on_chatbot_clicked();
       void on_back_chatbot_clicked();

       //menu
       void on_equipement_clicked();

       //use
       void on_valider_use_clicked();
       void on_add_use_clicked();
       void button_use();
       void on_delete_all_use_clicked();
       void on_delete_use_clicked(int id);
       void on_modify_use_clicked();
       void on_modifier_use_clicked(use u);
       void on_back_add_use_clicked();
       void on_back_modify_use_clicked();
       void on_pushButton_clicked();
       void on_back_to_list_clicked();
       void on_image_ajouter_use_clicked();
       void on_image_modifier_use_clicked();

       //arduino
       void output();


//fin/////////////////////////////////////////////////


    /*void on_modify_clicked();
    void on_next_clicked();
    //void on_add_clicked();
    //void on_display_clicked();
    //void on_pushButton_clicked();
    //void on_add1_clicked();
    //void on_pushButton_2_clicked();


    void on_pushButton_3_clicked();
    void on_add1_2_clicked();
    void on_add_2_clicked();
    void on_back_clicked();
    void on_back_2_clicked();
    void on_persp_clicked();
    void on_acc_clicked();
    void on_pushButton_4_clicked();*/
    //void on_pushButton_6_clicked();
    //void on_pushButton_8_clicked();
    //ahmed//////////////////
    void on_event_clicked();
    void on_ajouter_event_clicked();
    void on_back1_event_clicked();
    void on_valider_event_clicked();
    void on_delete_all_event_clicked();
    void on_pdf_event_clicked();
    void on_stat_event_clicked();
    void on_back3_event_clicked();
    void on_sort_event_currentTextChanged(const QString &arg1);
    void on_search_event_textChanged(const QString &arg1);
    void on_back2_event_clicked();
    void on_validerm_event_clicked();
    void button_ahmed();
    void on_modifier_event_clicked(Event e);
    void on_delete_event_clicked(int id);
    void on_back3_event_2_clicked();
    void on_map_event_clicked();
    void on_calendarWidget_selectionChanged();
    void on_back3_event_4_clicked();
    void on_Module_image_clicked();
    QString findImagePathByTitle(const QString& title);
    void displayPoster(const QImage& posterImage);
    void on_tableView_event_doubleClicked(const QModelIndex &index);
    void update();
    //ala///////////////////////
    void button_ala();
    void on_modifier_Sport_clicked(csports e);
    void on_delete_Sport_clicked(int id);
    void on_pdf_Sport_clicked();
    void on_delete_all_Sport_clicked();
    void on_sort_Sport_currentTextChanged(const QString &arg1);
    void on_search_Sport_textChanged(const QString &arg1);
    void on_ajouter_Sport_clicked();
    void on_back1_Sport_clicked();
    void on_valider_Sport_clicked();
    void on_back2_Sport_clicked();
    void on_validerm_Sport_clicked();
    void on_pushButton_7_clicked();
    void on_back3_Sport_clicked();


    //void on_add_photo_athlete_clicked();








    void on_add1_2_clicked();

    void on_add1_5_clicked();

    void on_next_clicked();

    void on_pushButton_3_clicked();

    void on_add_2_clicked();

    void on_modify_clicked();

    void on_back_2_clicked();

    void on_back_clicked();

    void on_persp_clicked();

    void on_acc_clicked();

    void on_pushButton_4_clicked();




    void on_add1_6_clicked();

    void on_pushButton_15_clicked();

    void on_scan_Sporrt_clicked();

    void on_back_3_clicked();

    void on_digital_clicked();

    //void on_pushButton_2_clicked();

    void on_athletes_clicked();

    void on_employees_clicked();

    void on_stat_Sport_2_clicked();

    void on_sp_clicked();

    void on_add_deleteAll_2_clicked();

signals:
    void setLocationMarking(QVariant,QVariant);
    void setCenterPosition(QVariant,QVariant);
};
#endif // MAINWINDOW_H
