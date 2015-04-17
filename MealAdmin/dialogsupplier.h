#ifndef DIALOGSUPPLIER_H
#define DIALOGSUPPLIER_H

#include <QDialog>

namespace Ui {
class DialogSupplier;
}

class DialogSupplier : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSupplier(QWidget *parent = 0);
    ~DialogSupplier();

private:
    Ui::DialogSupplier *ui;
};

#endif // DIALOGSUPPLIER_H
