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
    void makeRequest(QString city);
    void adjustLabels();
    void setImages();

    void updateRequest(QString city);

public slots:
    void replyFinished(QNetworkReply* reply);

private slots:
    void on_request_btn_clicked();
    void on_repeat_btn_clicked();

    void on_pushButton_clicked();

private:

    Favourite *fav_menu;
    AppModel mod[5];
    Ui::MainWindow *ui;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
};

#endif // MAINWINDOW_H
