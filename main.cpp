#include <QApplication>
#include <QWidget>
#include <QTcpSocket>
#include "ami.h"
#include "ptt.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ptt p;

    return a.exec();
}
