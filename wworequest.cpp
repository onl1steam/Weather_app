#include <QString>
#include <QMainWindow>
#include <QLabel>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

#include "wworequest.h"
#include "requestinterface.h"

WWORequest::WWORequest(QObject* parent) : QObject(parent)
{

}

void WWORequest::setCallback(std::function<void()> callback)
{
    func = callback;
}


void WWORequest::makeRequest(QString city, AppModel* model)
{
    mod = model;
    mod->setCity(city);
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(mod->getWWOUrl())));
}

void WWORequest::replyFinished(QNetworkReply* reply)
{
    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll(),&parseError);
    QJsonObject object = document.object();
    QString error = object["data"].toObject()["error"].toArray().at(0)["msg"].toString();
    if (error != "")
    {
        QMessageBox msgBox;
        msgBox.setText("Город не найден!");
        msgBox.exec();
        return;
    }
    QJsonObject data = object["data"].toObject();
    // Распределение данных
    QJsonArray request = data["request"].toArray();
    QJsonValue day1 = data["weather"].toArray().at(0)["hourly"].toArray().at(0);
    QJsonValue day2 = data["weather"].toArray().at(1)["hourly"].toArray().at(0);
    QJsonValue day3 = data["weather"].toArray().at(2)["hourly"].toArray().at(0);
    QJsonValue day4 = data["weather"].toArray().at(3)["hourly"].toArray().at(0);
    QJsonValue day5 = data["weather"].toArray().at(4)["hourly"].toArray().at(0);
    // 1 день
    mod[0].setDescription(day1["lang_ru"].toArray().at(0)["value"].toString());
    mod[0].setTemperature(day1["tempC"].toString() + "°");
    mod[0].setWeatherCode(day1["weatherCode"].toString());
    mod[0].setFeels_Like(day1["FeelsLikeC"].toString() + "°");
    mod[0].setHumidity(day1["humidity"].toString() + "%");
    mod[0].setWind(day1["windspeedKmph"].toString() + " км/ч");
    mod[0].setPrecipitation(day1["precipMM"].toString() + " мм");
    // Перевод давления в атмосферы
    int pressure_val = int(day1["pressure"].toString().toDouble() / 1.333);
    mod[0].setPressure(QString::number(pressure_val) + " мм рт.ст.");
    // 2 день
    mod[1].setDescription(day2["lang_ru"].toArray().at(0)["value"].toString());
    mod[1].setTemperature(day2["tempC"].toString() + "°");
    mod[1].setWeatherCode(day2["weatherCode"].toString());
    // 3 день
    mod[2].setDescription(day3["lang_ru"].toArray().at(0)["value"].toString());
    mod[2].setTemperature(day3["tempC"].toString() + "°");
    mod[2].setWeatherCode(day3["weatherCode"].toString());
    // 4 день
    mod[3].setDescription(day4["lang_ru"].toArray().at(0)["value"].toString());
    mod[3].setTemperature(day4["tempC"].toString() + "°");
    mod[3].setWeatherCode(day4["weatherCode"].toString());
    // 5 день
    mod[4].setDescription(day5["lang_ru"].toArray().at(0)["value"].toString());
    mod[4].setTemperature(day5["tempC"].toString() + "°");
    mod[4].setWeatherCode(day5["weatherCode"].toString());
    // Город
    QString city = request.at(0)["query"].toString();
    mod->setCity(city);
    // Заполнение данных
   func();
}

