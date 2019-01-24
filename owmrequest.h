#ifndef OWMREQUEST_H
#define OWMREQUEST_H

#include <QString>
#include <QMainWindow>
#include <QLabel>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>

#include "requestinterface.h"
#include "appmodel.h"

class OWMRequest : public QObject, public IRequest
{
    Q_OBJECT
public:
    explicit OWMRequest(QObject *parent = nullptr);
    void makeRequest(QString city, AppModel* model);
    void setCallback(std::function<void()> callback);
public slots:
    void replyFinished(QNetworkReply* reply);
private:

    QHash<QString, QString> imageMap;
    std::function<void()> func = nullptr;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    AppModel* mod;
};

#endif // OWMREQUEST_H
