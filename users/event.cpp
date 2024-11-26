#include "event.h"

Event::Event()
{
    id=0;
    nom="";
    age=0;
    lieu="";
    dure=0;
    type="";
    QDate date(2024, 2, 29);
    prix=0;
    winner=NULL;
    done=0;
}

Event::Event(int id,QString nom,int age,QString lieu,QDate date,int dure,QString type,QString niveau, int prix)
{
    this->id=id;
    this->nom=nom;
    this->age=age;
    this->lieu=lieu;
    this->date=date;
    this->dure=dure;
    this->type=type;
    this->prix=prix;
    this->niveau=niveau;
    this->winner=NULL;
}
bool Event::checkIfIdExists(int id)
{
    QSqlQuery query;
        query.prepare("SELECT id_event FROM event WHERE id_event = :id");
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
bool Event::ajouter()
{
    // Check if the ID already exists
       if (checkIfIdExists(id)) {
           QMessageBox::warning(nullptr, "Error", "Event with this ID already exists.");
           return false;
       }
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("insert into event (id_event,nom,age,lieu,date_event,dure,type,prix_inscrit,niveau)" "values (:id,:nom,:age,:lieu,:date,:dure,:type,:prix,:niveau)");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":age",age);
    query.bindValue(":lieu",lieu);
    query.bindValue(":date",date);
    query.bindValue(":dure",dure);
    query.bindValue(":type",type);
    query.bindValue(":prix",prix);
    query.bindValue(":niveau",niveau);

    return query.exec();
}
QSqlQueryModel * Event::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from event");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_event"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("age"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("lieu"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_event"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("dure"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("prix_inscrit"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("niveau"));
    model->insertColumn(model->columnCount());
    model->insertColumn(model->columnCount());
    model->setHeaderData(9,Qt::Horizontal,QObject::tr(""));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr(""));

    return model;
}
bool Event::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("delete from event where id_event=:id");
    query.bindValue(":id",res);
    return query.exec();
}
bool Event::modifier(int id, QString nom, int age, QString lieu, QDate date, int dure, QString type,QString niveau,int prix)
{
    QSqlQuery query;
    QString res=QString::number(id);

    query.prepare("update event set nom=:nom,age=:age,lieu=:lieu,date_event=:date,dure=:dure,type=:type,niveau=:niveau,prix_inscrit=:prix where id_event=:id");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":age",age);
    query.bindValue(":lieu",lieu);
    query.bindValue(":date",date);
    query.bindValue(":dure",dure);
    query.bindValue(":type",type);
    query.bindValue(":prix",prix);
    query.bindValue(":niveau",niveau);


    return query.exec();
}
bool Event::supprimer_all()
{
    QSqlQuery query;
    query.prepare("delete from event");
    return query.exec();
}
Event Event::getEventById(int id)
{
    QSqlQuery query;
    Event even;

    query.prepare("SELECT * FROM event WHERE id_event= :id");
    query.bindValue(":id", id);

    // Exécution de la requête
    if(query.exec() && query.next())
    {
        even.set_id(query.value(0).toInt());
        even.set_nom(query.value(1).toString());
        even.set_age(query.value(2).toInt());
        even.set_lieu(query.value(3).toString());
        even.set_date(query.value(4).toDate());
        even.set_dure(query.value(5).toInt());
        even.set_type(query.value(6).toString());
        even.set_prix(query.value(7).toInt());
        even.set_niveau(query.value(8).toString());

    }

    return even;
}

bool Event::exportToPdf()
{

    QString htmlContent = "<div style='text-align: center;'><h1 style='color: orange;'>Gestion d'evenement</h1>";
    htmlContent += "<p>Notre application offre une gestion efficace des sports, permettant aux utilisateurs de suivre et d'organiser facilement une grande variété d'activités sportives offrant ainsi aux utilisateurs une expérience optimale et personnalisée</p></div><br><br><br><br>";


    htmlContent += "<div style='text-align: center;'><h1 style='color: orange;'>Scouts evenements</h1></div>";
    htmlContent += "<table style='border-collapse: collapse; width: 100%; margin: auto;'>";
    htmlContent += "<thead><tr>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>id</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>nom</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>age</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>lieu</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>date</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>dure</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>type</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>prix</th>"
                   "<th style='border: 1px solid #000; padding: 8px; text-align: left;font-weight: bold;'>niveau</th>"

                   "</tr></thead>";
    QSqlQuery query("SELECT * FROM event");

    htmlContent += "<tbody>";

    while (query.next()) {
        htmlContent += "<tr>";
        for (int i = 0; i < query.record().count(); ++i) {
            htmlContent += "<td style='border: 1px solid #000; padding: 8px;'>" + query.value(i).toString() + "</td>";
        }
        htmlContent += "</tr>";
    }
    htmlContent += "</tbody>";

    htmlContent += "</table></div><br><br><br><br>";
    QString logoHtml = "<div style='margin: auto;'><img src=':/img/logo.png' alt='Logo' style='max-width: 40px;'>";
    htmlContent += logoHtml;


    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    QString filePath = documentsPath + "/evenement/event.pdf";

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

QSqlQueryModel *Event::search(const QString &criteria)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;


    QString checkQuery = "SELECT COUNT(*) FROM event WHERE nom LIKE :criteria";
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


    query.prepare("SELECT * FROM event WHERE nom LIKE :criteria");
    query.bindValue(":criteria", criteria + "%");

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_event"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("age"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("lieu"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_event"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("dure"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("prix_inscrit"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("niveau"));
        model->insertColumn(model->columnCount());
        model->insertColumn(model->columnCount());
        model->setHeaderData(9,Qt::Horizontal,QObject::tr(""));
        model->setHeaderData(10,Qt::Horizontal,QObject::tr(""));
        return model;
    } else {
        return nullptr;
    }
}

QSqlQueryModel *Event::sort(const QString &criteria)
{
    QSqlQueryModel *model = new QSqlQueryModel();
       QSqlQuery query;

       QString select = "SELECT * FROM event ORDER BY " + criteria + " ASC";
       query.prepare(select);

       if (query.exec()) {
           model->setQuery(query);
           model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_event"));
           model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
           model->setHeaderData(2,Qt::Horizontal,QObject::tr("age"));
           model->setHeaderData(3,Qt::Horizontal,QObject::tr("lieu"));
           model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_event"));
           model->setHeaderData(5,Qt::Horizontal,QObject::tr("dure"));
           model->setHeaderData(6,Qt::Horizontal,QObject::tr("type"));
           model->setHeaderData(7,Qt::Horizontal,QObject::tr("prix_inscrit"));
           model->setHeaderData(8,Qt::Horizontal,QObject::tr("niveau"));
           model->insertColumn(model->columnCount());
           model->insertColumn(model->columnCount());
           model->setHeaderData(9,Qt::Horizontal,QObject::tr(""));
           model->setHeaderData(10,Qt::Horizontal,QObject::tr(""));

           return model;
       } else {
           return nullptr;
       }
}

//stats
QSqlQueryModel* Event::getEventStatistics()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT type, COUNT(ID_EVENT) as event_count FROM EVENT GROUP BY type");

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("event_count"));
        return model;
    } else {
        qDebug() << "Error retrieving event statistics:" << query.lastError().text();
        return nullptr;
    }
}
QSqlQueryModel * Event::afficher_calendar(const QDate &selectedDate)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    QSqlQuery query;
    QString select = "select nom,age,lieu,dure,type,niveau from event where date_event like :date";
    query.prepare(select);
    query.bindValue(":date", selectedDate);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("age"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("lieu"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("dure"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("type"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("niveau"));
        return model;
    }else
        return nullptr;
}
void Event::highlightEventDates(QCalendarWidget *calendarWidget)
{
    QSqlQuery query;
    QString select = "SELECT DISTINCT date_event FROM event";
    query.prepare(select);
    if (query.exec()) {
        while (query.next()) {
            QDate date = query.value(0).toDate();
            QTextCharFormat format;
            QColor customColor(67, 127, 247); // Example RGB color (orange)
            format.setBackground(customColor);
            calendarWidget->setDateTextFormat(date, format);
        }
    } else {
        qDebug() << "Error fetching event dates:" << query.lastError().text();
    }

    // Disable date editing
    calendarWidget->setDateEditEnabled(false);
}

void Event::generatePoster(QLineEdit *IDEdit, QLineEdit *titleEdit, QDate dateEdit, QLineEdit *locationEdit, QLineEdit *typeEdit, QLineEdit *prixEdit, QLineEdit *ageEdit)
{
    // Retrieve information from UI elements
    QString ID = IDEdit->text();
    QString title = titleEdit->text();
    QString date = dateEdit.toString("yyyy-MM-dd"); // Convert the date to a string in the desired format
    QString location = locationEdit->text();
    QString description = typeEdit->text();
    QString prix = prixEdit->text() +" dt";
    QString age = ageEdit->text();

    // Concatenate all event information into a single string
        QString eventInfo =  title + "\n" + date + "\n" + location + "\n" + description + "\n" + prix + "\n" + age;


    // Generate QR Code based on the ID
    const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(eventInfo.toStdString().c_str(), qrcodegen::QrCode::Ecc::LOW);
    int qrSize = 128; // Define the size of the QR Code image (adjust as needed)

    // Convert QR Code to PNG image (or any other suitable format)
    QImage qrCodeImage = convertQRCodeToImage(qr, qrSize); // Assuming QR code size of 256x256 pixels

    // Create a QImage with dimensions 800x800 and fill it with a light background color
    QImage poster(1118, 720, QImage::Format_RGB32);
    poster.fill(QColor("#afe1e3")); // Fill with a light gray color


    // Create a painter to draw on the poster
    QPainter painter(&poster);
    painter.setRenderHint(QPainter::Antialiasing); // Enable antialiasing for smoother rendering


    // Draw background
    QRect backgroundRect(0, 0, poster.width(), poster.height());
    QPixmap backgroundImage("C:/Users/LENOVO/Documents/evenement/background.jpeg"); // Load your background image
    painter.drawPixmap(backgroundRect, backgroundImage);

    // Set up fonts
    QFont TitleFont("Arial", 32);
    QFont dateFont("Arial", 20, QFont::Bold);
    QFont lieuFont("Arial", 20);
    QFont prixFont("Arial",20);

    // Set up colors
    QColor textColor("blue");
    QColor accentColor("#FF5733");
    QColor shapeColor(253, 234, 183, 150); // Light yellow with transparency
    QColor prixColor(255, 255, 255, 100); // Blanc avec une opacité de 100

    // Draw shapes behind text elements
    painter.setBrush(Qt::transparent); // Set the brush color for shapes with alpha channel (transparency)
    painter.setPen(Qt::NoPen); // Disable outline for shapes

    // Draw shape behind title
    QRect TitleRect(450, 250, 200, 60); // Position and size of the ID rectangle
    painter.drawRect(TitleRect);

    // Draw shape behind date
    QRect dateRect(100, 655, 200, 40); // Position and size of the title rectangle
    painter.drawRect(dateRect);

    // Draw shape behind location
    QRect lieuRect(90, 580, 200, 50); // Position and size of the info rectangle
    painter.drawRect(lieuRect);

    // Draw shape behind prix
    QRect prixRect(120, 510, 100, 50); // Position and size of the description rectangle
    painter.drawRect(prixRect);

    // Set up text alignment
    painter.setPen(textColor); // Use accent color for the title text

    // Draw title text
    painter.setFont(TitleFont);
    painter.drawText(TitleRect, Qt::AlignCenter, title);

    // Draw date text
    painter.setFont(dateFont);
    painter.drawText(dateRect, Qt::AlignCenter, date);

    // Draw location text
    painter.setFont(lieuFont);
    painter.drawText(lieuRect, Qt::AlignCenter, lieu);

    // Draw prix text
    painter.setPen(prixColor);
    painter.setFont(prixFont);
    painter.drawText(prixRect, Qt::AlignCenter, prix);
    //QRectF descTextRect(60, 330, 680, 220); // Adjusted position for multiline description text

    painter.drawImage(QRect(950, 580, qrSize, qrSize), qrCodeImage); // Adjust position and size as needed

    // End painting
    painter.end();

    // Define the common part of the directory path
    QString commonPath = "C:/Users/LENOVO/Pictures/Desktop/finalprojet/2a19-smart-nautical-sports-club/users/";

    // Define the specific directory within the common path
    QString directoryName = "events/";

    // Construct the full directory path
    QString directoryPath = commonPath + directoryName;

    // Ensure the directory exists; if not, create it
    QDir directory(directoryPath);
    if (!directory.exists()) {
        if (!directory.mkpath(directoryPath)) {
            QMessageBox::warning(nullptr, QObject::tr("Error"), QObject::tr("Failed to create directory."));
            return; // Exit the function or handle the error as necessary
        }
    }

    // Construct the file path within the specified directory
    QString filePath = directoryPath + title + ".png";

    // Save the QImage to the file path
    if (!poster.save(filePath)) {
        QMessageBox::warning(nullptr, QObject::tr("Error"), QObject::tr("Failed to save the poster image to %1").arg(filePath));
    } else {
        QMessageBox::information(nullptr, QObject::tr("Success"), QObject::tr("Poster saved to %1").arg(filePath));
    }




}


QImage Event::convertQRCodeToImage(const qrcodegen::QrCode &qrCode, int size)
{
    // Create a QImage with a suitable format
    QImage image(size, size, QImage::Format_RGB32);
    image.fill(Qt::white); // Fill the image with white background

    // Initialize QPainter to draw on the image
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing); // Enable antialiasing for smoother rendering

    // Set up colors
    QColor blackColor(Qt::black);

    // Calculate the size of each module (pixel) in the QR code
    int moduleSize = size / qrCode.getSize();

    // Loop through each module in the QR code matrix
    for (int y = 0; y < qrCode.getSize(); ++y)
    {
        for (int x = 0; x < qrCode.getSize(); ++x)
        {
            // Check if the current module is black (1) or white (0)
            if (qrCode.getModule(x, y))
            {
                // If the module is black, draw a black rectangle
                QRect rect(x * moduleSize, y * moduleSize, moduleSize, moduleSize);
                painter.fillRect(rect, blackColor);
            }
        }
    }

    // End painting
    painter.end();
    return image;
}
QVector<QString> levelEnum= {"beginner", "intermediate", "amateur", "professional"};

bool Event::UpdateAthlete(){
        qDebug()<<"updating athlete func";
       QSqlQuery query;
       query.prepare("SELECT * FROM sportifs WHERE id=:id");
       query.bindValue(":id", winner);
       query.exec();
       query.next();
       Sportif sp(query.value("id").toInt() ,
                  query.value("name").toString() ,
                  query.value("lastname").toString() ,
                  query.value("age").toInt(),
                  query.value("adress").toString(),
                   query.value("email").toString(),
                  query.value("phone").toString(),
                  query.value("lvl").toString(),
                  query.value("sport_type").toString()
                  );
       sp.setFrequency(query.value("frequency").toInt());

       int athleteLevelIndex = levelEnum.indexOf(sp.getNiveau());
      if ( athleteLevelIndex < levelEnum.indexOf(niveau) and sp.getFrequency()>=20){
          qDebug()<<"athlete needs upgrade";
          sp.setNiveau(levelEnum.value(athleteLevelIndex+1));
          bool res =sp.modifier(sp);
          if (res==true){
              QMessageBox::information(nullptr, "Level Upgrade", "Athlete : "+ sp.getNom()+" has been promoted to " + sp.getNiveau());
          }
           return res;
      }
      return false;
}
bool Event::modifier_done(){
    QSqlQuery query;
    query.prepare("update event set done=:done where id_event=:id");
    query.bindValue(":id",id);
    query.bindValue(":done",done);
    return query.exec();
}
