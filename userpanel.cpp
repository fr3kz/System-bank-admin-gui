#include "userpanel.h"
#include "ui_userpanel.h"
#include "menu.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QMap>
#include <QSettings>
#include <QString>

UserPanel::UserPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPanel),api(new apiservice(this))
{
    ui->setupUi(this);

    QSettings settings("firma","nienazwany1");

    QJsonDocument response = api->get("http://127.0.0.1:8000/adminpanel/ticket_list/");
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


    /*for (const auto &transferData : users_list) {
        qDebug() << "ID:" << transferData["id"] << "Account1:" << transferData["username"] << "Account2:";
    }*/

    //wyswietlanie listy obietkow na kliknecie otwarcie nowego okna z dwoma przyciskami

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

UserPanel::~UserPanel()
{
    delete ui;
    delete api;
}



void UserPanel::on_pushButton_2_clicked()
{

    hide();
}

//aktywacja
void UserPanel::on_pushButton_clicked()
{
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


    //wykoanie zapytanian do api z userid
    QString url = "http://127.0.0.1:8000/adminpanel/activate_user/" + userid + "/";


    QJsonDocument response = api->get(url);
    QJsonObject jobj = response.object();
    qDebug() << jobj;

    //usuniecie z bazy danych rowniez
    delete item;
}

