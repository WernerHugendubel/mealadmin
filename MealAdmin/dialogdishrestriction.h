#ifndef DIALOGDISHRESTRICTION_H
#define DIALOGDISHRESTRICTION_H

#include <QDialog>

namespace Ui {
class DialogDishRestriction;
}

class DialogDishRestriction : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDishRestriction(QWidget *parent = 0);
    ~DialogDishRestriction();

private:
    Ui::DialogDishRestriction *ui;
};

#endif // DIALOGDISHRESTRICTION_H
