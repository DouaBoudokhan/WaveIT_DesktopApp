#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QPixmap>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>



/*#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d/xfeatures2d.hpp>*/




class equipement
{
public:

    //constructeurs
    equipement(){};
    equipement(int,QString,QString,int,QString,int,QString,int,QString);


    //setters
    void setid(int n);
    void setnom(QString n);
    void setimagepath(QString n);
    void setquantite(int n);
    void setetat(QString n);
    void setnb(int n);
    void settype(QString n);
    void setprix(int n);
    void setdate(QString n);

    //getters
    int get_id();
    QString get_nom();
    QString get_imagepath();
    int get_quantite();
    QString get_etat();
    int get_nb();
    QString get_type();
    int get_prix();
    QString get_date();

    //CRUD
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int idd);
    bool supprimer_all();
    bool update();
    equipement getEquipementById(int id);

    //metiers
    QSqlQueryModel *search(const QString &criteria);
    QSqlQueryModel *sort(const QString &criteria);
    bool exportToPdf();
    void stat();

    //metiers avances
    void sendSMS(const QString& accountSid, const QString& authToken, const QString& from, const QString& to, const QString& message);
    bool compareImages();
    bool compareImages(const QString& imagePath1, const QString& imagePath2);
    void metiers();
    //void extractColorFeatures(const cv::Mat& image, cv::Mat& features);
    //double compareColorFeatures(const cv::Mat& features1, const cv::Mat& features2);
    void check();
    QString generateChatbotReply(const QString& message);
    void update_nb(int id);




private:
    QString nom, etat, type, date, imagepath;
    int nb, id, quantite, prix;

    //comparaison images
    int histSize = 256;
    float histRange[2] = { 0, 256 };
    const bool uniform = true;
    const bool accumulate = false;
    QVector<QString> hist;


};

#endif // EQUIPEMENT_H


