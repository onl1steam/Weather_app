#include "favourites.h"
#include "ui_favourites.h"
#include "QFile"
#include <QJsonDocument>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include "mainwindow.h"

Favourite::Favourite(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Favourite)
{
    ui->setupUi(this);
    updateList();
}

void Favourite::setCallback(std::function<void(QString)> callback)
{
    func = callback;
}

void Favourite::updateList()
{
  QFile file("Favourite_List.txt");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
          qDebug() << "can't open list";
  }else{
           ui->listWidget->clear();
           while(!file.atEnd())
              {
                  QString str = file.readLine();
                  ui->listWidget->addItem(str);
              }
      }
  file.close();
}

Favourite::~Favourite()
{
    delete ui;
}

void Favourite::on_addButton_clicked()
{      
    QString str;
    QByteArray ba;
    char *c_str;
    QFile file("Favourite_List.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)){
            qDebug() << "can't open list";
    }else{
        if (file.pos() == 0) {
            ba = city.toLocal8Bit();
            c_str = ba.data();
            file.write(c_str);
            file.close();
        } else {
            ba = ("\n" + city).toLocal8Bit();
            c_str = ba.data();
            file.write(c_str);
            file.close();
        }
        }
    updateList();
}

void Favourite::setCity(QString value)
{
    city = value;
}

void Favourite::deleteFromList(const int index)
{
    if(index == ui->listWidget->count() - 1 && ui->listWidget->count() != 1) {
        QString string = ui->listWidget->item(index-1)->text();
        string.chop(1);
        ui->listWidget->item(index - 1)->setText(string);
    }
    ui->listWidget->removeItemWidget(ui->listWidget->takeItem(index));
    QFile file("Favourite_List.txt");
    QString str;
    QByteArray ba;
    char *c_str;
    if (!file.open(QIODevice::WriteOnly)){
            qDebug() << "can't open list";
    }else{
        for(int i(0); i < ui->listWidget->count(); i++) {
              str = (ui->listWidget->item(i)->text());
              ba = str.toLocal8Bit();
              c_str = ba.data();
              file.write(c_str);
            }
        }
    file.close();
    updateList();
}

void Favourite::on_listWidget_doubleClicked(const QModelIndex &index)
{
    QString str = ui->listWidget->item(index.row())->text();
    func(str);
    close();
}

void Favourite::on_deleteButton_clicked()
{
    deleteFromList(ui->listWidget->currentRow());
}
