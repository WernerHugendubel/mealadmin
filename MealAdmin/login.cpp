#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "QSqlQuery"



Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/freiw/Qt/5.3/hospmeal.sqlite");

    if (db.open())
    {
        qDebug() << "Opened in LOGIN!";
    }

    if (!db.open()) {
       qDebug() << "No Database Opened IN LOGING!";
    }

}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{

    QString username,password;
    username=ui->lineEditUsername->text();
    password=ui->lineEditPassword->text();

    qDebug() << username + " " + password;

    QSqlQuery qry;
    int count=0;

    if (qry.exec("select * from employee where username  = \'"+username+"\' and password =\'"+password+"\'" ))
    {
        while (qry.next() )
        {
            count++;
            //qDebug() << "OK asdfasdfasdfd";
            //qDebug() << count;
        }
    }

    if (count==1) {
        ui->labelLogin->setText("Username, Password OK!");
        this->hide();

    }
    else
    {
        ui->labelLogin->setText("Wrong Username or Password!");
    }



}

QString Login::UserName() const
{
    //return lineEdit->text();
    return "testusername";
}
