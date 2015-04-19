// 18.03.2015
// 07.04.2015

#include "restriction.h"
#include "ui_restriction.h"
#include "QDebug"
#include <QSqlQuery>
#include <QString>
#include <QDateTime>


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


    // model für Tabelle "menu"
    menuModel = new QSqlTableModel(this);
    menuModel->setTable("menu");
    menuModel->select();
    ui->comboBoxMenu->setModel(menuModel);


    // model für Tabelle "bed"
    model = new QSqlTableModel(this);
    model->setTable("bed");
    model->setSort(0, Qt::AscendingOrder);
    model->setHeaderData(0, Qt::Horizontal, tr("bed_id"));
    model->setHeaderData(1, Qt::Horizontal, tr("room_id"));
    model->setHeaderData(2, Qt::Horizontal, tr("description"));
    model->select();

    // tableView für Bed
    tableViewBed = new QTableView;
    tableViewBed->setColumnHidden(0, true);
    tableViewBed->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableViewBed->resizeColumnsToContents();

    // model für Tabelle "patient_diet_req"
    // QsqlRelationalTableModel - weil Fremdschlüssel "patient_id" und "dietary_req_id" vorhanden sind.
    //
    modelPatDietReq = new QSqlRelationalTableModel(this);
    modelPatDietReq->setTable("patient_dietary_req");

    //modelPatDietReq->setRelation(0,QSqlRelation("patient","patient_id","lastname"));
    modelPatDietReq->setRelation(1,QSqlRelation("dietary_req","dietary_req_id","description"));
    modelPatDietReq->select();

    qDebug() << "patient " << ui->comboBoxPatient->currentText();

    // Zwischenlösung: erstes Element in ComboBox wird gefiltert!
    // gleich Lösung wie in Slot
    QModelIndex indexId = patientModel->index(0,0);
    QString id = indexId.data().toString();

    modelPatDietReq->setFilter("patient_id = " + id);

    // zeige tableView mit patient-id, dietary_req->description
    ui->tableViewPatientDietReq->setModel(modelPatDietReq);

    // primary view is a table
    //ui->tableViewBed->setModel(model);

    // the same model as combobox
    ui->comboBoxBed->setModel(model);
    ui->comboBoxBed->setModelColumn(2);
    ui->comboBoxBed->modelColumn();



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


