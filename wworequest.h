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


class WWORequest : public QObject, public IRequest
{
    Q_OBJECT
public:
    explicit WWORequest(QObject *parent = nullptr);
    void makeRequest(QString city, AppModel* model);
    void setCallback(std::function<void()> callback);
public slots:
    void replyFinished(QNetworkReply* reply);
private:
    std::function<void()> func = nullptr;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    AppModel* mod;
};

#endif // WWOREQUEST_H
