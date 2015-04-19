#include "dialogsupplier.h"
#include "ui_dialogsupplier.h"
#include "connection.h"

DialogSupplier::DialogSupplier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSupplier)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/freiw/Qt/5.3/hospmeal.sqlite");

     if (db.open())
     {
         qDebug() << "Opened!";
     }

     if (!db.open()) {
        qDebug() << "No Database Opened!";
     }


     qryTableModelDish =new QSqlTableModel();
     qryTableModelDish->setTable("Dish");
     qryTableModelDish->setEditStrategy(QSqlTableModel::OnManualSubmit);
     //qryTableModelDish->OnRowChange;

     qryTableModelDish->select();

     ui->tableViewDish->setModel(qryTableModelDish);

     // Spalte 1 ausblenden, nur Namen zeigen
     //ui->comboBoxFloor->setModelColumn(1);
  qDebug() << "TableViewDish - activated!";


}

DialogSupplier::~DialogSupplier()
{
    delete ui;
}

void DialogSupplier::on_pushButtonSave_clicked()
{
    qryTableModelDish->submitAll();
}

void DialogSupplier::on_DialogSupplier_destroyed()
{
    qDebug() << " windows supplier destroyed";

}
