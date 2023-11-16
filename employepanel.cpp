#include "employepanel.h"
#include "ui_employepanel.h"
#include "apiservice.h"

employepanel::employepanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::employepanel),api(new apiservice(this))
{
    ui->setupUi(this);
}

employepanel::~employepanel()
{
    delete ui;
    delete api;
}
