#ifndef DIALOGBED_H
#define DIALOGBED_H

#include <QDialog>
#include "QSqlQueryModel"
#include "QSqlTableModel"
#include "QTableView"
#include "QSqlRelationalTableModel"

namespace Ui {
class DialogBed;
}

class DialogBed : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBed(QWidget *parent = 0);
    ~DialogBed();

private slots:
    void on_comboBoxBed_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();


    void on_comboBoxPatient_currentIndexChanged(int index);


private:
    Ui::DialogBed *ui;

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

#endif // DIALOGBED_H
