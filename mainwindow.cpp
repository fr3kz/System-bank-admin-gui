#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QUrlQuery postData;
    postData.addQueryItem("account1_id", "111111");
    postData.addQueryItem("account2_id", "333333");
    postData.addQueryItem("amount","1");
    postData.addQueryItem("title","test z innego apki");

    // Utwórz obiekt managera i żądanie
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request(QUrl("http://127.0.0.1:8000/accounts/transfer/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Wysyłanie żądania POST
    QNetworkReply *reply = manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

    // Oczekiwanie na zakończenie żądania
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Obsługa odpowiedzi
    QString data;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        data = QString(responseData);
        // qDebug() << data;
    } else {
        qDebug() << "Error: " << reply->errorString();
    }

    // Usuń obiekt odpowiedzi i managera
    reply->deleteLater();
    manager->deleteLater();

}

MainWindow::~MainWindow()
{
    delete ui;
}

