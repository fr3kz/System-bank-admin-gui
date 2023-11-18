#include "employepanel.h"
#include "ui_employepanel.h"
#include "apiservice.h"


#include <QJsonArray>
#include <QJsonObject>
#include <QListWidget>
#include <QSettings>

employepanel::employepanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::employepanel),api(new apiservice(this))
{
    ui->setupUi(this);

    QSettings settings("bank_admin","bank_admin");

    QJsonDocument response = api->get("http://127.0.0.1:8000/adminpanel/show_employess/");
    QJsonArray users_array = response.array();

    QList<QMap<QString,QVariant>> users_list;

    for(QJsonValue value: users_array){
        if(value.isObject()){
            QJsonObject jobj = value.toObject();
            QMap<QString,QVariant> user_data;

            user_data["id"] = jobj["id"].toInt();
            user_data["username"] = jobj["username"].toString();

            users_list.append(user_data);

        }
    }

    QListWidget *listwidget = ui->listWidget;

    for(auto data:users_list){
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString("ID: %1 ,username %2")
                          .arg(data["id"].toInt())
                          .arg(data["username"].toString())


                      );

        listwidget->addItem(item);
    }

    listwidget->show();

}

employepanel::~employepanel()
{
    delete ui;
    delete api;
}

//usuwanie pracownika
void employepanel::on_pushButton_clicked()
{
    //dostanie id z textu

    QListWidgetItem *item = ui->listWidget->currentItem();

    QString inputString = item->text();
    int idIndex = inputString.indexOf("ID: ");
    QString idValue;

    if (idIndex != -1) {
        QString idSubstring = inputString.mid(idIndex + 4);
        QStringList idParts = idSubstring.split(' ', Qt::SkipEmptyParts);

        if (!idParts.isEmpty()) {
            idValue = idParts.first();
        }
    }
    QString userid = idValue;

    //wysalnie zapytania
    QString url = "http://127.0.0.1:8000/adminpanel/delete_employee/" + userid + "/";
    QJsonDocument response = api->get(url);
    QJsonObject jobj = response.object();
    delete item;
    qDebug() << jobj;

}


void employepanel::on_pushButton_2_clicked()
{
    hide();
}

