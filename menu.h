#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QJsonDocument>
#include <QString>
#include "apiservice.h"

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    void funkcja1();
    void funkcja2();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();


private:
    Ui::Menu *ui;
    apiservice *api_service;
};

#endif // MENU_H
