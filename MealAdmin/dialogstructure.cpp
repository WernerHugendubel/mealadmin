#include "dialogstructure.h"
#include "ui_dialogstructure.h"
#include "connection.h"
#include "QSqlQueryModel"
#include "QSqlTableModel"
#include "QSqlRelation"
#include "QSqlRelationalDelegate"
#include <QtDebug>
#include <QSqlError>


DialogStructure::DialogStructure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStructure)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/freiw/Qt/5.3/hospmeal.sqlite");

    if (db.open())
    {
        qDebug() << "Opened!";
    }

    if (!db.open()) {
       qDebug() << "No Database Opened!";
    }

    model = new QSqlTableModel(this);
    model->setTable("floor");
    model->setSort(0, Qt::AscendingOrder);
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Floor"));
    model->setHeaderData(2, Qt::Horizontal, tr("Description"));
    model->select();


    tableView = new QTableView;
    tableView->setColumnHidden(0, true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->resizeColumnsToContents();

    ui->setupUi(this);

    ui->tableView->setModel(model);


    // **************************************************************************************
    // relational table View for "dish"
    modelMeal = new QSqlRelationalTableModel(this);
    modelMeal->setTable("dish");
    model->setSort(0, Qt::AscendingOrder);
    modelMeal->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelMeal->setHeaderData(0, Qt::Horizontal, tr("ID"));
    // 1 = colume with foregin key!
    // stellt automatisch Wert von Foregin key dar!! course_id ... description!!!
    modelMeal->setRelation(1, QSqlRelation("course", "course_id", "description"));
    modelMeal->select();

    tableViewMeal = new QTableView;
    tableViewMeal->setColumnHidden(0, true);

    tableViewMeal->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableViewMeal->resizeColumnsToContents();

    ui->tableViewMeal->setModel(modelMeal);
    // combo box!
    ui->tableViewMeal->setItemDelegate(new QSqlRelationalDelegate(tableViewMeal));


    // **************************************************************************************
    // relational table View for "patient"
    modelPatient = new QSqlTableModel(this);
    modelPatient->setTable("Patient");
    model->setSort(0, Qt::AscendingOrder);
    //modelPatient->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelPatient->setHeaderData(0, Qt::Horizontal, tr("ID"));
    modelPatient->select();

    tableViewPatient = new QTableView;
    //tableViewPatient->setColumnHidden(0, true);
    //tableViewPatient->setSelectionBehavior(QAbstractItemView::SelectRows);
    //tableViewPatient->resizeColumnsToContents();

    ui->tableView_Patient->setModel(modelPatient);

    // **************************************************************************************
    // relational table View for "PatientMenu"
    modelPatientMenu = new QSqlRelationalTableModel(this);
    modelPatientMenu->setTable("patient_menu");
    modelPatientMenu->setSort(0, Qt::AscendingOrder);
    modelPatientMenu->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelPatientMenu->setHeaderData(0, Qt::Horizontal, tr("Date"));
    modelPatientMenu->setHeaderData(1, Qt::Horizontal, tr("Patient"));
    modelPatientMenu->setHeaderData(3, Qt::Horizontal, tr("Menu"));

    /* The setRelation() function calls establish a relationship between two tables. The first call specifies that column 1
    * in table patient_menu is a foreign key that maps with field patient_id of table patient,
    * and that the view should present the name lastname to the user. The second call does something similar with column 2.
    */

    // 1= column no 1 = patient_id, 2= column no 2 = menu_id

    modelPatientMenu->setRelation(1, QSqlRelation("patient", "patient_id", "lastname"));
    modelPatientMenu->setRelation(2, QSqlRelation("menu", "menu_id", "menuname"));

    modelPatientMenu->select();

    tableViewPatientMenu = new QTableView;
    tableViewPatientMenu->setColumnHidden(0, true);

    tableViewPatientMenu->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableViewPatientMenu->resizeColumnsToContents();

    ui->tableViewPatientMenu->setModel(modelPatientMenu);
    // combo box! this works in automatic way for all relations ( menuname, lastname)
    ui->tableViewPatientMenu->setItemDelegate(new QSqlRelationalDelegate(tableViewPatientMenu));


}

DialogStructure::~DialogStructure()
{
   delete ui;
}

void DialogStructure::on_pushButton_NewRecord_clicked()
{
    int row = model->rowCount();

    model->insertRow(row);
    // access item in index(row,column,[parentindex])
    // 1 = floor
    QModelIndex index = model->index(row,1, QModelIndex());

    tableView->setCurrentIndex(index);
   // tableView->edit(index);

   //   qDebug() << "insertRow" << model->lastError().text();
}

void DialogStructure::on_pushButton_DeleteRecordFloor_clicked()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
        while (!indexes.isEmpty())
        {
            model->removeRows(indexes.last().row(), 1, QModelIndex());
            indexes.removeLast();
        }

}

void DialogStructure::on_pushButton_NewRecordDish_clicked()
{
    int row = modelMeal->rowCount();

    modelMeal->insertRow(row);
    // access item in index(row,column,[parentindex])
    // 1 = meal
    QModelIndex index = modelMeal->index(row,1, QModelIndex());


    tableViewMeal->setCurrentIndex(index);

     // tableViewMeal->edit(index);
      modelMeal->submitAll();
}

void DialogStructure::on_pushButton_DeleteRecordDish_clicked()
{
    QModelIndexList indexes = ui->tableViewMeal->selectionModel()->selectedRows();

        while (!indexes.isEmpty())
        {
            modelMeal->removeRows(indexes.last().row(),1, QModelIndex());
            indexes.removeLast();
        }
       modelMeal->submitAll();
}

void DialogStructure::on_pushButton_NewRecordPerson_clicked()
{
    int row = modelPatient->rowCount();

    modelPatient->insertRow(row);
    QModelIndex index = modelPatient->index(row,1, QModelIndex());


    tableViewPatient->setCurrentIndex(index);
    //tableViewPatient->edit(index);
}

void DialogStructure::on_pushButton_DeleteRecordPatient_clicked()
{
    QModelIndexList indexes = ui->tableView_Patient->selectionModel()->selectedRows();

        while (!indexes.isEmpty())
        {
            modelPatient->removeRows(indexes.last().row(),1, QModelIndex());
            indexes.removeLast();
        }
        modelPatient->submitAll();
}

void DialogStructure::on_NewRecordPatientMenu_clicked()
{
    int row = modelPatientMenu->rowCount();

    modelPatientMenu->insertRow(row);
    // access item in index(row,column,[parentindex])
    // 1 = meal
    QModelIndex index = modelPatientMenu->index(row,1, QModelIndex());

    tableViewPatientMenu->setCurrentIndex(index);

    modelPatientMenu->submit();
    modelPatientMenu->submitAll();

}

void DialogStructure::on_DeleteRecordPatientMenu_clicked()
{

}
