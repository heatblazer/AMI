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
            this, SLOT(hBytesWritten(qint64)));


    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(hReadyWrite()));

    // ami internals
    connect(this, SIGNAL(amiConnected()),
            this, SLOT(tryLogin()));

    connect(this, SIGNAL(amiDisconnected()),
            this, SLOT(hDisconnected())); // handle with the same slot for now
   // connect(this, SIGNAL(loginSuccess()),
   //         this, SLOT(testAction()));

    // connect to the routing function also
    connect(this, SIGNAL(amiConnected()),
            this, SLOT(route()));
    connect(this, SIGNAL(amiDisconnected()),
            this, SLOT(route()));
    connect(this, SIGNAL(actionReady()),
            this, SLOT(route()));
    connect(this, SIGNAL(actionNotReady()),
            this, SLOT(route()));

    m_socket->connectToHost("192.168.32.89", 5038);



}

void AMI::testAction()
{
    m_socket->write("Action: ListCommands\n\n");
}

void AMI::tryLogin()
{
   login("joro", "sopa123");
}



void AMI::hConnected()
{
    m_state = AmiState::AMI_CONNECTED;
    emit amiConnected();
}


void AMI::hDisconnected()
{
    m_state = AmiState::AMI_DISCONNECTED;
}


void AMI::hBytesWritten(qint64 bytes)
{
    std::cout  << "Bytes written: " << bytes;
}


void AMI::hReadyWrite()
{
    QString s;
    if (!m_socket->canReadLine()) {
        m_socket->waitForReadyRead(3000);
    }
    s = QString(m_socket->readLine().simplified());
    std::cout << s.toStdString() << std::endl;
}

//!
//! \brief take ami action
//! \param string or uri taking the action
//!
void AMI::action(const QString &act)
{
    m_socket->write(act.toLocal8Bit());
}



void AMI::route(void)
{
    switch (m_state)
    {
    case AmiState::AMI_CONNECTED:
        std::cout << "AMI CONNECTED\n";
        // try login
        break;
    case AmiState::AMI_DISCONNECTED:
        std::cout << "AMI DISCONNECTED\n";
        // try to connect again
        break;
    case AmiState::AMI_CONNECTION_LOST:
        std::cout << "AMI CONNECTION LOST\n";
        //
        break;
    case AmiState::AMI_READY:
        std::cout << "AMI READY\n";
        // ready to send actions
        break;
    case AmiState::UNKNOWN:
    default:
        std::cout << "AMI UNKNOWN STATE";
        break;
    }
}



void AMI::login(const QString& uname, const QString& pass)
{
    QString login_str = QString("Action: Login\nUsername: %1\nSecret: %2\n\n")
            .arg(uname).arg(pass);

    qint64 res = m_socket->write(login_str.toLocal8Bit());

    if (res < 0) {
        emit loginError();
    } else {
        emit loginSuccess();
    }
}
