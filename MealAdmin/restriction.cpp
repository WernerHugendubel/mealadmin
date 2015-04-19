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

    modelPatDietReq->setRelation(1,QSqlRelation("dietary_req","dietary_req_id","description"));

    modelPatDietReq->select();

    qDebug() << "patient " << ui->comboBoxPatient->currentText();
    // Zwischenlösung: erstes Element in ComboBox wird gefiltert!
    // gleich Lösung wie in Slot

    QModelIndex indexId = patientModel->index(0,0);
    QString id = indexId.data().toString();
    modelPatDietReq->setFilter("patient_id = " + id);

    // zeige tableView mit patient-id, dietary_req->description
    tableViewPatientDietReq->setSelectionBehavior(QAbstractItemView::SelectRows);
   // tableViewPatientDietReq->resizeColumnsToContents();


    ui->tableViewPatientDietReq->setModel(modelPatDietReq);

   // tableViewPatientDietReq->setItemDelegate(new QSqlRelationalDelegate(tableViewPatientDietReq));

    // view->setItemDelegate(new QSqlRelationalDelegate(view));
    // Combobox für dietary_req_id, deskription


    // primary view is a table
    //ui->tableViewBed->setModel(model);

    // the same model as combobox
  /*
    ui->comboBoxBed->setModel(model);
    ui->comboBoxBed->setModelColumn(2);
    ui->comboBoxBed->modelColumn();

*/


    /*      SO GEHTS mit COMBOBOX und RELATION!
     *     // **************************************************************************************
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
    // Das macht automatisch eine combo box, und zwar zu den QSqlRelations's !!
    // was ist wenn es mehrere gibt?
    ui->tableViewMeal->setItemDelegate(new QSqlRelationalDelegate(tableViewMeal));


*/








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


    /*
    // access item in index(row,column,[parentindex])
    // 1 = floor

    // jetzt Patient_id lesen!
    QModelIndex index = modelPatDietReq->index(row-1,0);
    QString id = index.data().toString();
    qDebug() << " patient_id: " << id;
    //QSqlRecord record = model->record(row+1);
    //record.setValue("patient_id", 1);

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
