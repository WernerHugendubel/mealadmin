#ifndef RESTRICTION_H
#define RESTRICTION_H

#include <QDialog>
#include "QSqlQueryModel"
#include "QSqlTableModel"
#include "QTableView"
#include "QSqlRelationalTableModel"

namespace Ui {
class Restriction;
}

class Restriction : public QDialog
{
    Q_OBJECT

public:
    explicit Restriction(QWidget *parent = 0);
    ~Restriction();

private slots:
    void on_comboBoxBed_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();


    void on_comboBoxPatient_currentIndexChanged(int index);


    void on_comboBoxPatient_activated(int index);

    void on_pushButtonAddRecordDietReq_clicked();

    void on_pushButtonSubmit_clicked();

private:
    Ui::Restriction *ui;

    QSqlTableModel *modelTable;
    QSqlTableModel *model;
    QSqlTableModel *menuModel;
    QSqlTableModel *patientModel;


    QSqlRelationalTableModel *modelRelationalBed;

    QTableView *tableViewBed;
    QTableView *tableView;


    // Master-Detail Patient->PatDietReq
    QSqlRelationalTableModel *modelPatDietReq;
    QTableView *tableViewPatientDietReq;






};

#endif // RESTRICTION_H
