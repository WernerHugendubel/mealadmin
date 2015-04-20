#include "dialoginsertdish.h"
#include "ui_dialoginsertdish.h"

DialogInsertDish::DialogInsertDish(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInsertDish)
{
    ui->setupUi(this);
}

DialogInsertDish::~DialogInsertDish()
{
    delete ui;
}
