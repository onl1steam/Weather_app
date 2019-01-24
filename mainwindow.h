#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>

#include "appmodel.h"
#include "favourites.h"
#include "wworequest.h"
#include "owmrequest.h"
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setInfo();
    void setDayOfWeek();
    void WRequest(QString city);
    void ORequest(QString city);
    void adjustLabels();
    void setImages();

    void makeRequest(QString city);

    void updateRequest(QString city);

private slots:
    void on_request_btn_clicked();
    void on_repeat_btn_clicked();

    void on_favouriteButton_clicked();

    void on_settingsButton_clicked();

private:

    bool isWWO;
    bool isOWM;
    OWMRequest* owmRequest = new OWMRequest();
    WWORequest* wwoRequest = new WWORequest();
    Favourite *fav_menu;
    AppModel* mod = new AppModel[5];
    Settings* settings_menu;
    Ui::MainWindow *ui;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
};

#endif // MAINWINDOW_H
