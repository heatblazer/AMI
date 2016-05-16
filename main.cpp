#include <QCoreApplication>
#include <QTcpSocket>
#include "ami.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    AMI* ami = new AMI();
    ami->init();

    return a.exec();
}
