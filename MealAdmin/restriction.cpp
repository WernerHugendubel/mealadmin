// 18.03.2015
// 07.04.2015

#include "restriction.h"
#include "ui_restriction.h"
#include "QDebug"
#include <QSqlQuery>
#include <QString>
#include <QDateTime>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QSqlError>


Restriction::Restriction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Restriction)
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

    // model für Tabelle "patient"   -- oder besser einfach QSqlQueryModel ?? QSqlTableModel ist editierbar.. braucht es nicht!
    patientModel = new QSqlTableModel(this);
    patientModel->setTable("patient");
    patientModel->select();
    ui->comboBoxPatient->setModel(patientModel);
    // jetzt versuchen comboBoxPatient ... Spalte mit id ausblenden!
    // 2 = Lastname
    ui->comboBoxPatient->setModelColumn(2);


    // model für"patient_diet_req" ************************************************************************************
    // QsqlRelationalTableModel - weil Fremdschlüssel "patient_id" und "dietary_req_id" vorhanden sind.
    //

    modelPatDietReq = new QSqlRelationalTableModel(this);

    modelPatDietReq->setTable("patient_dietary_req");
    modelPatDietReq->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelPatDietReq->setRelation(1,QSqlRelation("dietary_req","dietary_req_id","description"));
    modelPatDietReq->select();

    tableViewPatientDietReq = new QTableView;
    // patient_id von ComboBox holen!
    QModelIndex indexId = patientModel->index(0,0);
    QString id = indexId.data().toString();
    modelPatDietReq->setFilter("patient_id = " + id);
    //tableViewPatientDietReq->resizeColumnsToContents();
    ui->tableViewPatientDietReq->setModel(modelPatDietReq);
    ui->tableViewPatientDietReq->setItemDelegate(new QSqlRelationalDelegate(tableViewPatientDietReq));

     /*

    QSqlQuery query;
    query.exec("INSERT INTO employee (id, name, salary) "
                "VALUES (1001, 'Thad Beaumont', 65000)");
       QSqlQuery query;
          query.prepare("INSERT INTO employee (id, name, salary) "
                        "VALUES (:id, :name, :salary)");
          query.bindValue(":id", 1001);
          query.bindValue(":name", "Thad Beaumont");
          query.bindValue(":salary", 65000);
          query.exec();
          // Transaction!!!
          QSqlDatabase::database().transaction();
              QSqlQuery query;
              query.exec("SELECT id FROM employee WHERE name = 'Torild Halvorsen'");
              if (query.next()) {
                  int employeeId = query.value(0).toInt();
                  query.exec("INSERT INTO project (id, name, ownerid) "
                             "VALUES (201, 'Manhattan Project', "
                             + QString::number(employeeId) + ')');
              }
              QSqlDatabase::database().commit();
              */
    //db.close();


}

Restriction::~Restriction()
{
    delete ui;
}

void Restriction::on_comboBoxBed_currentIndexChanged(const QString &arg1)
{
    QString name = ui->comboBoxBed->currentText();
    qDebug() << name;


}

void Restriction::on_pushButton_clicked()
{

   QString xsql;
   QString menu_id;
   QString bed_id;



   QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("/home/freiw/Qt/5.3/hospmeal.sqlite");

   if (db.open())
   {
       qDebug() << "Opened!";
   }

   if (!db.open()) {
      qDebug() << "No Database Opened!";
   }

    //QString bett_nr = ui->comboBoxBed->currentData().String;
    bed_id = ui->comboBoxBed->currentText();
    menu_id = ui->comboBoxMenu->currentText();

    qDebug() << "Bed-id: " << bed_id;
    qDebug() << "Menu-id: " << menu_id;
    qDebug() << "Bed-id: current index:" << ui->comboBoxBed->currentIndex();
    QString now = QDateTime::currentDateTime().toString(Qt::ISODate);

    QSqlDatabase::database().transaction();

    // now get the patient-id from bed_patient
    // save patient-id and menu-id in patient_menu

    QSqlQuery query;
    //insert date, patient_id, menu_id ... in patient_menu
    xsql = "insert into patient_menu(date,patient_id, menu_id) values (" + now + ","+bed_id +"," + menu_id+");";
    /*
       query.exec("INSERT INTO project (id, name, ownerid) "
                   "VALUES (201, 'Manhattan Project', "
                 + QString::number(employeeId) + ')');
    */
    QSqlDatabase::database().transaction();
    QSqlQuery query1;
    query1.exec(xsql);
    QSqlDatabase::database().commit();
    db.close();

}


void Restriction::on_comboBoxPatient_currentIndexChanged(int index)
{
   // indexId hat ein Element des Models (zeile, spalte)
   // int index ist nicht elegant!
   // index(index,0) hat Element in Zeile index, spalte 0; das ist die patient_id
   // mit patient_id soll gefiltert werden
   // Problem ist, dass index 0 Probleme macht!
   // wahrscheinlich weil am Anfang der Wert nicht definiert ist!

   QModelIndex indexId = patientModel->index(index,0);
   QString id = indexId.data().toString();

   // so wird Element mit index 0 (erster Eintrag im combofeld) nicht gefiltert!
   if (index > 0) {
        modelPatDietReq->setFilter("patient_id = " + id);
   }
   else if (index == 0 ){
            qDebug() << "id: " << id<< "hier bin ich schon!";
            //modelPatDietReq->setFilter("patient_id = " +id);
   }
   else {
       return;
   }

}


void Restriction::on_comboBoxPatient_activated(int index)
{
    QModelIndex indexId = patientModel->index(index,0);
    QString id = indexId.data().toString();
    qDebug() << "id: " << id<< "activated_ hier bin ich schon!";
    modelPatDietReq->setFilter("patient_id = " + id);

}

void Restriction::on_pushButtonAddRecordDietReq_clicked()
{
    int row = modelPatDietReq->rowCount();

    modelPatDietReq->insertRow(row);

    QSqlRecord record = modelPatDietReq->record(row);

    record.setValue("patient_id",2 );
    record.setValue("dietary_req_id",2 );
    modelPatDietReq->setRecord(row,record);

    modelPatDietReq->submitAll();


    /*
    // access item in index(row,column,[parentindex])
    // 1 = floor

    // jetzt Patient_id lesen!
    QModelIndex index = modelPatDietReq->index(row-1,0);
    QString id = index.data().toString();
    qDebug() << " patient_id: " << id;

    qDebug() << " patient_id RECORD: " << row;
    //model->setRecord(row,record);
    modelPatDietReq->setData(model->index(row, 1), 1);
*/
    modelPatDietReq->submitAll();
    qDebug() << "last error: " << modelPatDietReq->lastError();


//    model->setData(model->index(row,0),1);






 /* ************ mit record kann in model geschrieben werden..!!!


            QSqlRecord record = model.record(i);
                   double salary = record.value("salary").toInt();
                   salary *= 1.1;
                   record.setValue("salary", salary);
                   model.setRecord(i, record);
               }

*/






}

void Restriction::on_pushButtonSubmit_clicked()
{
    modelPatDietReq->submitAll();

}
