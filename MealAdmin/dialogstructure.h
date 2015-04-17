#ifndef DIALOGSTRUCTURE_H
#define DIALOGSTRUCTURE_H

#include <QDialog>
#include "QSqlQueryModel"
#include "QSqlTableModel"
#include "QTableView"
#include "QSqlRelationalTableModel"




namespace Ui {
class DialogStructure;
}

class DialogStructure : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStructure(QWidget *parent = 0);



    ~DialogStructure();

private slots:
    void on_pushButton_NewRecord_clicked();

    void on_pushButton_DeleteRecordFloor_clicked();

    void on_pushButton_NewRecordDish_clicked();

    void on_pushButton_DeleteRecordDish_clicked();

    void on_pushButton_NewRecordPerson_clicked();

    void on_pushButton_DeleteRecordPatient_clicked();

    void on_NewRecordPatientMenu_clicked();

    void on_DeleteRecordPatientMenu_clicked();

private:
    Ui::DialogStructure *ui;
    QSqlTableModel *model;
    QSqlTableModel *modelPatient;

    QSqlRelationalTableModel *modelMeal;
    QSqlRelationalTableModel *modelPatientMenu;


    // tableView war das Problem!! Muss trotz es im dialgfenster da ist nochmal deklariert werden!
    QTableView *tableView;
    QTableView *tableViewMeal;
    QTableView *tableViewPatient;
    QTableView *tableViewPatientMenu;

};

#endif // DIALOGSTRUCTURE_H
