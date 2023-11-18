#include "apiservice.h"
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QDebug>
#include <QByteArray>
#include <QSettings>
#include <QNetworkCookie>

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
    // Utwórz QNetworkAccessManager jako zmienną składową klasy, aby uniknąć wycieku pamięci
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QUrl url(url_);
    QNetworkRequest request(url);

    QString csrf = "j5f2ZRbXPfWcXWUhIOqYTfcljIsAFVskBA6QomHKXEBnWG7gV6vughB8U7N2A1Xz";
    QByteArray csrfbyte = csrf.toUtf8();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("X-CSRFToken", csrfbyte);

    QNetworkReply *reply = manager->get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec(); // Czekaj na zakończenie odpowiedzi

    QJsonDocument datajson;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);

        if (jsonDocument.isNull()) {
            qDebug() << "Błąd parsowania JSON: Nieprawidłowy format danych";
        } else {
            // ... twój kod obsługi prawidłowego JSON ...
            return jsonDocument;
        }
    } else {
        qDebug() << "Błąd zapytania: " << reply->errorString();
    }

    reply->deleteLater();

    // Zwróć pustą dokumentację JSON w przypadku błędu
    return QJsonDocument();
}

QJsonDocument apiservice::get_auth(QString url_) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QSettings settings("bank_admin","bank_admin");


    QString sessid = settings.value("sessionid").toString();
    QNetworkCookie sessionCookie("sessionid", sessid.toUtf8());
    QList<QNetworkCookie> cookies;
    cookies.append(sessionCookie);


    QUrl url(url_);
    QNetworkRequest request(url);

    QString csrf = get_csrf();
    QByteArray csrfbyte = csrf.toUtf8();

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(cookies));
    request.setRawHeader("X-CSRFToken", csrfbyte);


    QNetworkReply *reply = manager->get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec(); // Czekaj na zakończenie odpowiedzi

    QJsonDocument datajson;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);

        if (jsonDocument.isNull()) {
            qDebug() << "Błąd parsowania JSON: Nieprawidłowy format danych";
        } else {
            // ... twój kod obsługi prawidłowego JSON ...
            return jsonDocument;
        }
    } else {
        qDebug() << "Błąd zapytania: " << reply->errorString();
    }

    reply->deleteLater();

    // Zwróć pustą dokumentację JSON w przypadku błędu
    return QJsonDocument();
}

QString apiservice::get_csrf() {
    QString url_ = "http://127.0.0.1:8000/csrf/";


    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QUrl url(url_);
    QNetworkRequest request(url);



    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply *reply = manager->get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec(); // Czekaj na zakończenie odpowiedzi


    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);

        if (jsonDocument.isNull()) {
            qDebug() << "Błąd parsowania JSON: Nieprawidłowy format danych";
        } else {
            QJsonObject jobj = jsonDocument.object();
            return jobj["csrf"].toString();
        }
    } else {
        qDebug() << "Błąd zapytania: " << reply->errorString();
    }

    reply->deleteLater();

    // Zwróć pustą dokumentację JSON w przypadku błędu
    return QString();
}
