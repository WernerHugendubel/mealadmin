#include "dialoggetlistordereddishes.h"
#include "ui_dialoggetlistordereddishes.h"

DialogGetListOrderedDishes::DialogGetListOrderedDishes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGetListOrderedDishes)
{
    ui->setupUi(this);
}

DialogGetListOrderedDishes::~DialogGetListOrderedDishes()
{
    delete ui;
}
