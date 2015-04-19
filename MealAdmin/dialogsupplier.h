#ifndef DIALOGSUPPLIER_H
#define DIALOGSUPPLIER_H

#include <QDialog>
#include "QSqlTableModel"

namespace Ui {
class DialogSupplier;
}

class DialogSupplier : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSupplier(QWidget *parent = 0);
    ~DialogSupplier();

private slots:
   // void on_tableViewDish_activated(const QModelIndex &index);

    void on_pushButtonSave_clicked();

    void on_DialogSupplier_destroyed();

private:
    Ui::DialogSupplier *ui;
    QSqlTableModel * qryTableModelDish;

};

#endif // DIALOGSUPPLIER_H
