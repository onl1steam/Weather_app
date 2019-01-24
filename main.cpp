#include <QApplication>

#include "mainwindow.h"
#include "favourites.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.makeRequest("Москва, Россия");
    w.show();
    return a.exec();
}


