#include "ami.h"

#include <QTcpSocket>

#include <iostream>
#include <stdio.h> // for fprintf //


AMI::AMI(QObject *parent) :
    QObject(parent), m_state(AmiState::AMI_DISCONNECTED)
{

}


AMI::~AMI()
{
    if (m_socket != nullptr) {
        delete m_socket;
    }
}


//!
//! \brief AMI::init, initializes socket and connections between objects
//! also, returns a value, and emits a signal
//! \param pResult return of the created QTcpSocket (1-OK) (0-FAIL)
//! NOTE :this is NOT FORBIDEN BY <C/C++ MISRA>
//!
void AMI::init(int *pResult)
{
    // I am interested IF m_socket was created, I don`t want asserts with    //
    // tryung to access not created socket                                   //
    // I will create the socket in the init since constructor can`t return a //
    // value, and I might need to return error if socket can`t be allocated  //

    m_socket = new QTcpSocket(this);

    if (m_socket != nullptr){
        *pResult = 1;
    } else {
        *pResult = 0;
    }

    connect(m_socket, SIGNAL(connected()),
            this, SLOT(hConnected()));

    connect(m_socket, SIGNAL(disconnected()),
            this, SLOT(hDisconnected()));

    connect(m_socket, SIGNAL(bytesWritten(qint64)),
            this, SLOT(hBytesWritten(qint64)));

    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(hReadyWrite()));

    // connect to the routing function also
    connect(this, SIGNAL(amiStateChanged(AmiState)),
            this, SLOT(route()));

    // jump to the routing function //
    emit amiStateChanged(m_state);
}

void AMI::testAction()
{
    m_socket->write("Action: ListCommands\n\n");
}

void AMI::tryLogin()
{
   // login("goro", "sopa123"); // тествам грешен login //
   login("joro", "sopa123");
}


void AMI::hConnected()
{
    m_state = AmiState::AMI_CONNECTED;
    emit amiStateChanged(m_state);
}


void AMI::hDisconnected()
{
    m_state = AmiState::AMI_DISCONNECTED;
    emit amiStateChanged(m_state);
}


void AMI::hBytesWritten(qint64 bytes)
{
    std::cout  << "Bytes written: " << bytes;
    if(bytes > 0){
        m_state = AmiState::AMI_READY;
    } else {
        m_state = AmiState::AMI_NOT_READY;
    }
    emit amiStateChanged(m_state);
}

// maybe emit or change state //
void AMI::hReadyWrite()
{
    QString s;
    m_state = AmiState::AMI_NOT_READY;
    if (m_socket->canReadLine()) {
        // read all //
        // or if needed read line by line depends what do we need //
        s = QString(m_socket->readAll().simplified());
        printf("%s\n", s.toLocal8Bit().constData());
        m_state = AmiState::AMI_READY;
    }
    // else ami is not ready //

    emit amiStateChanged(m_state);
}

//!
//! \brief take ami action
//! \param string or uri taking the action
//!
void AMI::action(const QString &act)
{
    qint64 bytes = m_socket->write(act.toLocal8Bit());
    if(bytes <= 0) {
        m_state = AmiState::AMI_NOT_READY;
    } else {
        m_state = AmiState::AMI_READY;
    }

    emit amiStateChanged(m_state);
}


//!
//! \brief Handle all AMI states and route them to the approp functions
//!
void AMI::route(void)
{
    switch (m_state)
    {
    case AmiState::AMI_LOGIN_OK:
        std::cout << "LOGGED IN\n";
        break;

    case AmiState::AMI_LOGIN_FAILED:
        std::cout << "NOT LOGGED IN\n";
        // какво да правим тука??? //
        // да пробваме пак? //
        tryLogin();
        break;

    case AmiState::AMI_CONNECTED:
        std::cout << "AMI CONNECTED\n";
        // try login
        tryLogin();
        break;

    case AmiState::AMI_CONNECTION_LOST:
        std::cout << "AMI CONNECTION LOST\n";
        // try to reconnect //
        m_socket->connectToHost("192.168.32.89", 5038);
        break;

    case AmiState::AMI_READY:
        std::cout << "AMI READY\n";
        // ready to send actions
        break;

    case AmiState::AMI_NOT_READY:
        std::cout << "AMI NOT READY\n";
        break;

    case AmiState::AMI_DISCONNECTED:
        std::cout << "AMI DISCONNECTED\n";
        // try to connect  //
    default:
        m_socket->connectToHost("192.168.32.89", 5038);
        break;
    }
}


void AMI::login(const QString& uname, const QString& pass)
{
    QString login_str = QString("Action: Login\nUsername: %1\nSecret: %2\n\n")
            .arg(uname).arg(pass);

    qint64 res = m_socket->write(login_str.toLocal8Bit());
    // I can`t be logged with -1 or less bytes than requested to be written //
    if ((res < 0) || (res < login_str.length())) {
        // the command will be error
        m_state = AmiState::AMI_LOGIN_FAILED;
    } else {
        m_state = AmiState::AMI_LOGIN_OK;
    }

    emit amiStateChanged(m_state);
}


