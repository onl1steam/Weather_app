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

/**
 * @brief The MainWindow class - class with UI,
 * which manages main program interface
 * Interact with users
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief setInfo - distributes information on the screen
     * Puts information in AppModel instance
     */
    void setInfo();
    /**
     * @brief setDayOfWeek - computes day of week
     * and 4 following days after today
     * Puts information in AppModel instance
     */
    void setDayOfWeek();
    /**
     * @brief WRequest - make request
     * to worldweatheronline.com server
     * Takes city as parameter
     */
    void WRequest(QString city);
    /**
     * @brief ORequest - make request
     * to openweathermap.org server
     * Takes city as parameter
     */
    void ORequest(QString city);
    /**
     * @brief adjustLabels - adjust the labels on screen
     * after getting infromation from server
     * according their length
     */
    void adjustLabels();
    /**
     * @brief setImages - set weather appropriate
     * images to the screen
     */
    void setImages();
    /**
     * @brief makeRequest - decide which
     * server use for request
     * After that call request function
     * Takes city as parameter
     */
    void makeRequest(QString city);
    /**
     * @brief updateRequest - updates information
     * decide which server use for request
     * After that call request function
     * Takes city as parameter
     */
    void updateRequest(QString city);

private slots:
    /**
     * @brief on_request_btn_clicked - response to request button
     * Make a request after click
     */
    void on_request_btn_clicked();
    /**
     * @brief on_repeat_btn_clicked - response to repeat button
     * Make a request after click to the same city
     */
    void on_repeat_btn_clicked();
    /**
     * @brief on_favouriteButton_clicked - response to favourite button
     * Displays the window with favourite places
     */
    void on_favouriteButton_clicked();
    /**
     * @brief on_settingsButton_clicked - response to settings button
     * Displays the window with settings of the program
     */
    void on_settingsButton_clicked();
private:
    /**
     * @brief isWWO - holds boolean value
     * if worldweatheronline.com is choosen for requests
     */
    bool isWWO;
    /**
     * @brief isOWM - holds boolean value
     * if openweathermap.org is choosen for requests
     */
    bool isOWM;
    /**
     * @brief owmRequest - holds instance
     * of OWMRequst class
     */
    OWMRequest* owmRequest = new OWMRequest();
    /**
     * @brief wwoRequest - holds instance
     * of WWORequst class
     */
    WWORequest* wwoRequest = new WWORequest();
    /**
     * @brief fav_menu - holds instance
     * of Favourite class
     */
    Favourite *fav_menu;
    /**
     * @brief mod - holds array AppModel
     * instance, used for information storage
     */
    AppModel* mod = new AppModel[5];
    /**
     * @brief settings_menu - holds instance of
     * Settings class
     */
    Settings* settings_menu;
    /**
     * @brief ui - instance of UI
     * Manages all elements of UI
     */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
