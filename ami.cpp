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


void AMI::init(void)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, SIGNAL(connected()),
            this, SLOT(hConnected()));

    connect(m_socket, SIGNAL(disconnected()),
            this, SLOT(hDisconnected()));

    connect(m_socket, SIGNAL(bytesWritten(qint64)),
            this, SLOT(hBytesWritten(quint64)));

    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(hReadyWrite()));

    m_socket->connectToHost("google.com", 80);

    if (!m_socket->waitForConnected(5000)) {

    }

}


void AMI::hConnected()
{
    m_socket->write("HEAD / HTTP1.0\r\n\r\n\r\n");

}


void AMI::hDisconnected()
{
    qDebug() << "Disconected\n";
}


void AMI::hBytesWritten(quint64 bytes)
{
    qDebug() << bytes << " read ";
}


void AMI::hReadyWrite()
{
    std::cout << m_socket->readAll().toStdString();
}

//!
//! \brief take ami action
//! \param string or uri taking the action
//!
void AMI::action(const QString &act)
{

}

