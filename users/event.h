#ifndef EVENT_H
#define EVENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include <QMessageBox>
#include <QTextDocument>
#include <QTextCursor>
#include <QSqlRecord>
#include <QPrinter>
#include <QStandardPaths>
#include <QDebug>
#include <QPdfWriter>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QCheckBox>
#include <QDebug>
#include <QLabel>
#include <QCalendarWidget>
#include <QFileDialog>
#include <QDir>
#include <QPainter>
#include <QTranslator>
#include <QCoreApplication>
#include <QObject>
#include <QLineEdit>
#include "qrcode.h"

#include "sportif.h"
QT_CHARTS_USE_NAMESPACE
class Event
{
private:
    QString nom,lieu,type,niveau;
    int id,age,dure,prix,done,winner;
    QDate date;

public:
    Event();
    Event(int,QString,int,QString,QDate,int,QString,QString,int);
    //getters
    QString get_nom() { return nom; }
    QString get_lieu() { return lieu; }
    QString get_type() { return type; }
    QString get_niveau() { return niveau; }

    int get_id() { return id; }
    int get_age() { return age; }
    int get_dure() { return dure; }
    int get_prix() { return prix; }
    QDate get_date() { return date; }
    //setters
    void set_nom(QString n){nom=n;}
    void set_lieu(QString l){lieu=l;}
    void set_type(QString t){type=t;}
    void set_niveau(QString ni){niveau=ni;}
    void set_id(int id){this->id=id;}
    void set_age(int age){this->age=age;}
    void set_dure(int dure){this->dure=dure;}
    void set_winner(int winner){this->winner=winner;}
    void set_done(int done){this->done=done;}
    void set_prix(int prix){this->prix=prix;}
    void set_date(QDate d){this->date=d;}
    //fonctionalites
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool supprimer_all();
    bool modifier(int,QString,int,QString,QDate,int,QString,QString,int);

    Event getEventById(int id);

    bool checkIfIdExists(int id);
    bool idIsValid(int id);

    bool exportToPdf();
    QSqlQueryModel *search(const QString &criteria);
    QSqlQueryModel *sort(const QString &criteria);

    //stats

    void choix_bar(QLabel *);
    void choix_pie();
    void handleCheckboxes();
    //metiers avances
    QSqlQueryModel * afficher_calendar(const QDate &selectedDate );
    void highlightEventDates(QCalendarWidget *calendarWidget);
    QSqlQueryModel* getEventStatistics();
    //poster
    QImage convertQRCodeToImage(const qrcodegen::QrCode &qrCode, int size);
    void generatePoster(QLineEdit *,QLineEdit *,QDate ,QLineEdit *,QLineEdit *,QLineEdit *,QLineEdit *);

    bool UpdateAthlete();
    bool modifier_done();

};

#endif // EVENT_H
