#include "dialogdishrestriction.h"
#include "ui_dialogdishrestriction.h"

DialogDishRestriction::DialogDishRestriction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDishRestriction)
{
    ui->setupUi(this);
}

DialogDishRestriction::~DialogDishRestriction()
{
    delete ui;
}
