#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogstructure.h"
#include "dialogadmin.h"
#include "connection.h"
#include "dialogsupplier.h"
#include <QMessageBox>
#include <QtDebug>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <login.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 28.12.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/freiw/Qt/5.3/hospmeal.sqlite");

    if (db.open())
    {
        qDebug() << "Opened!";
    }

    if (!db.open()) {
       qDebug() << "No Database Opened!";
    }

    // new 16.04
    // first floor, then Bed (combo) --> patient -textfield.
    //

    qryModelFloor =new QSqlQueryModel();
    qryModelFloor->setQuery("SELECT floor_id, floor FROM floor");
    ui->comboBoxFloor->setModel(qryModelFloor);
    // Spalte 1 ausblenden, nur Namen zeigen
    ui->comboBoxFloor->setModelColumn(1);

     qDebug() << "qryModelFloor: " << qryModelFloor->record(0).value("floor_id").toInt();

     // braucht es trotz on_activated noch!!! bo...

     QModelIndex indexId = qryModelFloor->index(0,0);
     QString id = indexId.data().toString();
     qDebug() << "Index: 0,0 floor: " << id;


     // now set filter from floor to bed!
     // onIndexChanged wird das gemacht

    // first: get the bed-id
    // get the values for menu_id, menu_id_ev from patient_menu

    userModel =new QSqlQueryModel();
    bedModel =new QSqlQueryModel();
    patientModel = new QSqlQueryModel();

    menuModelMittag = new QSqlQueryModel();
    menuModelAbend = new QSqlQueryModel();


    QSqlQuery* qryUser = new QSqlQuery(db);
    QSqlQuery* qryBed = new QSqlQuery(db);
    QSqlQuery* qryPatient = new QSqlQuery(db);

    // combobox source is id + lastname
    qryUser->prepare("select employee_id || '-' || lastname || ' ' ||firstname from employee");

    qryBed->prepare("select bed_id,description from bed");

    qryPatient->prepare("select patient_id, lastname,firstname from patient");
    qryUser->exec();
    qryBed->exec();
    qryPatient->exec();

    userModel->setQuery(*qryUser);
    bedModel->setQuery(*qryBed);
    patientModel->setQuery(*qryPatient);

    bedModel->setQuery("select bed_id,description from bed where floor_id="+id);


    ui->comboBoxUser->setModel(userModel);

    ui->comboBoxBed->setModel(bedModel);

    ui->comboBoxBed->setModelColumn(1);

    ui->comboBoxPatient->setModel(patientModel);
    ui->comboBoxPatient->setModelColumn(1);


    qDebug() << (userModel->rowCount());
    qDebug() << (bedModel->rowCount());

    // Menu select 30.12
    QSqlQueryModel * menuMidModel =new QSqlQueryModel();
    QSqlQueryModel * menuEvModel =new QSqlQueryModel();

    QSqlQuery* qryMenuMid = new QSqlQuery(db);
    QSqlQuery* qryMenuEv = new QSqlQuery(db);

    qryMenuMid->prepare("select menu_id || '-' ||menuname from menu;");
    qryMenuEv->prepare("select menu_id || '-' ||menuname from menu;");

    qryMenuMid->exec();
    qryMenuEv->exec();

    menuMidModel->setQuery(*qryMenuMid);
    menuEvModel->setQuery(*qryMenuEv);

    ui->comboBoxMenuMid->setModel(menuMidModel);
    ui->comboBoxMenuMid->setStyleSheet("QWidget {background-color:red; color:black;}");
    ui->comboBoxMenuEv->setModel(menuEvModel);
    ui->comboBoxMenuEv->setStyleSheet("QWidget {background-color:green; color:white;}");


    // Patient-Restricitons
    // relational table View for "PatientMenu"
    modelPatientDietary_req = new QSqlRelationalTableModel(this);
    modelPatientDietary_req ->setTable("patient_dietary_req");
    modelPatientDietary_req ->setSort(0, Qt::AscendingOrder);
    modelPatientDietary_req ->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelPatientDietary_req ->setHeaderData(0, Qt::Horizontal, tr("abc"));
    modelPatientDietary_req ->setHeaderData(1, Qt::Horizontal, tr("cde"));

    // 1 = colum with foregin key!
    // stellt automatisch Wert von Foregin key dar!! course_id ... description!!!
   // modelPatientDietary_req ->setRelation(0, QSqlRelation("patient", "patient_id", "firstname"));
    modelPatientDietary_req ->setRelation(1, QSqlRelation("dietary_req", "dietary_req_id", "description"));

    modelPatientDietary_req ->select();

    tableViewPatientDietary_req = new QTableView;

    //ui->tableViewPatientDietary_req ->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableViewPatientDietary_req ->resizeColumnsToContents();

    //ui->tableViewPatientDietary_req ->setModel(modelPatientDietary_req );

    // error was missing ui-> !!!
    //ui->tableViewPatientDietary_req ->setColumnHidden(0, true);

    //ui->tableViewPatientDietary_req->setItemDelegate(new QSqlRelationalDelegate(tableViewPatientDietary_req));

   // ui->lineEditUser->setText("");





    /*
     *  Input data in tables
     *  QSqlQuery query;
    query.prepare("INSERT INTO person (id, forename, surname) "
                  "VALUES (:id, :forename, :surname)");
    query.bindValue(":id", 1001);
    query.bindValue(":forename", "Bart");
    query.bindValue(":surname", "Simpson");
    query.exec();
     *
     *
     *
     * */

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // create DB hospital
    QMessageBox msgBox;
    msgBox.setText("Database not found!");
    msgBox.setInformativeText("Do you want to create a new one?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    qDebug() << ret;
    qDebug() << "Tschüss";

    if (ret == 16384) {
    qDebug() << "Yes"; // create Database
    qDebug() <<  QDir::current();

    createConnection();

    }
}

void MainWindow::on_pushButton_Structure_clicked()
{
    DialogStructure d;
    d.setModal(true);
    d.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
  //  ui->textEdit->setText("Hallo");
}

void MainWindow::on_pushButton_Supplier_clicked()
{
    DialogSupplier mDialog;
    mDialog.setModal(true);
    mDialog.exec();
}

void MainWindow::on_pushButtonPatientDietary_req_newRecord_clicked()
{
    int row = modelPatientDietary_req->rowCount();
    modelPatientDietary_req->insertRow(row);
    // access item in index(row,column,[parentindex])
    // 1 = meal
    QModelIndex index = modelPatientDietary_req->index(row,1, QModelIndex());
    tableViewPatientDietary_req->setCurrentIndex(index);
    modelPatientDietary_req->submit();
    modelPatientDietary_req->submitAll();
}


void MainWindow::on_pushButtonSaveOrder_clicked()
{
    // error qDebug() << ui->comboBoxMenuMid->currentData();
     qDebug() << ui->comboBoxMenuMid->currentText() << " Menu_Mid: ";

     QString st = ui->comboBoxBed->currentText();
     qDebug()<< st.indexOf("-");
     qDebug() << "Zahl : " << st.mid(0,1).toInt();
     qDebug() << ui->comboBoxMenuEv->currentText();
     qDebug() << ui->lineEditDate->text();
     qDebug() << ui->comboBoxMenuEv->currentText();
     qDebug() << ui->comboBoxBed->currentText() << " Bed:";
}

void MainWindow::on_pushButton_admin_clicked()
{
    DialogAdmin aDialog;
    aDialog.setModal(true);
    aDialog.exec();
}

/*
    QModelIndex indexId = qryModelFloor->index(index,0);
    QString id = indexId.data().toString();
    qDebug() << "Index: floor: " << id;
*/

void MainWindow::on_comboBoxFloor_currentIndexChanged(int index)
{

  indexId = qryModelFloor->index(index,0);
  QString id = indexId.data().toString();
  qDebug() << "id_indexId.data: "<< id;

  if (index > 0) { qDebug() << "qryModelFloor: " << qryModelFloor->record(index).value("floor_id").toInt();
      bedModel->setQuery("select bed_id,description from bed where floor_id="+id);
  }

}


void MainWindow::on_comboBoxFloor_activated(int index)
{
    indexId = qryModelFloor->index(index,0);
    QString id = indexId.data().toString();
    qDebug() << "on_activated: " << "id_indexId.data: "<< id;

    if (index == 0) { qDebug() << "qryModelFloor: " << qryModelFloor->record(index).value("floor_id").toInt();
        bedModel->setQuery("select bed_id,description from bed where floor_id="+id);
    }



}
