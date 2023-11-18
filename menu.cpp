#include "menu.h"
#include "ui_menu.h"
#include "userpanel.h"
#include "employepanel.h"

#include <QFuture>
#include <QtConcurrent>


QSettings settings("bank_admin", "bank_admin");

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu),
    api_service(new apiservice(this))
{
    ui->setupUi(this);

    //wyswietlenie informacji w qeventloop

    QJsonDocument response = api_service->get("http://127.0.0.1:8000/adminpanel/user_count");
    QJsonObject jobj = response.object();

    QJsonDocument response_1 = api_service->get("http://127.0.0.1:8000/adminpanel/employe_count");
    QJsonObject jobj_1 = response_1.object();

    QJsonDocument response_2 = api_service->get("http://127.0.0.1:8000/adminpanel/ticket_count");
    QJsonObject jobj_2 = response_2.object();


    int value = jobj["value"].toInt();
    std::string t = "ilosc uzytkownikow: " + std::to_string(value);

    int value1 = jobj_1["value"].toInt();
    std::string t1 = "ilosc pracownikow: " + std::to_string(value1);

    int value2 = jobj_2["value"].toInt();
    std::string t2 = "ilosc wnioskow: " + std::to_string(value2);

    ui->label->setText(QString::fromStdString(t));
    ui->label_2->setText(QString::fromStdString(t1));
    ui->label_3->setText(QString::fromStdString(t2));





/*
    ///nie dziala
    QFuture<void> wynik1 = QtConcurrent::run(&Menu::funkcja1, this);
    QFuture<void> wynik2 = QtConcurrent::run(&Menu::funkcja2, this);

    // Czekaj na zakończenie wszystkich funkcji
    wynik1.waitForFinished();
    wynik2.waitForFinished();*/
}

Menu::~Menu()
{
    delete ui;
    delete api_service;
}

void Menu::funkcja1()
{
    QJsonDocument response = api_service->get("http://127.0.0.1:8000/adminpanel/user_count");
    QJsonObject jobj = response.object();
    qDebug() << jobj["value"].toInt();
}

void Menu::funkcja2()
{
    QJsonDocument response = api_service->get("http://127.0.0.1:8000/adminpanel/employe_count");
    QJsonObject jobj = response.object();
    qDebug() << jobj;
}



// Panel pracowniczy
void Menu::on_pushButton_2_clicked()
{
    // Implementuj logikę dla panelu pracowniczego nowy widok
    employepanel *emppanel = new employepanel(this);
    //hide();
    emppanel->show();
}

// Wnioski
void Menu::on_pushButton_3_clicked()
{
   //nowy widok i powrot do menu
    UserPanel *userpanel = new UserPanel(this);
    //hide();
    userpanel->show();
}

// Wyloguj
void Menu::on_pushButton_clicked()
{
    QCoreApplication::quit();
}
