#include <QApplication>
#include <QWidget>
#include <QTcpSocket>
#include "ami.h"
#include "ptt.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AMI ami;
    ami.init();
    ptt p(&ami);

    Q_UNUSED(p);
    return a.exec();
}
