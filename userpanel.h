#ifndef USERPANEL_H
#define USERPANEL_H

#include <QWidget>
#include "apiservice.h"
namespace Ui {
class UserPanel;
}

class UserPanel : public QWidget
{
    Q_OBJECT

public:
    explicit UserPanel(QWidget *parent = nullptr);
    ~UserPanel();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::UserPanel *ui;
    apiservice *api;
};

#endif // USERPANEL_H
