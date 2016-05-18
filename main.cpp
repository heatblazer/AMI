#include <QApplication>
#include <QWidget>
#include <QTcpSocket>
#include "ami.h"
#include "ptt.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // create an ami machine //
    AMI ami;

    // initialize it //
    ami.init();

    // create a test ptt device //
    ptt p1;
    ptt p2;

    // get a handle to the ami //
    p1.registerAmi(&ami);
    p2.registerAmi(&ami);

    return a.exec();
}


