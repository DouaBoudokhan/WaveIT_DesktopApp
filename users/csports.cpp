#include "csports.h"
#include <QPixmap>
#include <QtWidgets>
#include <QPdfWriter>
#include <QPdfWriter>
#include <QTextDocument>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QPrinter>
#include <QTextDocument>
#include <QTextCursor>
#include <QDebug>
#include <QSqlRecord>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>






csports::csports()
{
    Id_sport=0;
    nom="";
    description="";
    nb_sportif=0;
    age_min=0;
    frequence="";
}
csports::csports(int id,QString nom,QString description,int nb_sportif,int age_min,QString frequence)
{
    this->Id_sport=id;
    this->nom=nom;
    this->description=description;
    this->nb_sportif=nb_sportif;
    this->age_min=age_min;
    this->frequence=frequence;
}
bool csports::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(Id_sport);
    query.prepare("insert into tabsports (Id_sport,nom,description,nb_sportif,age_min,frequence)" "values (:id,:nom,:description,:nb_sportif,:age_min,:frequence)");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":description",description);
    query.bindValue(":nb_sportif",nb_sportif);
    query.bindValue(":age_min",age_min);
    query.bindValue(":frequence",frequence);

    return query.exec();
}
QSqlQueryModel * csports::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM tabsports");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_sport"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("nb_sportif"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("age_min"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("frequence"));
    model->insertColumn(model->columnCount());
    model->insertColumn(model->columnCount());
    model->setHeaderData(9,Qt::Horizontal,QObject::tr(""));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr(""));

    return model;
}
bool csports::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("delete from tabsports where Id_sport= :id");
    query.bindValue(":id",res);
    return query.exec();
}
bool csports::modifier(int id, QString nom, QString description, int nb_sportif, int age_min, QString frequence)
{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("UPDATE tabsports SET nom=:nom, description=:description, nb_sportif=:nb_sportif, age_min=:age_min, frequence=:frequence WHERE Id_sport=:id");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":nb_sportif", nb_sportif);
    query.bindValue(":age_min", age_min);
    query.bindValue(":frequence", frequence);
    return query.exec();
}

csports csports::getsportsById(int id)
{
    QSqlQuery query;
    csports s;

    // Préparation de la requête SQL avec une clause WHERE pour filtrer par ID
    query.prepare("SELECT * FROM tabsports WHERE Id_sport= :id");
    query.bindValue(":id", id);

    // Exécution de la requête
    if(query.exec() && query.next())
    {
        // Récupération des valeurs de la requête et attribution à l'objet equipement
        s.set_id(query.value(0).toInt());
        s.set_nom(query.value(1).toString());
        s.set_description(query.value(2).toString());
        s.set_age_min(query.value(3).toInt());
        s.set_nb_sportif(query.value(4).toInt());
        s.set_frequence(query.value(5).toString());
    }

    return s;
}
bool csports::checkIfIdExists(int id)
{
    QSqlQuery query;
        query.prepare("SELECT Id_sport FROM tabsports WHERE Id_sport = :id");
        query.bindValue(":id", id);

        if (query.exec() && query.next()) {
            // ID exists
            return true;
        } else {
            // ID does not exist or query execution failed
            QMessageBox::warning(nullptr, "Database Error", "Error checking ID existence: " + query.lastError().text());
            return false;
        }
}
bool csports::supprimer_all()
{
    QSqlQuery query;

    query.prepare("DELETE FROM tabsports");
    return query.exec();
}
////////////////////////////////// metier//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QSqlQueryModel *csports::search(const QString &criteria)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;


    QString checkQuery = "SELECT COUNT(*) FROM tabsports WHERE nom LIKE :criteria";
    query.prepare(checkQuery);
    query.bindValue(":criteria", criteria + "%"); // Append % to match names starting with 'criteria'

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count == 0) {
            return nullptr;
        }
    } else {
        return nullptr;
    }


    query.prepare("SELECT * FROM tabsports WHERE nom LIKE :criteria");
    query.bindValue(":criteria", criteria + "%");

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id_sport"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("nb_sportif"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("age_min"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("frequence"));
        model->insertColumn(model->columnCount());
        model->insertColumn(model->columnCount());
        model->setHeaderData(8,Qt::Horizontal,QObject::tr(""));
        model->setHeaderData(9,Qt::Horizontal,QObject::tr(""));

        return model;
    } else {
        return nullptr;
    }
}

bool csports::exportToPdf()
{
    // Début de la création du contenu HTML
    QString htmlContent = "<div style='text-align: center;'><h1 style='color: orange;'>Gestion des Sports</h1>";
    htmlContent += "<p>Notre application offre une gestion efficace des sports, permettant aux utilisateurs de suivre et d'organiser facilement une grande variété d'activités sportives offrant ainsi aux utilisateurs une expérience optimale et personnalisée</p></div><br><br><br><br>";

    // Titre et début du tableau
    htmlContent += "<div style='text-align: center;'><h1 style='color: orange;'>Tableau des Sports</h1></div>";
    htmlContent += "<table style='border-collapse: collapse; width: 100%; margin: auto;'>";
    htmlContent += "<thead><tr>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>id</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>nom</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>description</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>age_min</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>nb_sportif</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>frequence</th>"
                   "</tr></thead>";

    // Corps du tableau (remplissage des données)
    QSqlQuery query("SELECT * FROM tabsports");
    htmlContent += "<tbody>";
    while (query.next()) {
        htmlContent += "<tr>";
        for (int i = 0; i < query.record().count(); ++i) {
            htmlContent += "<td style='border: 1px solid #000; padding: 8px;'>" + query.value(i).toString() + "</td>";
        }
        htmlContent += "</tr>";
    }
    htmlContent += "</tbody>";

    // Fin du tableau et ajout de l'image
    htmlContent += "</table></div><br><br><br><br>";
    QString logoHtml = "<div style='margin: auto;'><img src='C:/Users/kamou/Desktop/logo.png' alt='Logo' style='max-width: 40px;'>";
    htmlContent += logoHtml;

    // Get path to user's Documents directory
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    // Set the output file path to the documents directory
    QString filePath = documentsPath + "/sports.pdf";

    // Create a QTextDocument and set its HTML content
    QTextDocument doc;
    doc.setHtml(htmlContent);

    // Create a QPrinter
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    // Print the document to the printer
    doc.print(&printer);

    if (doc.isEmpty()) {
        qDebug() << "Error printing to PDF:" ;
        return false;
    }

    qDebug() << "PDF exported successfully to:" << filePath;
    return true;
}
QSqlQueryModel* csports::getSportStatistics()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT nb_sportif, COUNT(ID_sport) as sport_count FROM tabsports GROUP BY nb_sportif");

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("nb_sportif"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("sport_count"));
        return model;
    } else {
        qDebug() << "Error retrieving event statistics:" << query.lastError().text();
        return nullptr;
    }
}
QSqlQueryModel *csports::sort(const QString &criteria)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    QString select = "SELECT * FROM tabsports ORDER BY " + criteria+" ASC";
    query.prepare(select);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id_sport"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("nb_sportif"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("age_min"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("frequence"));
        model->insertColumn(model->columnCount());
        model->insertColumn(model->columnCount());
        model->setHeaderData(8,Qt::Horizontal,QObject::tr(""));
        model->setHeaderData(9,Qt::Horizontal,QObject::tr(""));
        return model;
    } else {
        return nullptr;
    }
}
void csports::onNetworkReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QString weatherData = QString::fromUtf8(data); // Convertir les données en QString
        qDebug() << "Weather data:" << weatherData;
        // Utilisez weatherData comme vous le souhaitez, par exemple, l'afficher dans une fenêtre
    } else {
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater();
}








