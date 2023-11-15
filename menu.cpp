#include "menu.h"
#include "ui_menu.h"

#include <QFuture>
#include <QtConcurrent>

QSettings settings("bank_admin", "bank_admin");

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu),
    api_service(new apiservice(this))
{
    ui->setupUi(this);


    QFuture<void> wynik1 = QtConcurrent::run(&Menu::funkcja1, this);
    QFuture<void> wynik2 = QtConcurrent::run(&Menu::funkcja2, this);

    // Czekaj na zakończenie wszystkich funkcji
    wynik1.waitForFinished();
    wynik2.waitForFinished();
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
    qDebug() << jobj;
}

void Menu::funkcja2()
{
    QJsonDocument response = api_service->get("http://127.0.0.1:8000/adminpanel/user_count");
    QJsonObject jobj = response.object();
    qDebug() << jobj;
}



// Panel pracowniczy
void Menu::on_pushButton_2_clicked()
{
    // Implementuj logikę dla panelu pracowniczego
}

// Wnioski
void Menu::on_pushButton_3_clicked()
{
    // Implementuj logikę dla panelu wniosków
}

// Wyloguj
void Menu::on_pushButton_clicked()
{
    QCoreApplication::quit();
}
