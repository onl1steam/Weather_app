#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "appmodel.h"

namespace Ui {
class Favourite;
}

class Favourite : public QWidget
{
    Q_OBJECT

public:
    explicit Favourite(QWidget *parent = nullptr);

    void updateList();
    void deleteFromList(const int index);
    void setCity(QString value);
    void setCallback(std::function<void(QString)> callback);
    ~Favourite();

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

private:

    std::function<void(QString)> func = nullptr;
    QString city;
    AppModel *mod;
    Ui::Favourite *ui;

};

#endif // FORM_H
