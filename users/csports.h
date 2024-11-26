#ifndef CSPORTS_H
#define CSPORTS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMap>
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


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QObject>


class csports
{
private:
    QString nom,description,frequence;
    int Id_sport,nb_sportif,age_min;
public:
    csports();
    csports(int,QString,QString,int,int,QString);
    //getters
    QString get_nom(){ return nom; }
    QString get_description(){ return description; }
    QString get_frequence(){ return frequence; }
    int get_Id_sport(){ return Id_sport; }
    int get_nb_sportif(){ return nb_sportif; }
    int get_age_min(){ return age_min; }
    //setters
    void set_nom(QString n){nom=n;}
    void set_description(QString d){description=d;}
    void set_frequence(QString f){frequence=f;}
    void set_id(int id){this->Id_sport=id;}
    void set_nb_sportif(int nb){this->nb_sportif=nb;}
    void set_age_min(int age){this->age_min=age;}
    /////////////// crud/////////////////////////////////////// (all done)
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int ,QString ,QString,int,int,QString);
    csports getsportsById(int id);
    bool checkIfIdExists(int id);
    bool supprimer_all();
    //////////////////////////////////////////////metier////////////////////////////////////
    QSqlQueryModel *search(const QString &criteria);////done//
    QSqlQueryModel *sort(const QString &criteria);////done////
    bool exportToPdf();///// done///////
    int getTotalSports();////done not totally///////////////////
    QSqlQueryModel * trierafficher();
    QMap<QString, double> getSportsStatistics();
    /////////////////////////////////////////////////////////////////////////////
    QString performFaceAnalysis(const QImage &image);
    void getWeatherData();
    public slots:
    void onNetworkReplyFinished(QNetworkReply *reply);
    QSqlQueryModel* getSportStatistics();



};

#endif // CSPORTS_H
