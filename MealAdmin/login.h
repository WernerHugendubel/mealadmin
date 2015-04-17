#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlDatabase>
# include <QString>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);

    // delete ? uses for trying to access loginname..
    QString UserName() const;



    ~Login();


private slots:
    void on_pushButton_clicked();

private:

      Ui::Login *ui;


};

#endif // LOGIN_H
