#ifndef EMPLOYEPANEL_H
#define EMPLOYEPANEL_H

#include <QWidget>
#include "apiservice.h"

namespace Ui {
class employepanel;
}

class employepanel : public QWidget
{
    Q_OBJECT

public:
    explicit employepanel(QWidget *parent = nullptr);
    ~employepanel();

private:
    Ui::employepanel *ui;
    apiservice *api;
};

#endif // EMPLOYEPANEL_H
