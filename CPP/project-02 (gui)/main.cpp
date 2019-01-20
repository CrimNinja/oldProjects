//Siva Sankar Kannan 267605
//siva.kannan@student.tut.fi

//Joe David 267598
//joe.david@bstudent.tut.fi

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
