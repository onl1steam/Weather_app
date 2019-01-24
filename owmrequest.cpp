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

#include "requestinterface.h"
#include "owmrequest.h"

OWMRequest::OWMRequest(QObject* parent) : QObject(parent)
{
    // 2xx
    imageMap.insert("200", "389");
    imageMap.insert("201", "386");
    imageMap.insert("202", "389");
    imageMap.insert("210", "200");
    imageMap.insert("211", "200");
    imageMap.insert("212", "200");
    imageMap.insert("221", "200");
    imageMap.insert("230", "389");
    imageMap.insert("231", "389");
    imageMap.insert("232", "389");
    // 3xx
    imageMap.insert("300", "266");
    imageMap.insert("301", "266");
    imageMap.insert("302", "266");
    imageMap.insert("310", "266");
    imageMap.insert("311", "266");
    imageMap.insert("312", "266");
    imageMap.insert("313", "266");
    imageMap.insert("314", "266");
    imageMap.insert("321", "266");
    // 5xx
    imageMap.insert("500", "296");
    imageMap.insert("501", "296");
    imageMap.insert("502", "296");
    imageMap.insert("503", "296");
    imageMap.insert("504", "296");
    imageMap.insert("511", "296");
    imageMap.insert("520", "296");
    imageMap.insert("521", "296");
    imageMap.insert("522", "296");
    imageMap.insert("531", "296");
    // 6xx
    imageMap.insert("600", "179");
    imageMap.insert("601", "179");
    imageMap.insert("602", "179");
    imageMap.insert("611", "317");
    imageMap.insert("612", "317");
    imageMap.insert("615", "179");
    imageMap.insert("616", "179");
    imageMap.insert("620", "179");
    imageMap.insert("621", "179");
    imageMap.insert("622", "179");
    // 7xx
    imageMap.insert("701", "143");
    imageMap.insert("711", "143");
    imageMap.insert("721", "143");
    imageMap.insert("731", "143");
    imageMap.insert("741", "248");
    imageMap.insert("751", "143");
    imageMap.insert("761", "143");
    imageMap.insert("762", "143");
    imageMap.insert("771", "143");
    imageMap.insert("781", "143");
    // 8xx
    imageMap.insert("800", "113");
    imageMap.insert("801", "113");
    imageMap.insert("802", "113");
    imageMap.insert("803", "113");
    imageMap.insert("804", "122");
}

void OWMRequest::setCallback(std::function<void()> callback)
{
    func = callback;
}


void OWMRequest::makeRequest(QString city, AppModel* model)
{
    mod = model;
    mod->setCity(city);
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(mod->getOWMUrl())));
}

void OWMRequest::replyFinished(QNetworkReply* reply)
{
    // Парсинг
    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll(),&parseError);
    QJsonObject object = document.object();
    QString error = object["message"].toString();
    if (error == "city not found")
    {
        QMessageBox msgBox;
        msgBox.setText("Город не найден!");
        msgBox.exec();
        return;
    }
    // Город
    QJsonObject cityData = object["city"].toObject();
    mod->setCity(cityData["name"].toString() + ", " + cityData["country"].toString());
    // Основная информация
    QJsonArray data = object["list"].toArray();
    QJsonObject day1 = data[4].toObject();
    QJsonObject day2 = data[12].toObject();
    QJsonObject day3 = data[20].toObject();
    QJsonObject day4 = data[28].toObject();
    QJsonObject day5 = data[36].toObject();
    if(day5.isEmpty()) {
        day5 = data[32].toObject();
    }

    // Заполнение
    // 1 день
    mod[0].setDescription((day1["weather"].toArray()[0].toObject()["description"]).toString());
    mod[0].setTemperature(QString::number(int(day1["main"].toObject()["temp"].toDouble())) + "°");
    mod[0].setFeels_Like(QString::number(int(day1["main"].toObject()["temp_min"].toDouble())) + "°");
    mod[0].setHumidity(QString::number(day1["main"].toObject()["humidity"].toDouble()) + "%");
    mod[0].setPrecipitation("-");
    // Перевод скорости ветра
    mod[0].setWind(QString::number(day1["wind"].toObject()["speed"].toDouble()) + " м/с");
    // Перевод давления в атмосферы
    int pressure_val = int(day1["main"].toObject()["pressure"].toDouble() / 1.333);
    mod[0].setPressure(QString::number(pressure_val) + " мм рт.ст.");
    // 2 день
    mod[1].setDescription((day2["weather"].toArray()[0].toObject()["description"]).toString());
    mod[1].setTemperature(QString::number(int(day2["main"].toObject()["temp"].toDouble())) + "°");
    // 3 день
    mod[2].setDescription((day3["weather"].toArray()[0].toObject()["description"]).toString());
    mod[2].setTemperature(QString::number(int(day3["main"].toObject()["temp"].toDouble())) + "°");
    // 4 день
    mod[3].setDescription((day4["weather"].toArray()[0].toObject()["description"]).toString());
    mod[3].setTemperature(QString::number(int(day4["main"].toObject()["temp"].toDouble())) + "°");
    // 5 день
    mod[4].setDescription((day5["weather"].toArray()[0].toObject()["description"]).toString());
    mod[4].setTemperature(QString::number(int(day5["main"].toObject()["temp"].toDouble())) + "°");
    // Отдельное определение weatherCode
    QString code1 = QString::number(day1["weather"].toArray()[0].toObject()["id"].toDouble());
    QString code2 = QString::number(day2["weather"].toArray()[0].toObject()["id"].toDouble());
    QString code3 = QString::number(day3["weather"].toArray()[0].toObject()["id"].toDouble());
    QString code4 = QString::number(day4["weather"].toArray()[0].toObject()["id"].toDouble());
    QString code5 = QString::number(day5["weather"].toArray()[0].toObject()["id"].toDouble());
    mod[0].setWeatherCode(imageMap.value(code1));
    mod[1].setWeatherCode(imageMap.value(code2));
    mod[2].setWeatherCode(imageMap.value(code3));
    mod[3].setWeatherCode(imageMap.value(code4));
    mod[4].setWeatherCode(imageMap.value(code5));
    // Заполнение данных
   func();
}


