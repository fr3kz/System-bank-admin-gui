#include "menu.h"
#include "ui_menu.h"

#include <QSettings>


QSettings settings("bank_admin","bank_admin");

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    //zapytanie do bazy danych, ilosc pracownikow wniskow pracownikow
    //concurency

    //deklaracje
    apiservice *api = new apiservice(this);
    QString userid = settings.value("userid").toString();
    QString csrf = settings.value("csrf").toString();
    QString sessionid = settings.value("sessionid").toString();

    //requesty

    QJsonDocument *respose = api->get("http://127.0.0.1:8000/adminpanel/user_count");
    QJsonDocument *respose1 = api->get("http://127.0.0.1:8000/adminpanel/employe_count");
    QJsonDocument *respose2 = api->get("http://127.0.0.1:8000/adminpanel/ticket_count");

    //wyjatki, bledy




    //wyswiewtlenie uzytkownik,pracownik, wnioski
    ui->label->setText(response.object());
    ui->label_2->setText(response1.object());
    ui->label_3->setText(response2.object());



}

Menu::~Menu()
{
    delete ui;
}

//panel pracowniczy
void Menu::on_pushButton_2_clicked()
{

}



//Wnioski
void Menu::on_pushButton_3_clicked()
{

}

//Wyloguj
void Menu::on_pushButton_clicked()
{
   QCoreApplication::quit();
}

