#include <QApplication>
#include <QWidget>
#include <QTcpSocket>
#include <QHBoxLayout>
#include "ami.h"
#include "ptt.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // create an Ami machine //
    Ami Ami;

    // initialize it //
    int res = 0;
    Ami.init(&res);

    if (res == 0) {
        exit(1);
    }


    // create a test ptt device //
    ptt p1;
    ptt p2;
    ptt p3;
    ptt p4;

    // get a handle to the Ami //
    p1.registerAmi(&Ami);
    p2.registerAmi(&Ami);
    p3.registerAmi(&Ami);
    p4.registerAmi(&Ami);


    QWidget mw;
    mw.setLayout((QHBoxLayout*)&ptt::hlayout);
    mw.show();


    return a.exec();
}


