#ifndef DIALOGGETLISTORDEREDDISHES_H
#define DIALOGGETLISTORDEREDDISHES_H

#include <QDialog>

namespace Ui {
class DialogGetListOrderedDishes;
}

class DialogGetListOrderedDishes : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGetListOrderedDishes(QWidget *parent = 0);
    ~DialogGetListOrderedDishes();

private:
    Ui::DialogGetListOrderedDishes *ui;
};

#endif // DIALOGGETLISTORDEREDDISHES_H
