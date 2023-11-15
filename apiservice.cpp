#include "apiservice.h"
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QDebug>
#include <QByteArray>

apiservice::apiservice(QObject *parent) : QObject(parent) {}

QJsonDocument apiservice::post(QString url_, QByteArray data) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url(url_);
    QNetworkRequest request(url);

    QString csrf = "j5f2ZRbXPfWcXWUhIOqYTfcljIsAFVskBA6QomHKXEBnWG7gV6vughB8U7N2A1Xz";
    QByteArray csrfbyte = csrf.toUtf8();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-CSRFToken", csrfbyte);



    QNetworkReply *reply = manager->post(request, data);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
        return jsonDocument;

    } else {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
        return jsonDocument;
        qDebug() << "Error: " << reply->errorString();
    }

    reply->deleteLater();
}

QJsonDocument apiservice::post_auth(QString url_) {

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url(url_);
    QNetworkRequest request(url);

    QString csrf = get_csrf();
    QByteArray csrfbyte = csrf.toUtf8();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-CSRFToken", csrfbyte);

    QJsonObject transferData;
    transferData["account1_id"] = "111111";
    transferData["account2_id"] = "333333";
    transferData["amount"] = 1;
    transferData["title"] = "test z innego apki";

    QJsonDocument postDataJson(transferData);
    QByteArray postDataByteArray = postDataJson.toJson();

    QNetworkReply *reply = manager->post(request, postDataByteArray);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);

        return jsonDocument;
    } else {
        qDebug() << "Error: " << reply->errorString();
    }

    reply->deleteLater();
    // Modify the return type as needed
}

QJsonDocument apiservice::get(QString url_) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url(url_);
    QNetworkRequest request(url);

    QString csrf = get_csrf();
    QByteArray csrfbyte = csrf.toUtf8();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("X-CSRFToken", csrfbyte);

    QNetworkReply *reply = manager->get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    QJsonDocument datajson;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);

        return jsonDocument;
    } else {
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}

QJsonDocument apiservice::get_auth(QString url_) {
    QNetworkAccessManager manager;
    QUrl url(url_);
    QNetworkRequest request(url);

    QString csrf = get_csrf();
    QByteArray csrfbyte = csrf.toUtf8();
    QString sessionid = "";
    QByteArray sessionidbyte = sessionid.toUtf8();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("X-CSRFToken", csrfbyte);
    request.setRawHeader("sessionid", sessionidbyte);

    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);

        return jsonDocument;

    } else {
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}

QString apiservice::get_csrf() {
    QJsonDocument response = get("http://127.0.0.1:8000/csrf/");
    QJsonObject jobj = response.object();
    return jobj["csrf"].toString();
}
