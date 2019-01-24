#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

void Settings::getBoolean(bool* wwo, bool* owm)
{
    this->wwo = wwo;
    this->owm = owm;
    if(*wwo) {
    ui->variant1->setChecked(true);
    } else {
    ui->variant2->setChecked(true);
    }
}

void Settings::saveToFile()
{
    QString str;
    QByteArray ba;
    char *c_str;
    QFile file("Find_method.txt");
    QString method;
    if(*wwo) {
        method = "wwo";
    } else {
        method = "owm";
    }
    if (!file.open(QIODevice::WriteOnly)){
            qDebug() << "can't open list";
    }else{
        ba = method.toLocal8Bit();
        c_str = ba.data();
        file.write(c_str);
        file.close();
    }
}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_variant1_clicked()
{
    *wwo = true;
    *owm = false;
    saveToFile();
}

void Settings::on_variant2_clicked()
{
    *owm = true;
    *wwo = false;
    saveToFile();
}
