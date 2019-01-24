#ifndef FORM1_H
#define FORM1_H

#include <QWidget>

#include "appmodel.h"

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);

    void getBoolean(bool* wwo, bool* owm);
    void saveToFile();

    ~Settings();

private slots:


    void on_variant1_clicked();

    void on_variant2_clicked();

private:

    bool* wwo;
    bool* owm;
    Ui::Settings *ui;

};

#endif // FORM1_H
