#ifndef FORM_H
#define FORM_H

#include <QWidget>

#include "appmodel.h"

namespace Ui {
class Favourite;
}

/**
 * @brief The Favourite class - class with UI,
 * which manages list of favourite places
 */
class Favourite : public QWidget
{
    Q_OBJECT

public:
    explicit Favourite(QWidget *parent = nullptr);
    ~Favourite();
    /**
     * @brief updateList - updates list of
     * favourite places after addition or deletion
     */
    void updateList();
    /**
     * @brief deleteFromList - delete selected note from the list
     * After deletion updates list
     * Takes index of note as parameters
     */
    void deleteFromList(const int index);
    /**
     * @brief setCity - set city name to
     * local city variable
     * Takes city name as parameters
     */
    void setCity(QString value);
    /**
     * @brief setCallback - set callback to interact with MainWindow class
     * Takes lambda expression as parameters
     */
    void setCallback(std::function<void(QString)> callback);

private slots:
    /**
     * @brief on_addButton_clicked - response to add button
     * Add a note to list of favourite places
     */
    void on_addButton_clicked();
    /**
     * @brief on_deleteButton_clicked - response to delete button
     * Delete a selected note from list of favourite places
     */
    void on_deleteButton_clicked();
    /**
     * @brief on_listWidget_doubleClicked - response to double click
     * on listWidget item
     * After double click find weather in this place
     * Takes index of selected note as parameters
     */
    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    /**
     * @brief func - lamda expression for callback
     */
    std::function<void(QString)> func = nullptr;
    /**
     * @brief city - holds name of the city
     * in which weather is looking for
     */
    QString city;
    /**
     * @brief mod - holds array AppModel
     * instance, used for information storage
     */
    AppModel *mod;
    /**
     * @brief ui - instance of UI
     * Manages all elements of UI
     */
    Ui::Favourite *ui;

};

#endif // FORM_H
