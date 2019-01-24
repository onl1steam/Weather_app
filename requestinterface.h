#ifndef IREQUEST_H
#define IREQUEST_H

#include <QString>
#include <QMainWindow>
#include <QLabel>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>

#include "appmodel.h"

/**
 * @brief The IRequest class - abstract class used for
 * requests to inheritance of request classes
 */
class IRequest
{
public:
    virtual ~IRequest(){}
    /**
     * @brief makeRequest  - make request to the server
     * Takes city and instance of AppModel as parameters
     * Pure virtual function
     */
    virtual void makeRequest(QString city, AppModel* model) = 0;
public slots:
    /**
     * @brief replyFinished - processes the JSON file
     * and distributes the data to AppModel instance
     * Takes reply after request as parameters
     * Pure virtual function
     */
     virtual void replyFinished(QNetworkReply* reply) = 0;
};

#endif // IREQUEST_H
