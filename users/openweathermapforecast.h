#ifndef OPENWEATHERMAPFORECAST_H
#define OPENWEATHERMAPFORECAST_H

#include <QObject>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class OpenWeatherMapForecast : public QObject
{
    Q_OBJECT

public:
    OpenWeatherMapForecast(QObject *parent = nullptr);

    void updateForecasts(QString appId, QString location, quint8 maxForecasts);
    void updateForecastsById(QString appId, QString locationId, quint8 maxForecasts);

signals:
    void forecastsUpdated(QJsonArray data);
    void errorOccurred(QString errorString);

private slots:
    void onNetworkReplyFinished(QNetworkReply *reply);

private:
    QString buildPath(QString appId, QString locationParameter);
    void parseJson(QByteArray jsonData);

    QNetworkAccessManager *manager;
    quint8 maxForecasts;
};

#endif // OPENWEATHERMAPFORECAST_H
