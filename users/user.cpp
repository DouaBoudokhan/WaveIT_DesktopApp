#include "user.h"
#include <QPushButton>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QDate>
#include <QRegularExpression>
#include <QSqlError>
#include <QObject>
#include "user.h"
#include <QPushButton>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QDate>
#include <QRegularExpression>
#include <QSqlError>
#include <QObject>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QTextFrame>
#include <QtCharts>
#include <QPrinter>




user::user(QString first_name, QString last_name, QString email, QString username, QString pw, QString position, QString cin, QString phone, QDate bdate)
{
    this->first_name = first_name;
    this->last_name = last_name;
    this->username = username;
    this->bdate = bdate;
    this->email = email;
    this->pw = pw;
    this->position = position;
    this->cin = cin;
    this->phone = phone;
}

bool user::add() {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, position, cin, phone, bdate, first_name, last_name, email, pw) "
                  "VALUES (:username, :position, :cin, :phone, :bdate, :first_name, :last_name, :email, :pw)");
    query.bindValue(":username", username);
    query.bindValue(":position", position);
    query.bindValue(":cin", cin);
    query.bindValue(":phone", phone);
    query.bindValue(":bdate", bdate);
    query.bindValue(":first_name", first_name);
    query.bindValue(":last_name", last_name);
    query.bindValue(":email", email);
    query.bindValue(":pw", pw);

    return query.exec();
}

QSqlQueryModel* user::display() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT idu, first_name, last_name, position, email, pw, username, cin, phone, bdate FROM users");

    if (model->lastError().isValid()) {
        qDebug() << "Query Error:" << model->lastError().text();
    } else {
        qDebug() << "Query Executed Successfully!";
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDU"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Position"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Password"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Username"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Phone"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Birth Date"));

    return model;
}





bool user::del(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE idu = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            qDebug() << "User with ID" << id << "deleted successfully!";
            return true;
        } else {
            qDebug() << "User with ID" << id << "not found.";
            return false;
        }
    } else {
        qDebug() << "Error deleting user with ID" << id << ":" << query.lastError().text();
        return false;
    }
}

bool user::update()
{
    QSqlQuery query;
    query.prepare("UPDATE users SET first_name=:fn, last_name=:ln, email=:email, pw=:pw, position=:pos, cin=:cin, phone=:phone, username=:username, bdate=:bdate WHERE idu=:idu");
    query.bindValue(":fn", first_name);
    query.bindValue(":ln", last_name);
    query.bindValue(":email", email);
    query.bindValue(":pw", pw);
    query.bindValue(":pos", position);
    query.bindValue(":cin", cin);
    query.bindValue(":phone", phone);
    query.bindValue(":idu", idu);
    query.bindValue(":username", username);
    query.bindValue(":bdate", bdate);

    return query.exec();
}

bool user::findUser(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE idu = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // Fetch user data from the query result
        idu = query.value("idu").toInt();
        first_name = query.value("first_name").toString();
        last_name = query.value("last_name").toString();
        position = query.value("position").toString();
        email = query.value("email").toString();
        pw = query.value("pw").toString();
        username = query.value("username").toString();
        cin = query.value("cin").toString();
        phone = query.value("phone").toString();
        bdate = query.value("bdate").toDate();

        qDebug() << "User found with ID:" << idu << "Name:" << first_name << last_name;
        return true;
    } else {
        qDebug() << "Error finding user with ID" << id << ":" << query.lastError().text();
        return false;
    }
}

bool user::unique(const QString& username) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);
    if (!query.exec()) {
        qDebug() << "Database query failed:" << query.lastError().text();
        return false;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        return false;
    }

    return true;
}
QSqlQueryModel* user::search(const QString& searchTerm) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
   QString queryString = "SELECT idu, first_name, last_name, position, email, pw, username, cin, phone, bdate FROM users WHERE ";
    queryString += "first_name LIKE :searchTerm OR ";
    queryString += "last_name LIKE :searchTerm OR ";
    queryString += "username LIKE :searchTerm";

    query.prepare(queryString);
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    if (!query.exec()) {
        qDebug() << "Query Error:" << query.lastError().text();
    } else {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDU"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Position"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Password"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Username"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Phone"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("Birth Date"));
    }

    return model;
}
QMap<QString, double> user::getStatsByPositionPercentage() {
    QMap<QString, double> stats;
    QSqlQuery query;
    query.exec("SELECT position, COUNT(*) FROM users GROUP BY position");
    int totalUsers = 0;
    while (query.next()) {
        QString position = query.value(0).toString();
        int count = query.value(1).toInt();
        stats[position] = count;
        totalUsers += count;
    }
    // Convert user counts to percentages
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        it.value() = (it.value() / totalUsers) * 100.0;
    }
    return stats;
}
bool user::exportToPdf(const QString& filePath) {
    QSqlQueryModel* model = display();

    if (!model) {
        return false;
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(filePath);

    QTextDocument doc;

    QTextCursor cursor(&doc);
    cursor.movePosition(QTextCursor::Start);

    QTextTable* table = cursor.insertTable(model->rowCount() + 1, model->columnCount());
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignHCenter);
    table->setFormat(tableFormat);

    for (int col = 0; col < model->columnCount(); ++col) {
        table->cellAt(0, col).firstCursorPosition().insertText(model->headerData(col, Qt::Horizontal).toString());
    }
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            table->cellAt(row + 1, col).firstCursorPosition().insertText(model->data(model->index(row, col)).toString());
        }
    }
    doc.print(&printer);

    return true;
}
QSqlQueryModel* user::TrieParPrenom() {
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT idu, first_name, last_name, position, email, pw, username, cin, phone, bdate "
                    "FROM users "
                    "ORDER BY first_name");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDU"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Position"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Password"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Username"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Phone"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Birth Date"));

    return model;
}
int user::login(QString username, QString password)
{
    QSqlQuery query;
    query.prepare("SELECT idu FROM users WHERE username = :username AND pw = :password ");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec() && query.next())
        return query.value("idu").toInt();

    else {
       return -1;
    }
}
QString user::pos(QString username, QString password)
{
    QSqlQuery query;
    query.prepare("SELECT position FROM users WHERE username = :username AND pw = :password ");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec() && query.next())
        return query.value("position").toString(); // Return pos as a QString

    else {
       return QString(); // Return an empty QString if no position found
    }
}

