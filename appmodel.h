#ifndef APPMODEL_H
#define APPMODEL_H

#include "QString"
#include <QtNetwork/QNetworkAccessManager>

/**
 * @brief The AppModel class - class that
 * hold all information needed to provide
 * on screen. Contains information and
 * properies to get and set them
 */
class AppModel : public QObject
{
    Q_OBJECT
    /**
     * @brief pressure - property that provides
     * and changes information about pressure
     */
    Q_PROPERTY(QString pressure READ getPressure WRITE setPressure)
    /**
     * @brief precipitation - property that provides
     * and changes information about precipitation
     */
    Q_PROPERTY(QString precipitation READ getPrecipitation WRITE setPrecipitation)
    /**
     * @brief weatherCode - property that provides
     * and changes information about image that
     * displays needed wheather
     */
    Q_PROPERTY(QString weatherCode READ getWeatherCode WRITE setWeatherCode)
    /**
     * @brief dayOfWeek - property that provides
     * and changes information about day of the week
     */
    Q_PROPERTY(QString dayOfWeek READ getDayOfWeek WRITE setDayOfWeek)
    /**
     * @brief temperature - property that provides
     * and changes information about temperature
     */
    Q_PROPERTY(QString temperature READ getTemperature WRITE setTemperature)
    /**
     * @brief description - property that provides
     * and changes information about weather description
     */
    Q_PROPERTY(QString description READ getDescription WRITE setDescription)
    /**
     * @brief humidity - property that provides
     * and changes information about humidity
     */
    Q_PROPERTY(QString humidity READ getHumidity WRITE setHumidity)
    /**
     * @brief wind - property that provides
     * and changes information about wind speed
     */
    Q_PROPERTY(QString wind READ getWind WRITE setWind)
    /**
     * @brief feels_like - property that provides
     * and changes information about perceived temperature
     */
    Q_PROPERTY(QString feels_like READ getFeels_Like WRITE setFeels_Like)
    /**
     * @brief city - property that provides
     * and changes information about city
     */
    Q_PROPERTY(QString city READ getCity WRITE setCity)
    /**
     * @brief wwoUrl - property that provides
     * url adress of worldweatheronline server
     */
    Q_PROPERTY(QString wwoUrl READ getWWOUrl)
    /**
     * @brief owmUrl - property that provides
     * url adress of openweathermap server
     */
    Q_PROPERTY(QString owmUrl READ getOWMUrl)
public:
    AppModel() = default;

    /**
     * @brief setters of properties
     */
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

    /**
     * @brief getters of properties
     */
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
    QString getOWMUrl();
    QString getWWOUrl();

private:

    /**
     * @brief variables that holds the infrormation
     * used in properties
     */
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
