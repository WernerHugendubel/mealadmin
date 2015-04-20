#ifndef DIALOGUDATEDISHES_H
#define DIALOGUDATEDISHES_H

#include <QDialog>

namespace Ui {
class DialogUdateDishes;
}

class DialogUdateDishes : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUdateDishes(QWidget *parent = 0);
    ~DialogUdateDishes();

private:
    Ui::DialogUdateDishes *ui;
};

#endif // DIALOGUDATEDISHES_H
