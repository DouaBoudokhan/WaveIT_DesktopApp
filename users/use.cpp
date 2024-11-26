#include "use.h"
#include <QSqlError>

use::use()
{

}

use::use(int id_e,int id_s,QString d,QString i,QString v)
{
    id_equip=id_e;
    id_sportif=id_s;
    date=d;
    image=i;
    verif=v;
}

void use::setid_equip(int id_e){id_equip=id_e;}
void use::setid_sportif(int id_s){id_sportif=id_s;}
void use::setdate(QString d){date=d;}
void use::setimage(QString i){image=i;}
void use::setverif(QString v){verif=v;}

//
int use::getid_equip(){return id_equip;}
int use::getid_sportif(){return id_sportif;}
QString use::getdate(){return date;}
QString use::getimage(){return image;}
QString use::getverif(){return verif;}


bool use::ajouter()
{
    QSqlQuery query;
    QString id_e = QString::number(id_equip);
    QString id_s = QString::number(id_sportif);

    QString select="INSERT INTO use VALUES (:id_equip, :id_sportif, :date_deb, :image, :verif)";
    query.prepare(select);

    query.bindValue(":id_equip", id_e);
    query.bindValue(":id_sportif", id_s);
    query.bindValue(":date_deb", date);
    query.bindValue(":image", image);
    query.bindValue(":verif", verif);


    return query.exec();
}




QSqlQueryModel * use::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM use");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Equipement's Identifier"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Sportmen's Identifier"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Image"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Verification"));


    model->insertColumn(model->columnCount());
    model->insertColumn(model->columnCount());
    model->setHeaderData(5,Qt::Horizontal,QObject::tr(""));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr(""));





    return model;
}


bool use::supprimer(int idd)
{
    QSqlQuery query;
    QString id_e = QString::number(idd);
    query.prepare("delete from use where id_equip = :id");
    query.bindValue(":id", id_e);

    return query.exec();
}

bool use::supprimer_all()
{
    QSqlQuery query;

    query.prepare("DELETE FROM use");
    return query.exec();
}

bool use::update() {
    QSqlQuery query;

    QString updateQuery = "UPDATE use SET date_deb = :date, image = :image, verif = :verif WHERE id_equip = :id_equip AND id_sportif = :id_sportif";

    query.prepare(updateQuery);

    query.bindValue(":id_equip", id_equip);
    query.bindValue(":id_sportif", id_sportif);
    query.bindValue(":image", image);
    query.bindValue(":date", date);
    query.bindValue(":verif", verif);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    return true;
}


use use::getEquipementById(int id)
{
    QSqlQuery query;
    use u;

    query.prepare("SELECT COUNT(*) FROM use WHERE id_equip = :id");
    query.bindValue(":id", id);


    if(query.exec() && query.next())
    {
        int count = query.value(0).toInt();
        if(count > 0) {
            query.prepare("SELECT * FROM use WHERE id_equip = :id");
            query.bindValue(":id", id);
            if(query.exec() && query.next())
            {
                u.setid_equip(query.value(0).toInt());
                u.setid_sportif(query.value(1).toInt());
                u.setdate(query.value(2).toString());
                u.setimage(query.value(3).toString());
                u.setverif(query.value(4).toString());

            }
        }
        else {

            u.setid_equip(-1); // ID invalide
        }
    }

    return u;
}


QVector<QString> use::retrieve_id_equip() {
    QVector<QString> equipmentIDs;

    QSqlQuery query;
    query.prepare("SELECT id,nom FROM equipement");
    query.exec();

    while (query.next()) {
        QString nom = query.value(1).toString();
        equipmentIDs.push_back(nom);
    }


    return equipmentIDs;
}


QVector<QString> use::retrieve_id_sportif() {
    QVector<QString> sportifIDs;

    QSqlQuery query;

    query.prepare("SELECT name,lastname FROM sportifs");
    query.exec();

    while (query.next()) {
        QString nom = query.value(0).toString();
        QString prenom = query.value(1).toString();
        QString both= nom+" "+prenom;
        sportifIDs.push_back(both);
    }

    return sportifIDs;
}


int use::chercherIDE(QString nom)
{
    QSqlQuery query;

    query.prepare("SELECT id FROM equipement WHERE nom = :nom");
    query.bindValue(":nom", nom);
    query.exec();

    if (query.next()) {
        int id = query.value(0).toInt();
        return id;
    } else {
        return -1;
    }
}

int use::chercherIDS(QString nom)
{
    QSqlQuery query;

    query.prepare("SELECT id FROM sportifs WHERE name = :nom");
    query.bindValue(":nom", nom);
    query.exec();

    if (query.next()) {
        int id = query.value(0).toInt();
        return id;
    } else {
        return -1;
    }
}

QString use::chercherNOME(int id)
{
    QSqlQuery query;

    query.prepare("SELECT nom FROM equipement WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    if (query.next()) {
        QString nom = query.value(0).toString();
        return nom;
    }
    return " ";
}

QString use::chercherNOMS(int id)
{
    QSqlQuery query;

    query.prepare("SELECT name, lastname FROM sportifs WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    if (query.next()) {
        QString nom = query.value(0).toString();
        QString prenom = query.value(1).toString();
        QString both= nom+" "+prenom;
        return both;
    }
    return " ";
}
