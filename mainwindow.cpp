#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), apiService(new apiservice(this))
{
    ui->setupUi(this);
    QJsonDocument response = apiService->get("http://127.0.0.1:8000/adminpanel/user_count");
    QJsonObject jobj = response.object();

    qDebug() << jobj;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete apiService;
}

void MainWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    QJsonObject transferData;
    transferData["username"] = username;
    transferData["password"] = password;

    QJsonDocument postDataJson(transferData);
    QByteArray postDataByteArray = postDataJson.toJson();

    QJsonDocument response = apiService->post("http://127.0.0.1:8000/login/",postDataByteArray);
    QJsonObject jobj = response.object();
    qDebug() << response;

    //obsluga wyjatkow

    QSettings settings("bank_admin","bank_admin");
    settings.setValue("csrf",jobj["csrf"].toString());
    settings.setValue("sessionid",jobj["sessionid"].toString());
    settings.setValue("userid",jobj["userid"].toString());


    Menu *menu = new Menu(this);
    hide();
    menu->show();

}
