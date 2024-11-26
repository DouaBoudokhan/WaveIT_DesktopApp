#include "sportif.h"
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QTextDocument>
#include <QTextCursor>
#include <QPrinter>
#include <QSqlQuery>
#include <QPair>
#include <event.h>



Sportif::Sportif(){};
Sportif::Sportif(
        int id ,
QString nom ,
QString prenom ,
int age  ,
QString adresse,
 QString mail,
QString num_tel,
QString niveau,
QString type_sport ,
QVariant image
        )
{
    this->id =id;
    this->nom = nom ;
    this->prenom = prenom  ;
    this->age  =age;
    this->adresse= adresse;
    this->mail=mail;
    this->num_tel= num_tel;
    this->niveau=niveau;
    this->type_sport=type_sport;
    this->frequency =0;
    this->image = image;
}
Sportif::Sportif(
        int id ,
QString nom ,
QString prenom ,
int age  ,
QString adresse,
 QString mail,
QString num_tel,
QString niveau,
QString type_sport
        )
{
    this->id =id;
    this->nom = nom ;
    this->prenom = prenom  ;
    this->age  =age;
    this->adresse= adresse;
    this->mail=mail;
    this->num_tel= num_tel;
    this->niveau=niveau;
    this->type_sport=type_sport;
    this->frequency =0;
}


//setters
void Sportif::setId(int n){id = n ;};
void Sportif::setNom(QString n){nom = n ;};
void Sportif::setPrenom(QString n){prenom = n;};
void Sportif::setAge(int n){age=n;};
void Sportif::setAdresse(QString n){adresse=n;};
void Sportif::setNumTel(QString n){num_tel=n;};
void Sportif::setMail(QString n){mail=n;};
void Sportif::setTypeSport(QString n){type_sport=n;};
void Sportif::setNiveau(QString n){niveau=n;};
void Sportif::setFrequency(int n){frequency=n;};

//getters
int Sportif::getId(){return id;};
QString Sportif::getNom(){return nom;};
QString Sportif::getPrenom(){return prenom;};
int Sportif::getAge(){return age;};
QString Sportif::getAdresse(){return adresse;};
QString Sportif::getNumTel(){return num_tel;};
QString Sportif::getMail(){return mail;};
QString Sportif::getTypeSport(){return type_sport;};
QString Sportif::getNiveau(){return niveau;};
int Sportif::getFrequency(){return frequency;};

//CRUD
bool Sportif::ajouter()
{
    QSqlQuery query;
    query.prepare("insert into Sportifs (id,name,lastname,age,adress,phone,email,sport_type,lvl,frequency,image)" "values (:id,:nom,:prenom , :age, :adresse , :num_tel ,:mail,:type_sport,:niveau ,:frequency,:image)");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":age",age);
    query.bindValue(":adresse",adresse);
    query.bindValue(":num_tel",num_tel);
    query.bindValue(":mail",mail);
    query.bindValue(":type_sport",type_sport);
    query.bindValue(":niveau",niveau);
    query.bindValue(":frequency",frequency);
    query.bindValue(":image",image);
    return query.exec();
}






 QSqlQueryModel * Sportif::afficher(const QPair <int , QString> &param)
{
    QSqlQueryModel * model=new QSqlTableModel();
    QSqlQuery query;
    if (param.second==""){
        qDebug()<<"no var query";
        query.prepare("select id, name,lastname,adress,email,sport_type,phone,frequency,lvl,age from Sportifs");
    }
    else{
        switch (param.first) {
        case 0 : {
            qDebug()<<"id query search";
            query.prepare("select * from Sportifs where TO_CHAR(id) LIKE '"+param.second+"%'");
            break;
        }
        case 1 : {
            qDebug()<<"name query search";
            query.prepare("select * from Sportifs where lower(name) LIKE lower('%"+param.second+"%')");
            break;
        }
        case 2 : {
            qDebug()<<"phone query search";
            query.prepare("select * from Sportifs where phone LIKE '"+param.second+"%'");
            break;
        }
        case 3 : {
            qDebug()<<"mail query search";
            query.prepare("select * from Sportifs where lower(email) LIKE lower('%"+param.second+"%')");
            break;
        }
    }
}
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NAME"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("LASTNAME"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESS"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("SPORT TYPE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("PHONE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("FREQUENCY"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("LEVEL"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("AGE"));
    model->insertColumn(model->columnCount());
    model->insertColumn(model->columnCount());
    model->setHeaderData(10,Qt::Horizontal,QObject::tr(""));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr(""));
    model->setHeaderData(12,Qt::Horizontal,QObject::tr("IMAGE"));


    return model;
}
bool Sportif::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("delete from Sportifs where id= :id");
    query.bindValue(":id",id);
    return query.exec();

}

QSqlQueryModel * Sportif::afficherActifs()
{
   QSqlQueryModel * model=new QSqlTableModel();
   QSqlQuery query;
       query.prepare("select id , name , lastname,age, lvl, phone,init_pos,curr_pos  from Sportifs where curr_pos is not null");
   query.exec();

   model->setQuery(query);
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("NAME"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("LASTNAME"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("AGE"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("LEVEL"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("PHONE"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("INITIAL POS"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("CURRENT POS"));
   model->insertColumn(model->columnCount());
   model->setHeaderData(8,Qt::Horizontal,QObject::tr(""));


   return model;
}



// for alaa
bool Sportif::sendCurrentPos(QString curr_pos){
    QSqlQuery query;

    query.prepare("update Sportifs set curr_pos=:curr_pos WHERE id=1");
    query.bindValue(":id",1);
     query.bindValue(":curr_pos",curr_pos);


    return query.exec();

}
bool Sportif::sendInitPos(int id , QString init_pos){
    QSqlQuery query;

    query.prepare("update Sportifs set init_pos=:curr_pos WHERE id=:id");
    query.bindValue(":id",id);
     query.bindValue(":curr_pos",init_pos);
    return query.exec();

}








bool Sportif::modifier(Sportif sp)
{
    QSqlQuery query;

    query.prepare("update Sportifs set name=:nom,lastname=:prenom , age=:age, adress=:adresse , phone=:num_tel ,email=:mail, sport_type=:type_sport, lvl=:niveau WHERE id=:id");
    query.bindValue(":id",sp.getId());
    query.bindValue(":nom",sp.getNom());
    query.bindValue(":prenom",sp.getPrenom());
    query.bindValue(":age",sp.getAge());
    query.bindValue(":adresse",sp.getAdresse());
    query.bindValue(":num_tel",sp.getNumTel());
    query.bindValue(":mail",sp.getMail());
    query.bindValue(":type_sport",sp.getTypeSport());
    query.bindValue(":niveau",sp.getNiveau());

    return query.exec();
}

bool Sportif::supprimerTous(){

    QSqlQuery query;
    query.prepare("delete from Sportifs");
    return query.exec();

}

QSqlQuery Sportif::getStatsQuery(){
    QSqlQuery query ;
    query.prepare("SELECT lvl, COUNT(*) AS count_of_athletes  FROM Sportifs GROUP BY lvl order by count_of_athletes desc;");
    query.exec();
    return query;
}












