#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appmodel.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fav_menu = new Favourite;
    fav_menu->setCallback([this](QString city){
      updateRequest(city);
    });
    adjustLabels();
    setDayOfWeek();
    setImages();
}

void MainWindow::setDayOfWeek()
{
    // Определение текущего и следующих дней недели
    for(int i = 0; i < 5; i++) {
        QDate date = QDate().currentDate();
        QString str = date.addDays(i).toString("ddd");
        mod[i].setDayOfWeek(str);
    }
}

void MainWindow::updateRequest(QString city)
{
    makeRequest(city);
}

void MainWindow::adjustLabels()
{
    // Основные поля
    ui->main_temp->setGeometry(55-ui->main_temp->text().length() / 2, 220, 70, 70);
    ui->cityLabel->setGeometry(30-ui->cityLabel->text().length() / 2, 50, 450, 15);
    ui->main_description->setGeometry(30-ui->main_description->text().length() / 2, 75, 450, 15);
}

void MainWindow::setImages()
{
    QPixmap img = QPixmap(":/images/weather_icons/113.png");

    // Основные картинки
    img = QPixmap(":/images/weather_icons/barometer.png");
    ui->pressure_img->setPixmap(img.scaled(24,24,Qt::KeepAspectRatio));
    img = QPixmap(":/images/weather_icons/precipitation.png");
    ui->precipitation_img->setPixmap(img.scaled(24,24,Qt::KeepAspectRatio));
    img = QPixmap(":/images/weather_icons/feels_like.png");
    ui->feels_like_img->setPixmap(img.scaled(24,24,Qt::KeepAspectRatio));
    img = QPixmap(":/images/weather_icons/humidity.png");
    ui->humidity_img->setPixmap(img.scaled(24,24,Qt::KeepAspectRatio));
    img = QPixmap(":/images/weather_icons/wind.png");
    ui->wind_img->setPixmap(img.scaled(24,24,Qt::KeepAspectRatio));
    img = QPixmap(":/images/weather_icons/113.png");

    // Дневные картинки
    ui->day1_img->setPixmap(img.scaled(64,64,Qt::KeepAspectRatio));
    img = QPixmap(":/images/weather_icons/113.png");
    ui->day2_img->setPixmap(img.scaled(64,64,Qt::KeepAspectRatio));
    img = QPixmap(":/images/weather_icons/113.png");
    ui->day3_img->setPixmap(img.scaled(64,64,Qt::KeepAspectRatio));
    img = QPixmap(":/images/weather_icons/113.png");
    ui->day4_img->setPixmap(img.scaled(64,64,Qt::KeepAspectRatio));
}

void MainWindow::makeRequest(QString city)
{
    mod->setCity(city);
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(mod->getUrl())));
}

void MainWindow::replyFinished(QNetworkReply* reply)
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
    // Заполнение данных
    ui->cityLabel->setText(city);
    fav_menu->setCity(ui->cityLabel->text());
    setInfo();
}

void MainWindow::setInfo()
{
    QString url;
    QPixmap img;
    // Актуальная дата
    ui->main_temp->setText(mod[0].getTemperature());
    ui->main_description->setText(mod[0].getDescription());
    ui->wind_lbl->setText(mod[0].getWind());
    ui->humidity_lbl->setText(mod[0].getHumidity());
    ui->precipitation_lbl->setText(mod[0].getPrecipitation());
    ui->feels_like_lbl->setText(mod[0].getFeels_Like());
    ui->pressure_lbl->setText(mod[0].getPressure());
    url = ":/images/weather_icons/" + mod[0].getWeatherCode() + ".png";
    img = QPixmap(url);
    ui->actual_img->setPixmap(img.scaled(64,64,Qt::KeepAspectRatio));
    // 2 день
    ui->day1_temp->setText(mod[1].getTemperature());
    ui->day1_desc->setText(mod[1].getDescription());
    url = ":/images/weather_icons/" + mod[1].getWeatherCode() + ".png";
    img = QPixmap(url);
    ui->day1_img->setPixmap(img.scaled(64,64,Qt::KeepAspectRatio));
    // 3 день
    ui->day2_temp->setText(mod[2].getTemperature());
    ui->day2_desc->setText(mod[2].getDescription());
    url = ":/images/weather_icons/" + mod[2].getWeatherCode() + ".png";
    img = QPixmap(url);
    ui->day2_img->setPixmap(img.scaled(64,64,Qt::KeepAspectRatio));
    // 4 день
    ui->day3_temp->setText(mod[3].getTemperature());
    ui->day3_desc->setText(mod[3].getDescription());
    url = ":/images/weather_icons/" + mod[3].getWeatherCode() + ".png";
    img = QPixmap(url);
    ui->day3_img->setPixmap(img.scaled(64,64,Qt::KeepAspectRatio));
    // 5 день
    ui->day4_temp->setText(mod[4].getTemperature());
    ui->day4_desc->setText(mod[4].getDescription());
    url = ":/images/weather_icons/" + mod[4].getWeatherCode() + ".png";
    img = QPixmap(url);
    ui->day4_img->setPixmap(img.scaled(64,64,Qt::KeepAspectRatio));
    adjustLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_request_btn_clicked()
{
    makeRequest(ui->cityEdit->toPlainText());
}

void MainWindow::on_repeat_btn_clicked()
{
    makeRequest(mod->getCity());
}


void MainWindow::on_pushButton_clicked()
{
    fav_menu->show();
    fav_menu->setCity(ui->cityLabel->text());
}
