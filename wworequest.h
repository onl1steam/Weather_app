#ifndef WWOREQUEST_H
#define WWOREQUEST_H

#include <QString>
#include <QMainWindow>
#include <QLabel>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>

#include "requestinterface.h"
#include "appmodel.h"

/**
 * @brief The WWORequest class - class used for
 * requests to the server worldweatheronline.com
 */
class WWORequest : public QObject, public IRequest
{
    Q_OBJECT
public:
    explicit WWORequest(QObject *parent = nullptr);
    /**
     * @brief makeRequest - make request to the server
     * Takes city and instance of AppModel as parameters
     */
    void makeRequest(QString city, AppModel* model);
    /**
     * @brief setCallback - set callback to interact with MainWindow class
     * Takes lambda expression as parameters
     */
    void setCallback(std::function<void()> callback);
public slots:
    /**
     * @brief replyFinished - processes the JSON file
     * and distributes the data to AppModel instance
     * Takes reply after request as parameters
     */
    void replyFinished(QNetworkReply* reply);
private:
    /**
     * @brief func - lamda expression for callback
     */
    std::function<void()> func = nullptr;
    /**
     * @brief manager - instance of QNetworkAccessManager
     * Used to make requests
     */
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    /**
     * @brief mod - contains instance
     * given from MainWindow class
     */
    AppModel* mod;
};

#endif // WWOREQUEST_H
