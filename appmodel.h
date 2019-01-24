#ifndef APPMODEL_H
#define APPMODEL_H

#include "QString"
#include <QtNetwork/QNetworkAccessManager>

class AppModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString pressure READ getPressure WRITE setPressure)
    Q_PROPERTY(QString precipitation READ getPrecipitation WRITE setPrecipitation)
    Q_PROPERTY(QString weatherCode READ getWeatherCode WRITE setWeatherCode)
    Q_PROPERTY(QString dayOfWeek READ getDayOfWeek WRITE setDayOfWeek)
    Q_PROPERTY(QString temperature READ getTemperature WRITE setTemperature)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription)
    Q_PROPERTY(QString humidity READ getHumidity WRITE setHumidity)
    Q_PROPERTY(QString wind READ getWind WRITE setWind)
    Q_PROPERTY(QString feels_like READ getFeels_Like WRITE setFeels_Like)
    Q_PROPERTY(QString city READ getCity WRITE setCity)
    Q_PROPERTY(QString wwoUrl READ getWWOUrl)
    Q_PROPERTY(QString owmUrl READ getOWMUrl)
public:
    AppModel() = default;

    QString getOWMUrl();
    QString getWWOUrl();

    // setters
    void setPressure(const QString &value);
    void setPrecipitation(const QString &value);
    void setWeatherCode(const QString &value);
    void setDayOfWeek(const QString &value);
    void setTemperature(const QString &value);
    void setDescription(const QString &value);
    void setHumidity(const QString &value);
    void setWind(const QString &value);
    void setFeels_Like(const QString &value);
    void setCity(const QString &value);

    // getters
    QString getPressure();
    QString getPrecipitation();
    QString getWeatherCode();
    QString getDayOfWeek();
    QString getTemperature();
    QString getDescription();
    QString getHumidity();
    QString getWind();
    QString getFeels_Like();
    QString getCity();

private:

    QString pressure;
    QString precipitation;
    QString weatherCode;
    QString dayOfWeek;
    QString temperature;
    QString description;
    QString humidity;
    QString wind;
    QString feels_like;
    QString city;
    QString owmUrl;
    QString wwoUrl;
};

#endif // APPMODEL_H
