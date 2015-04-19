#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtCore>
#include <QDialog>
#include "QTableView"
#include "QSqlRelationalTableModel"
#include <QModelIndex>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Structure_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_Supplier_clicked();

    void on_pushButtonPatientDietary_req_newRecord_clicked();

    void on_pushButtonSaveOrder_clicked();

    void on_pushButton_admin_clicked();

    void on_comboBoxFloor_currentIndexChanged(int index);

    void on_comboBoxFloor_activated(int index);

    void on_comboBoxMenuMid_activated(int index);

    void on_comboBoxMenuEv_activated(int index);

    void on_comboBoxBed_activated(int index);

    void on_pushButtonRestriction_clicked();

    void on_pushButtonSupplier_clicked();

private:

    Ui::MainWindow *ui;

    QSqlRelationalTableModel *modelPatientDietary_req ;

    QTableView *tableViewPatientDietary_req;

    QSqlQueryModel *qryModelFloor;

    // war nur Versuch wegen Fehlermeldung on index_changed!
    // QModelIndex indexId;

    QSqlQueryModel * userModel;
    QSqlQueryModel * bedModel;

    QSqlQueryModel * patientModel;

    QSqlQueryModel * menuMidModel;

    QSqlQueryModel * menuEvModel;

    QSqlQueryModel * listMidModel;

    QSqlQueryModel * listEvModel;


};

#endif // MAINWINDOW_H
