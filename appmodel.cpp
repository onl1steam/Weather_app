#include "appmodel.h"
#include "QDate"
#include "QDebug"
#include "QString"

QString AppModel::getUrl()
{
    url = "http://api.worldweatheronline.com/premium/v1/weather.ashx?key=cebcb30c79bb4211936200546180112&tp=24&num_of_days=5&format=json&lang=ru&q=" + city;
    return url;
}

// setters

void AppModel::setCity(const QString &value)
{
    city = value;
}

void AppModel::setDayOfWeek(const QString &value)
{
    dayOfWeek = value;
}

void AppModel::setDescription(const QString &value)
{
    description = value;
}

void AppModel::setFeels_Like(const QString &value)
{
    feels_like = value;
}

void AppModel::setHumidity(const QString &value)
{
    humidity = value;
}

void AppModel::setPrecipitation(const QString &value)
{
    precipitation = value;
}

void AppModel::setPressure(const QString &value)
{
    pressure = value;
}

void AppModel::setTemperature(const QString &value)
{
    temperature = value;
}

void AppModel::setWeatherCode(const QString &value)
{
    weatherCode = value;
}

void AppModel::setWind(const QString &value)
{
    wind = value;
}


// getters

QString AppModel::getDayOfWeek()
{
    return dayOfWeek;
}

QString AppModel::getCity()
{
    return city;
}

QString AppModel::getDescription()
{
    return description;
}

QString AppModel::getFeels_Like()
{
    return feels_like;
}

QString AppModel::getHumidity()
{
    return humidity;
}

QString AppModel::getPrecipitation()
{
    return precipitation;
}

QString AppModel::getPressure()
{
    return pressure;
}

QString AppModel::getTemperature()
{
    return temperature;
}

QString AppModel::getWeatherCode()
{
    return weatherCode;
}

QString AppModel::getWind()
{
    return wind;
}











