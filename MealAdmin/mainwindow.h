#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtCore>
#include <QDialog>
#include "QTableView"
#include "QSqlRelationalTableModel"

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

    void on_comboBoxBed_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    QSqlRelationalTableModel *modelPatientDietary_req ;

    QTableView *tableViewPatientDietary_req;

};

#endif // MAINWINDOW_H
