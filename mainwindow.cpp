#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QComboBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // favourite
    fav_menu = new Favourite;
    fav_menu->setCallback([this](QString city){
      updateRequest(city);
    });
    // settings
    settings_menu = new Settings;
    settings_menu->getBoolean(&isWWO, &isOWM);
    // worldweatheronline
    wwoRequest->setCallback([this](){
        setInfo();
      });
    // openweathermap
    owmRequest->setCallback([this](){
        setInfo();
      });
    // detect which method use
    QFile file("Find_method.txt");
    QString str;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "can't open list";
            str = "";
    }else{
        str = file.readLine();
     }
    file.close();
    if(str == "") {
        str = "wwo";
    isWWO = true;
    isOWM = false;
    } else {
        if(str == "wwo") {
    isWWO = true;
    isOWM = false;
         } else {
    isWWO = false;
    isOWM = true;
    }
    }
    // adjust labels
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
    ui->day1->setText(mod[1].getDayOfWeek());
    ui->day2->setText(mod[2].getDayOfWeek());
    ui->day3->setText(mod[3].getDayOfWeek());
    ui->day4->setText(mod[4].getDayOfWeek());
    ui->dateLabel->setText(QDate().currentDate().toString("dd MMMM yyyy, ddd"));
}

void MainWindow::updateRequest(QString city)
{
    makeRequest(ui->cityEdit->toPlainText());
}

void MainWindow::adjustLabels()
{
    ui->day1_desc->setAlignment(Qt::AlignCenter);
    ui->day2_desc->setAlignment(Qt::AlignCenter);
    ui->day3_desc->setAlignment(Qt::AlignCenter);
    ui->day4_desc->setAlignment(Qt::AlignCenter);
    // Основные поля
    ui->main_temp->setGeometry(55 - ui->main_temp->text().length() / 2, 220, 70, 70);
    ui->cityLabel->setGeometry(30 - ui->cityLabel->text().length() / 2, 50, 450, 15);
    ui->dateLabel->setGeometry(200 - ui->dateLabel->text().length() / 2, 75, 450, 15);
    ui->main_description->setGeometry(30 - ui->main_description->text().length() / 2, 100, 450, 15);
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

void MainWindow::WRequest(QString city)
{
    wwoRequest->makeRequest(city, mod);
}

void MainWindow::ORequest(QString city)
{
    owmRequest->makeRequest(city, mod);
}

void MainWindow::makeRequest(QString city)
{
    if(isWWO) {
        WRequest(city);
    } else {
        ORequest(city);
    }
}

void MainWindow::setInfo()
{
    ui->cityLabel->setText(mod->getCity());
    fav_menu->setCity(ui->cityLabel->text());
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
    makeRequest(ui->cityEdit->toPlainText());
}

void MainWindow::on_favouriteButton_clicked()
{
    fav_menu->show();
    fav_menu->setCity(ui->cityLabel->text());
}

void MainWindow::on_settingsButton_clicked()
{
    settings_menu->show();
}
