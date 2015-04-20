#include "dialogudatedishes.h"
#include "ui_dialogudatedishes.h"

DialogUdateDishes::DialogUdateDishes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUdateDishes)
{
    ui->setupUi(this);
}

DialogUdateDishes::~DialogUdateDishes()
{
    delete ui;
}
