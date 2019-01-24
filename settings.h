#ifndef FORM1_H
#define FORM1_H

#include <QWidget>

#include "appmodel.h"

namespace Ui {
class Settings;
}

/**
 * @brief The Settings class - class with UI,
 * which manages program settings
 */
class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
     ~Settings();

    /**
     * @brief getBoolean - takes pointers
     * to boolean values from MainWindow class
     */
    void getBoolean(bool* wwo, bool* owm);
    /**
     * @brief saveToFile - saves choosen server
     * for requests to file
     */
    void saveToFile();
private slots:
    /**
     * @brief on_variant1_clicked - radio button response.
     * Set default server as worldweatheronline.com
     */
    void on_variant1_clicked();
    /**
     * @brief on_variant2_clicked - radio button response.
     * Set default server as openweathermap.org
     */
    void on_variant2_clicked();
private:
    /**
     * @brief wwo - shows selected the server
     * worldweatheronline.com as default
     */
    bool* wwo;
    /**
     * @brief owm - shows selected the server
     * openweathermap.org as default
     */
    bool* owm;
    /**
     * @brief ui - instance of UI
     * Manages all elements of UI
     */
    Ui::Settings *ui;
};

#endif // FORM1_H
