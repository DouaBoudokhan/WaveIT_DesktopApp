#ifndef USER_H
#define USER_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>
#include<QToolTip>
#include<QMessageBox>
#include<QPainter>
#include <QDesktopServices>
#include <QPdfWriter>
#include <QUrl>
#include <QPushButton>
#include <QString>

#include<QMainWindow>


class user
{
private:
    int idu;
    QString first_name, last_name, position, email, pw, username,cin,phone;
    QDate bdate;

public:
    // Constructeurs
    user(){};
    user( QString, QString, QString, QString, QString, QString, QString, QString, QDate);
    //crud
    bool add();
    QSqlQueryModel* display();
    bool update();
    bool del(int id);
    bool findUser(int id);
    bool unique(const QString& username);
    //metiers
    QSqlQueryModel* search(const QString& searchTerm);
    QMap<QString, double> getStatsByPositionPercentage();
    bool exportToPdf(const QString& filePath);
    QSqlQueryModel* TrieParPrenom();
    int login(QString username, QString password);
    QString pos(QString username, QString password);
    // Getters
    int getIdu() const {
        return idu;
    }
    QString getFirstName() const {
        return first_name;
    }
    QString getLastName() const {
        return last_name;
    }
    QString getPosition() const {
        return position;
    }
    QString getEmail() const {
        return email;
    }
    QString getPw() const {
        return pw;
    }
    QString getUsername() const {
        return username;
    }
    QString getCin() const {
        return cin;
    }
    QString getPhone() const {
        return phone; }
    QDate getBDate() const {
        return bdate; }

    // Setters
    void setIdu(int id) {
        idu = id;
    }
    void setFirstName(const QString& firstName) {
        first_name = firstName;
    }
    void setLastName(const QString& lastName) {
        last_name = lastName;
    }
    void setPosition(const QString& pos) {
        position = pos;
    }
    void setEmail(const QString& emailAddr) {
        email = emailAddr;
    }
    void setPw(const QString& password) {
        pw = password;
    }
    void setUsername(const QString& uname) {
        username = uname;
    }
    void setCin(const QString& cinnum) {
        cin = cinnum; }
    void setPhone(const QString& phoneNumber) {
        phone = phoneNumber;
                                   }
    void setBDate(const QDate& birthDate) {
        bdate = birthDate;
    }
};


#endif // USER_H
