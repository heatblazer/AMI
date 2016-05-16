#include "ami.h"
#include <QTcpSocket>
#include <iostream>


AMI::AMI(QObject *parent) :
    QObject(parent)
{

}

AMI::~AMI()
{

}


void AMI::init()
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, SIGNAL(connected()),
            this, SLOT(connected()));

    connect(m_socket, SIGNAL(disconnected()),
            this, SLOT(disconnected()));

    connect(m_socket, SIGNAL(bytesWritten(qint64)),
            this, SLOT(bytesWritten(quint64)));

    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(readyRead()));

    m_socket->connectToHost("google.com", 80);

    if (!m_socket->waitForConnected(5000)) {

    }

}


void AMI::connected()
{
    m_socket->write("HEAD / HTTP1.0\r\n\r\n\r\n");

}


void AMI::disconnected()
{
    qDebug() << "Disconected\n";
}


void AMI::bytesWritten(quint64 bytes)
{
    qDebug() << bytes << " read ";
}


void AMI::readyRead()
{
    std::cout << m_socket->readAll().toStdString();
}


