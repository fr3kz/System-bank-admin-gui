#ifndef APISERVICE_H
#define APISERVICE_H

#include <QAbstractItemModel>

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QByteArray>
#include <QNetworkReply>
class apiservice : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit apiservice(QObject *parent = nullptr);



private:
};

#endif // APISERVICE_H
