#include "mainwindow.h"
#include <QApplication>
#include "connection.h"
#include "dialogbed.h"
#include "dialogstructure.h"
#include "login.h"
#include <unittest++/UnitTest++.h>
#include <myclass.h>



TEST(WillFail) {
    CHECK(true);
}



TEST(MyMath) {
    MyClass my;
    CHECK(my.addition(3,4) == 12);
}



int main(int argc, char *argv[])
{
    //UnitTest::TestList;
    // 01.01.201
    //return UnitTest::RunAllTests();

    QApplication a(argc, argv);



    // MainWindows is called from Login
    // then Login !!



    MainWindow mainWindow;
    Login passwordWindow;


    passwordWindow.setModal(true);
    passwordWindow.exec();
    mainWindow.show();

    //DialogBed dialogBed;
    //dialogBed.show();


    return a.exec();
}
