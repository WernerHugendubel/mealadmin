#ifndef CONNECTION_H
#define CONNECTION_H


#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtDebug>


static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");


    QString dbPath = QCoreApplication::applicationDirPath();
    qDebug() << dbPath;

            // + "/MyDatabase.db";
    //db.setDatabaseName(dbPath);

    if (!db.open()) {
    //    // handle error here...
         qDebug() << dbPath;
    }


    db.setDatabaseName("/home/freiw/hospmeal.sqlite");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;

    query.exec("create table ward (ward_id int primary key,ward text,note text)");
    query.exec("create table floor (floor_id int primary key,floor varchar(40),description varchar(100))");
    query.exec("create table room (room_id int primary key,floor_id int,description text)");
    query.exec("create table bed (bed_id int primary key,room_id int,description text)");

    query.exec("create table course (course_id int CHECK(course_id > 0),description text)");
    query.exec("create table dietary_req (dietary_req_id int primary key,description text)");

    // change 29.12
    query.exec("create table restriction (restriction_id int primary key,description text)");

    // change 29.12 + resctriction_id int
    query.exec("create table dish (dish_id int primary key,course_id int,meal text,restriction_id int)");
    query.exec("create table dish_ingredient (dish_id int,ingredient_id int,quantity real,unit text,price real,primary key (dish_id,ingredient_id))");
    query.exec("create table ingredient (ingredient_id int primary key,ingredient text)");


    query.exec("create table patient (patient_id int primary key,firstname text, lastname text, adress text, city text, gender text,bed_id int)");

    // change 29.12 firstname, lastname instead of simply name
    query.exec("create table employee (employee_id int primary key,firstname text, lastname text, gender text, ward_id int, employeetype_id int)");

    query.exec("create table employeetype (employeetype_id int primary key,employeetype text)");

    query.exec("create table patient_dietary_req (patient_id int,dietary_req_id int, primary key(patient_id,dietary_req_id))");
    query.exec("create table menu (menu_id int primary key,menuname text,price real)");
    query.exec("create table menu_dish (menu_id int,dish_id int,primary key (menu_id, dish_id))");
    query.exec("create table patient_menu (patient_id int,menu_id int,primary key(patient_id,menu_id))");


    query.exec("insert into bed values (1,1,'1-1')");
    query.exec("insert into bed values (2,1,'1-2')");
    query.exec("insert into bed values (3,1,'1-3')");
    query.exec("insert into bed values (4,1,'1-4')");
    query.exec("insert into bed values (5,2,'1-5')");
    query.exec("insert into bed values (6,2,'1-6')");
    query.exec("insert into bed values (7,3,'1-7')");
    query.exec("insert into bed values (8,4,'2-1')");
    query.exec("insert into bed values (9,4,'2-2')");
    query.exec("insert into bed values (10,5,'2-3')");
    query.exec("insert into bed values (11,5,'2-4')");
    query.exec("insert into bed values (12,5,'2-5')");
    query.exec("insert into bed values (13,6,'2-6')");
    query.exec("insert into bed values (14,6,'2-7')");
    query.exec("insert into bed values (15,7,'3-1')");
    query.exec("insert into bed values (16,7,'3-21')");
    query.exec("insert into bed values (17,7,'3-3')");
    query.exec("insert into bed values (18,8,'3-4')");
    query.exec("insert into bed values (19,8,'3-5')");
    query.exec("insert into bed values (20,9,'3-6')");

    query.exec("insert into floor values (1,'1st floor','')");
    query.exec("insert into floor values (2,'2nd floor','')");
    query.exec("insert into floor values (3,'3rd floor','')");

    query.exec("insert into course values (1,'Entry')");
    query.exec("insert into course values (2,'Main')");
    query.exec("insert into course values (3,'Desert')");

    query.exec("insert into dietary_req values (1,'coumadin')");
    query.exec("insert into dietary_req values (2,'coeliac condition')");
    query.exec("insert into dietary_req values (3,'diabetes')");

     query.exec("insert into dish values (1,2,'Spaghetti al dente',1)");
     query.exec("insert into dish values (2,2,'Gnocchi alla romana')");
     query.exec("insert into dish values (3,1,'Soup vegan')");
     query.exec("insert into dish values (4,1,'Tomato soup')");


     // new 29.12
     query.exec("insert into restriction values (1,'gluten')");
     query.exec("insert into restriction values (2,'diabetes')");


     query.exec("insert into dish_ingredient values (1,1,100.0,'g',0.0)");
     query.exec("insert into dish_ingredient values (1,6,20.0,'g',0.0)");

     query.exec("insert into employeetype values (1,'Nurse')");

     // 29.12. PROBLEMS employee doesnt insert!
     query.exec("insert into employee values (1,'Reinhild','f',1,1)");
     query.exec("insert into employee values (2,'Joe','m',1,1)");

     query.exec("insert into ingredient values (1,'semolina')");
     query.exec("insert into ingredient values (2,'water')");
     query.exec("insert into ingredient values (3,'skim milk)'");
     query.exec("insert into ingredient values (4,'salt')");
     query.exec("insert into ingredient values (5,'butter')");
     query.exec("insert into ingredient values (6,'olive oil')");

     query.exec("insert into menu values (1,'standard',8.0)");
     query.exec("insert into menu values (2,'veggi',7.0)");
     query.exec("insert into menu values (3,'vegan',9.0)");

     query.exec("insert into menu_dish values (1,1)");
     query.exec("insert into menu_dish values (2,3)");
     query.exec("insert into menu_dish values (1,4)");
     query.exec("insert into menu_dish values (2,2)");

     query.exec("insert into patient values (1,'Werner','Frei','Angerweg 17','Meran','m',0)");

     query.exec("insert into patient_dietary_req values (1,3)");

     query.exec("insert into patient_menu values (1,1)");


     query.exec("insert into room values (1,1,'')");
     query.exec("insert into room values (2,1,'')");
     query.exec("insert into room values (3,1,'')");
     query.exec("insert into room values (4,2,'')");
     query.exec("insert into room values (5,2,'')");
     query.exec("insert into room values (6,2,'')");
     query.exec("insert into room values (7,3,'')");
     query.exec("insert into room values (8,3,'')");
     query.exec("insert into room values (9,3,'')");

     query.exec("insert into ward values (1,'Reha','')");


    db.close();

   return true;
}

#endif

