#ifndef SPORTIF_H
#define SPORTIF_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QSortFilterProxyModel>
#include <QSqlTableModel>

class Sportif
{

private :

    QString num_tel;
    int id, age, frequency;
    QString   nom ,prenom  , adresse , mail , type_sport, niveau  ;
    QVariant image;


public:
    Sportif();
    Sportif(int id ,QString nom ,QString prenom ,int age  ,QString adresse,QString mail,QString num_tel,QString niveau,QString type_sport, QVariant image);
     Sportif(int id ,QString nom ,QString prenom ,int age  ,QString adresse,QString mail,QString num_tel,QString niveau,QString type_sport);
    void setId(int n);
    void setNom(QString n);
    void setPrenom(QString n);
    void setAge(int n);
    void setAdresse(QString n);
    void setNumTel(QString n);
    void setMail(QString n);
    void setTypeSport(QString n);
    void setNiveau(QString n);
    void setFrequency(int n);

    int getId();
    QString getNom();
    QString getPrenom();
    int getAge();
    QString getAdresse();
    QString getNumTel();
    QString getMail();
    QString getTypeSport();
    QString getNiveau();
    int getFrequency();

    bool ajouter();
    QSqlQueryModel * afficher(const QPair <int , QString> &param);
    bool supprimer(int id);
    bool modifier(Sportif sp);
    bool supprimerTous();
   QSqlQuery getStatsQuery();
   QSqlQueryModel * afficherActifs();
   bool sendCurrentPos(QString curr_pos);
   bool sendInitPos(int id , QString init_pos);


};

#endif // SPORTIF_H
