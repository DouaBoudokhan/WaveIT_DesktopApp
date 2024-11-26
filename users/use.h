#ifndef USE_H
#define USE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

class use
{
    int id_equip,id_sportif;
    QString date,image,verif;
public:
    use();
    use(int id_e,int id_s,QString d,QString i,QString v);

    //CRUD
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int idd);
    bool supprimer_all();
    bool update();
    use getEquipementById(int id);
    QVector<QString> retrieve_id_equip();
    QVector<QString> retrieve_id_sportif();
    int chercherIDE(QString nom);
    int chercherIDS(QString nom);
    QString chercherNOME(int id);
    QString chercherNOMS(int id);



    //setters
    void setid_equip(int id_e);
    void setid_sportif(int id_s);
    void setdate(QString d);
    void setimage(QString i);
    void setverif(QString i);

    //getters
    int getid_equip();
    int getid_sportif();
    QString getdate();
    QString getimage();
    QString getverif();



};

#endif // USE_H
