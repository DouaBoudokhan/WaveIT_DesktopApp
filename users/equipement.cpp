#include "equipement.h"
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
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
//#include <twilio-cpp/Services/Twilio/Twilio.h>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QImage>
#include <QCryptographicHash>
#include <QBuffer>
#include <QDateTime>

//using namespace cv;


equipement::equipement(int id,QString nom,QString imagepath,int quantite,QString etat,int nb,QString type,int prix,QString date)
{
    this->id=id;
    this->nom=nom;
    this->imagepath=imagepath;
    this->quantite=quantite;
    this->etat=etat;
    this->nb=nb;
    this->type=type;
    this->prix=prix;
    this->date=date;
}


void equipement::setid(int n){id=n;}
void equipement::setnom(QString n){nom=n;}
void equipement::setimagepath(QString n){imagepath=n;}
void equipement::setquantite(int n){quantite=n;}
void equipement::setetat(QString n){etat=n;}
void equipement::setnb(int n){nb=n;}
void equipement::settype(QString n){type=n;}
void equipement::setprix(int n){prix=n;}
void equipement::setdate(QString n){date=n;}

int equipement::get_id(){return id;}
QString equipement::get_nom(){return nom;}
QString equipement::get_imagepath(){return imagepath;}
int equipement::get_quantite(){return quantite;}
QString equipement::get_etat(){return etat;}
int equipement::get_nb(){return nb;}
QString equipement::get_type(){return type;}
int equipement::get_prix(){return prix;}
QString equipement::get_date(){return date;}


bool equipement::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    QString q = QString::number(quantite);
    QString n = QString::number(nb);
    QString p = QString::number(prix);

    QString select="INSERT INTO equipement VALUES (:id, :nom, :imagepath, :quantite, :etat, :nb, :type, :prix, :date)";
    query.prepare(select);

    // Binding values to the query
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":imagepath", imagepath);
    query.bindValue(":quantite", q);
    query.bindValue(":etat", etat);
    query.bindValue(":nb", n);
    query.bindValue(":type", type);
    query.bindValue(":prix", p);
    query.bindValue(":date", date);

    return query.exec();
}




QSqlQueryModel * equipement::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM equipement");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NAME"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("IMAGE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("QUANTITY"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("STATE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("USERS'NUMBER"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("TYPE_SPORT"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("PRICE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATE"));
    model->insertColumn(model->columnCount());
    model->insertColumn(model->columnCount());
    model->setHeaderData(9,Qt::Horizontal,QObject::tr(""));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr(""));





    return model;
}


bool equipement::supprimer(int idd)
{
    QSqlQuery query;
    QString res = QString::number(idd);
    query.prepare("delete from equipement where id = :id");
    query.bindValue(":id", res);

    return query.exec();
}

bool equipement::supprimer_all()
{
    QSqlQuery query;

    query.prepare("DELETE FROM equipement");
    return query.exec();
}

bool equipement::update()
{
    QSqlQuery query;

    QString resId = QString::number(id);
    QString q = QString::number(quantite);
    QString n = QString::number(nb);
    QString p = QString::number(prix);

    QString updateQuery = "UPDATE equipement"
                          " SET nom = :nom, imagepath = :imagepath, quantite = :quantite, etat = :etat, nb = :nb, type = :type, prix = :prix, date_e = :date "
                          "WHERE id = :id ";
    query.prepare(updateQuery);

    // Binding values to the query
    query.bindValue(":id", resId);
    query.bindValue(":nom", nom);
    query.bindValue(":imagepath", imagepath);
    query.bindValue(":quantite", q);
    query.bindValue(":etat", etat);
    query.bindValue(":nb", n);
    query.bindValue(":type", type);
    query.bindValue(":prix", p);
    query.bindValue(":date", date);

    return query.exec();
}


equipement equipement::getEquipementById(int id)
{
    QSqlQuery query;
    equipement equip;

    query.prepare("SELECT COUNT(*) FROM equipement WHERE id = :id");
    query.bindValue(":id", id);


    if(query.exec() && query.next())
    {
        int count = query.value(0).toInt();
        if(count > 0) {
            // L'ID existe dans la base de données, vous pouvez récupérer l'équipement
            query.prepare("SELECT * FROM equipement WHERE id = :id");
            query.bindValue(":id", id);
            if(query.exec() && query.next())
            {
                equip.setid(query.value(0).toInt());
                equip.setnom(query.value(1).toString());
                equip.setimagepath(query.value(2).toString());
                equip.setquantite(query.value(3).toInt());
                equip.setetat(query.value(4).toString());
                equip.setnb(query.value(5).toInt());
                equip.settype(query.value(6).toString());
                equip.setprix(query.value(7).toInt());
                equip.setdate(query.value(8).toString());
            }
        }
        else {

            equip.setid(-1); // ID invalide
        }
    }

    return equip;
}


QSqlQueryModel *equipement::search(const QString &criteria)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;


    QString checkQuery = "SELECT COUNT(*) FROM equipement WHERE nom = :criteria";
    query.prepare(checkQuery);
    query.bindValue(":criteria", criteria);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count == 0) {
            return nullptr;
        }
    } else {
        return nullptr;
    }
    query.prepare("SELECT * FROM equipement WHERE nom = :criteria");
    query.bindValue(":criteria", criteria);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("IMAGE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITY"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("USERS'NUMBER"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("TYPE_SPORT"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRICE"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATE"));
        model->insertColumn(model->columnCount());
        model->insertColumn(model->columnCount());
        model->setHeaderData(9,Qt::Horizontal,QObject::tr(""));
        model->setHeaderData(10,Qt::Horizontal,QObject::tr(""));

        return model;
    } else {
        return nullptr;
    }
}

QSqlQueryModel *equipement::sort(const QString &criteria)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    QString select = "SELECT * FROM equipement ORDER BY " + criteria;
    query.prepare(select);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("IMAGE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITY"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("USERS'NUMBER"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("TYPE_SPORT"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("PRICE"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATE"));
        model->insertColumn(model->columnCount());
        model->insertColumn(model->columnCount());
        model->setHeaderData(9,Qt::Horizontal,QObject::tr(""));
        model->setHeaderData(10,Qt::Horizontal,QObject::tr(""));

        return model;
    } else {
        return nullptr;
    }
}


bool equipement::exportToPdf()
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
                   "<h1>EQUIPEMENTS</h1>"
                   "<h2>Here you can find all the necessary information</h2>"
                   "<br />"
                   "<table>"
                   "<tr>"
                   "<th>ID</th>"
                   "<th>Nom</th>"
                   "<th>Image</th>"
                   "<th>Quantité</th>"
                   "<th>Etat</th>"
                   "<th>NB</th>"
                   "<th>Type</th>"
                   "<th>Prix</th>"
                   "<th>Date</th>"
                   "</tr>";

    // Fetch data from the database
    QSqlQuery query("SELECT * FROM equipement");
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
    printer.setOutputFileName("C:/Users/DOUA/Desktop/equipement.pdf");

    // Print the QTextDocument to the PDF
    doc.print(&printer);

    // Check if the document is empty
    if (doc.isEmpty()) {
        qDebug() << "Error printing to PDF";
        return false;
    }

    qDebug() << "PDF exported successfully.";
    return true;
}




void equipement::sendSMS(const QString& accountSid, const QString& authToken, const QString& from, const QString& to, const QString& message)
{
    QNetworkAccessManager manager;

    /*qInfo()<<QSslSocket::sslLibraryBuildVersionString();
    qInfo()<<QSslSocket::sslLibraryVersionString();*/
    QUrl url("https://api.twilio.com/2010-04-01/Accounts/AC89e96c705053ac7b02247b89cf3b7556/Messages.json");
    QNetworkRequest request(url);

    // Créer les données à envoyer
    QByteArray postData;
    QUrlQuery params;
    params.addQueryItem("From", from);
    params.addQueryItem("To", to);
    params.addQueryItem("Body", message);
    postData = params.toString(QUrl::FullyEncoded).toUtf8();

    // Définir les informations d'authentification
    QString combined = accountSid + ":" + authToken;
    QByteArray data = combined.toUtf8().toBase64();
    QString headerData = "Basic " + data;
    request.setRawHeader("Authorization", headerData.toUtf8());

    // Définir le type de contenu
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Envoyer la requête POST
    QNetworkReply* reply = manager.post(request, postData);

    // Handle SSL errors
    QObject::connect(reply, static_cast<void(QNetworkReply::*)(const QList<QSslError> &)>(&QNetworkReply::sslErrors),
                     [=](const QList<QSslError> &sslErrors){
        foreach (const QSslError &error, sslErrors) {
            qDebug() << "SSL Error:" << error.errorString();
        }
        reply->ignoreSslErrors(); // Ignorer les erreurs SSL et continuer
    });

    // Handle reply
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
       qDebug() << "SMS sent successfully!";
    } else {
        qDebug() << "Error sending SMS:" << reply->errorString();
    }

    reply->deleteLater();

}


void equipement::stat()
{
QSqlQuery query ;
    query.prepare("SELECT etat, COUNT(*) AS count FROM equipement GROUP BY etat ORDER BY count DESC;");
    query.exec();


    QBarSeries *series = new QBarSeries();

    while(query.next()){
       QString etat = query.value(0).toString();
       int count = query.value(1).toInt();
       QBarSet *barSet = new QBarSet(etat);
       *barSet << count;

       if (etat == "new")
           barSet->setColor(Qt::red);
       else if (etat == "used")
           barSet->setColor(Qt::green);
       else if (etat == "reconditioned")
           barSet->setColor(Qt::blue);

       series->append(barSet);
    }



    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Number of athletes / sport");



    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%i");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    chart->setTheme(QChart::ChartTheme::ChartThemeBlueNcs);

    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setWindowTitle("Statistics");
    chartview->resize(900,600);
    chartview->setVisible(true);
}




/*bool equipement::compareImages(const QString& imagePath1, const QString& imagePath2) {

    cv::Mat image1 = cv::imread(imagePath1.toStdString());
    cv::Mat image2 = cv::imread(imagePath2.toStdString());

    if (image1.empty() || image2.empty()) {
        qDebug() << "Failed to load images!";
        return false;
    }

    cv::Mat hsv_image1, hsv_image2;
    cv::cvtColor(image1, hsv_image1, cv::COLOR_BGR2HSV);
    cv::cvtColor(image2, hsv_image2, cv::COLOR_BGR2HSV);

    cv::Mat hist1, hist2;
    extractColorFeatures(hsv_image1, hist1);
    extractColorFeatures(hsv_image2, hist2);

    double color_similarity = compareColorFeatures(hist1, hist2);
    double color_threshold = 0.5;
    cv::Ptr<cv::Feature2D> orb = cv::ORB::create();

    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    cv::Mat descriptors1, descriptors2;

    orb->detectAndCompute(image1, cv::noArray(), keypoints1, descriptors1);
    orb->detectAndCompute(image2, cv::noArray(), keypoints2, descriptors2);

    cv::BFMatcher matcher(cv::NORM_HAMMING);

    std::vector<cv::DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

    double max_dist = 0;
    double min_dist = 100;

    for (int i = 0; i < descriptors1.rows; i++) {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }
    std::vector<cv::DMatch> good_matches;
    for (int i = 0; i < descriptors1.rows; i++) {
        if (matches[i].distance <= 2 * min_dist) {
            good_matches.push_back(matches[i]);
        }
    }

    qDebug() << "Color similarity: " << color_similarity;
    qDebug() << "Number of good matches: " << good_matches.size();

    if (color_similarity > color_threshold && good_matches.size() > 5) {
        qDebug() << "Images likely contain the same objects.";
        return false;
    } else {
        qDebug() << "Images do not contain the same objects.";
        return true;
    }
}

void equipement::extractColorFeatures(const cv::Mat& image, cv::Mat& features) {
    cv::Mat hsv_image;
    cv::cvtColor(image, hsv_image, cv::COLOR_BGR2HSV);

    int h_bins = 30;
    int s_bins = 32;
    int hist_size[] = {h_bins, s_bins};
    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 256};
    const float* ranges[] = {h_ranges, s_ranges};
    int channels[] = {0, 1};

    cv::calcHist(&hsv_image, 1, channels, cv::Mat(), features, 2, hist_size, ranges, true, false);
    cv::normalize(features, features, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
}

double equipement::compareColorFeatures(const cv::Mat& features1, const cv::Mat& features2) {
    double distance = cv::compareHist(features1, features2, cv::HISTCMP_CHISQR);
    double similarity = 1.0 / (1.0 + distance);

    return similarity;
}

*/
void equipement::metiers() {
   


    QSqlQuery query;
    query.prepare("SELECT u.date_deb, u.verif, u.image, e.imagepath,e.nom, s.lastname, s.phone, u.id_equip "
                  "FROM use u JOIN equipement e ON (u.id_equip=e.id) JOIN sportifs s ON (u.id_sportif=s.id)");
    query.exec();

    QDateTime currentDate = QDateTime::currentDateTime(); // Obtenir la date et l'heure actuelles
    QString currentDateString = currentDate.toString("yyyy-MM-dd hh:mm:ss");

    while (query.next()) {
        int useId = query.value("id_equip").toInt();
        QString image_use = query.value("image").toString();
        QString imagepath_equip = query.value("imagepath").toString();
        QString nom_sportif = query.value("lastname").toString();
        QString num = query.value("phone").toString();
        QString date_deb_str = query.value("date_deb").toString();

        QString nom_e=query.value("nom").toString();
        QString verif=query.value("verif").toString();
        if (verif=="No"){
            QString msg;
            QDateTime date_deb = QDateTime::fromString(date_deb_str, "yyyy-MM-dd hh:mm:ss");

            qint64 differenceInSeconds = qAbs(currentDate.toUTC().secsTo(date_deb.toUTC()));
            qint64 thresholdInSeconds = 2 * 60 * 60 + 30 * 60;
            QString to = QString("+216%1").arg(num);
            int hours = differenceInSeconds / 3600;
            int minutes = (differenceInSeconds % 3600) / 60;
            int seconds = differenceInSeconds % 60;

            if (differenceInSeconds > thresholdInSeconds) {
                if (image_use.isEmpty()){

                QString to = QString("+216%1").arg(num);
                 msg = QString("Monsieur/Madame %1, vous n'avez pas rendu l'équipement %2, cela fait %3 heure(s) %4 minute(s) %5 seconde(s)")
                                  .arg(nom_sportif)
                                  .arg(nom_e)
                                  .arg(hours)
                                  .arg(minutes)
                                  .arg(seconds);
                qDebug()<<msg;
                sendSMS(accountSid, authToken, from, to, msg);

                }else{
                    bool test = true;//compareImages(image_use, imagepath_equip);
                    if (test==false){
                         msg = QString("Monsieur/Madame %1, nous vous prions de bien vouloir rendre l'équipement %2 à temps lors de votre prochaine visite.")
                                          .arg(nom_sportif)
                                          .arg(nom_e);
                        qDebug()<<msg;
                        sendSMS(accountSid, authToken, from, to, msg);
                    }
                    else{
                         msg = QString("Monsieur/Madame %1, Vous deviez rendre l'équipement %2 il y a %3 heure(s), %4 minute(s) et %5 seconde(s)."
                                              " Cependant, l'équipement que vous avez rendu est endommagé. Vous êtes prié(e) de payer sa valeur.")
                                            .arg(nom_sportif)
                                            .arg(nom_e)
                                            .arg(hours)
                                            .arg(minutes)
                                            .arg(seconds);
                        qDebug()<<msg;
                        sendSMS(accountSid, authToken, from, to, msg);
                    }
                }
            }else if (differenceInSeconds <= thresholdInSeconds && !image_use.isEmpty()) {
                bool test = true;//compareImages(image_use, imagepath_equip);
                if (test==true) {
                    msg = QString("Monsieur/Madame %1, l'équipement %2 que vous avez rendu est endommagé. Vous êtes prié(e) de payer sa valeur.")
                            .arg(nom_sportif)
                            .arg(nom_e);
                    qDebug()<<msg;
                    sendSMS(accountSid, authToken, from, to, msg);
                }

            }
        //changer verif to yes in table use

            query.prepare("UPDATE use SET verif = :verif WHERE id_equip = :id ");

            query.bindValue(":verif", "Yes");
            query.bindValue(":id", useId);
            query.exec();
        }
    }
}


void equipement::check()
{
    QSqlQuery equipQuery("SELECT id FROM equipement");
    while (equipQuery.next()) {
        int equipId = equipQuery.value("id").toInt();

        // Check if the equipment ID exists in the use table
        QSqlQuery useQuery;
        useQuery.prepare("SELECT COUNT(*) FROM use WHERE id_equip = :equipId");
        useQuery.bindValue(":equipId", equipId);
        useQuery.exec();

        if (useQuery.next()) {
            int useCount = useQuery.value(0).toInt();
            // If the equipment is used, increment its 'nb' attribute by 1
            if (useCount > 0) {
                QSqlQuery updateQuery;
                updateQuery.prepare("UPDATE equipement SET nb = nb + 1 WHERE id = :equipId");
                updateQuery.bindValue(":equipId", equipId);
                updateQuery.exec();
            }
        }
    }
}

QString equipement::generateChatbotReply(const QString& message)
{
    QString reply;
    QString msg = message.toLower();

    if (msg.contains("hello") || msg.contains("hi"))
    {
        reply = "Hello!";
    }
    else if (msg.contains("how are you"))
    {
        reply = "I'm doing well, thank you! How about you?";
    }
    else if (msg.contains("fine") || msg.contains("good"))
    {
        reply = "That's great to hear!";
    }
    else if (msg.contains("bad"))
    {
        reply = "I'm sorry to hear that.";
    }
    else if (msg.contains("my name"))
    {
        reply= "I am sorry but I don't know your name";
    }

    else if (msg.contains("sad"))
    {
        reply = "Don't be sad. Everything's gonna be alright. Cheer up!";
    }
    else if (msg.contains("happy"))
    {
        reply = "Glad to hear!";
    }
    else if (msg.contains("thank"))
    {
        reply = "Your welcome!";
    }
    else if (msg.contains("ok"))
    {
        reply="Yes, ok!";
    }

    else if (msg.contains("your name"))
    {
        reply = "My name is 'equipie'.";
    }
    else if (msg.contains("most used"))
    {
        QSqlQuery query;
        if(query.exec("SELECT id, nom FROM equipement WHERE nb = (SELECT MAX(nb) FROM equipement)"))
        {
            QStringList most;
            while(query.next()){
                QString id = query.value(0).toString();
                QString nom = query.value(1).toString();
                most.append(id + "| " + nom);
            }
            if(!most.isEmpty()){
                reply = "The most used equipment(s) is/are: \n";
                reply += most.join("\n");}
            else{
                reply = "There are no records in the database."; }
        }
     }
    else if (msg.contains("least used"))
    {
        QSqlQuery query;
        if(query.exec("SELECT id, nom FROM equipement WHERE nb = (SELECT MIN(nb) FROM equipement)"))
        {
            QStringList least;
            while(query.next()){
                QString id = query.value(0).toString();
                QString nom = query.value(1).toString();
                least.append(id + "| " + nom);
            }
            if(!least.isEmpty()){
                reply = "The least used equipment(s) is/are: \n";
                reply += least.join("\n");}
            else{
                reply = "There are no records in the database."; }
        }

    }
    else if (msg.contains("in use") || msg.contains("not being used"))
    {
        QSqlQuery query;
        if(query.exec("SELECT e.id, e.nom FROM equipement e LEFT JOIN use u ON e.id = u.id_equip WHERE u.id_equip IS NULL"))
        {
            QStringList notInUseEquipments;
            while(query.next())
            {
                QString id = query.value(0).toString();
                QString nom = query.value(1).toString();
                notInUseEquipments.append(id + ": " + nom + "\n");
            }
            if(!notInUseEquipments.isEmpty())
            {
                reply = "The available equipment(s) are: \n";
                reply += notInUseEquipments.join("\n");
            }
            else
            {
                reply = "All equipment are currently in use.";
            }
        }
    }

    else if (msg.contains("need to be reconditioned")) {
        QSqlQuery query;
        QString selectQuery = "SELECT id, nom FROM equipement WHERE (etat = 'new' OR etat = 'used') AND nb > 15";
        if (query.exec(selectQuery)) {
            QStringList needReconditioningEquipments;
            while (query.next()) {
                QString id = query.value(0).toString();
                QString nom = query.value(1).toString();
                needReconditioningEquipments.append(id + "| " + nom + "\n");
            }
            if (!needReconditioningEquipments.isEmpty()) {
                reply = "The equipment(s) that need to be reconditioned are/is: \n";
                reply += needReconditioningEquipments.join("");
            } else {
                reply = "All equipment are in a good state.";
            }
        } else {
            qDebug() << "Query execution failed:" << query.lastError().text();
        }
    }
    else if (msg.contains("without")) {
        QSqlQuery query;
        QStringList list;
        if (query.exec("SELECT id, question FROM historique")) {
            while (query.next()) {
                QString quest = query.value(1).toString();
                list.append(quest);
            }
            if (!list.isEmpty()) {
                reply = "The questions with non provided answers are: \n";
                reply += list.join("\n");
            } else {
                reply = "There are no records in the database.";
            }
        }
    }


    else if (msg.contains("oldest"))
    {
        QSqlQuery query;
        if(query.exec("SELECT id, nom FROM equipement ORDER BY date_e ASC"))
        {
            QStringList oldestEquipments;
            while(query.next())
            {
                QString id = query.value(0).toString();
                QString nom = query.value(1).toString();
                oldestEquipments.append(id + ": " + nom);
            }
            if (!oldestEquipments.isEmpty())
            {
                reply = "The oldest equipment(s) are: \n";
                reply += oldestEquipments.join("\n");
            }
            else
            {
                reply = "No equipment found.";
            }
        }
    }





    else {
        reply = "Unfortunately, I couldn't find an answer right now. However, I'll make sure to provide one next time.";
        QSqlQuery query;

        QString select = "INSERT INTO historique (question) VALUES (:question)";
        query.prepare(select);

        query.bindValue(":question", msg);
        query.exec();
    }

    return reply;
}

void equipement::update_nb(int id)
{
    QSqlQuery query;
    int n=0;
    QString updateQuery = "UPDATE equipement SET nb = :nb WHERE id = :id";
    query.prepare(updateQuery);
    query.bindValue(":nb", n);
    query.bindValue(":id", id);
    query.exec();
    if (query.exec()) {
    qDebug() << "Update successful";
    } else {
    qDebug() << "Update failed:" << query.lastError().text();
    }
}

