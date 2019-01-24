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

class IRequest
{
public:
    virtual ~IRequest(){}
    virtual void makeRequest(QString city, AppModel* model) = 0;
public slots:
     virtual void replyFinished(QNetworkReply* reply) = 0;
};

#endif // IREQUEST_H
