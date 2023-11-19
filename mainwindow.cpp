#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>
#include <QMessageBox>
#include <QJsonArray>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), apiService(new apiservice(this))
{
    ui->setupUi(this);
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

    if(username == "" || password == "")
    {
        QMessageBox::critical(this,"Error","Wszystkie pola musza byc wypelnione");
        return;
    }

    QJsonObject transferData;
    transferData["username"] = username;
    transferData["password"] = password;

    QJsonDocument postDataJson(transferData);
    QByteArray postDataByteArray = postDataJson.toJson();

    QJsonDocument response = apiService->post("http://127.0.0.1:8000/login/",postDataByteArray);
    QJsonObject jobj = response.object();
    qDebug() << response;
    if(jobj["value"].toString() != "")
    {
        qDebug() << jobj["error"].toString();
        QJsonObject errorobj = jobj["error"].toObject();
        QJsonArray valueArray = errorobj["value"].toArray();

        QMessageBox::critical(this,"Error",valueArray[0].toString());
        return;
    }else{
        QSettings settings("bank_admin","bank_admin");
        settings.setValue("csrf",jobj["csrf"].toString());
        settings.setValue("sessionid",jobj["sessionid"].toString());
        settings.setValue("userid",jobj["userid"].toString());


        Menu *menu = new Menu(this);
        hide();
        menu->show();
        return;
    }


}
