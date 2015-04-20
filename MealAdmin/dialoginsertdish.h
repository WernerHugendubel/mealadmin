#ifndef DIALOGINSERTDISH_H
#define DIALOGINSERTDISH_H

#include <QDialog>

namespace Ui {
class DialogInsertDish;
}

class DialogInsertDish : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInsertDish(QWidget *parent = 0);
    ~DialogInsertDish();

private:
    Ui::DialogInsertDish *ui;
};

#endif // DIALOGINSERTDISH_H
