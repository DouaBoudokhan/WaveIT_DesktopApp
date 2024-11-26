#include "openweathermapforecast.h"

OpenWeatherMapForecast::OpenWeatherMapForecast(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &OpenWeatherMapForecast::onNetworkReplyFinished);
}

void OpenWeatherMapForecast::updateForecasts(QString appId, QString location, quint8 maxForecasts)
{
    this->maxForecasts = maxForecasts;
    QString path = buildPath(appId, "q=" + location);
    QUrl url(path);
    QNetworkRequest request(url);
    manager->get(request);
}




void OpenWeatherMapForecast::updateForecastsById(QString appId, QString locationId, quint8 maxForecasts)
{
    this->maxForecasts = maxForecasts;
    QString path = buildPath(appId, "id=" + locationId);
    QUrl url(path);
    QNetworkRequest request(url);
    manager->get(request);
}


void OpenWeatherMapForecast::onNetworkReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        parseJson(data);
    } else {
        emit errorOccurred(reply->errorString());
    }
    reply->deleteLater();
}

QString OpenWeatherMapForecast::buildPath(QString appId, QString locationParameter)
{
    QString units = "metric"; // or "imperial" for Fahrenheit
    QString language = "en"; // Language code, e.g., "en" for English
    return QStringLiteral("https://api.openweathermap.org/data/2.5/forecast?") +
           locationParameter + "&appid=" + appId + "&units=" + units + "&lang=" + language;
}

void OpenWeatherMapForecast::parseJson(QByteArray jsonData)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        emit errorOccurred("Invalid JSON data");
        return;
    }

    QJsonArray forecastsArray = doc.array();
    if (forecastsArray.size() == 0) {
        emit errorOccurred("No forecast data available");
        return;
    }
    emit forecastsUpdated(forecastsArray);
}
